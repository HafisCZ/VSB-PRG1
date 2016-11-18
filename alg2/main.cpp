#include <iostream>
#include <ctime>

bool Colony[20][20] = {};
bool Colony2[20][20] = {};

/**
    Pseudo-random number generator.

    @param min Minimal value (included).
    @param max Maximal value (included).
    @return Pseudo-random number.
*/
int pseudo_random(int min, int max) {
    static unsigned int seed = time(0);
    seed = (3245879 * seed + 1275845);
    return (seed % (min + max + 1)) - min;
}

/**
    Generate random colony.

    @param rows Total row count of Colony.
    @param cols Total col count of Colony.
    @param colony Colony.
    @param max_occurences_in_row Maximum number of living cells per row.
    @param occurence_chance Chance 1:X for any cell to be alive.
*/
template <const int rows, const int cols> void generateRandomColony(bool colony[rows][cols], int max_occurences_in_row, int occurence_chance) {
    int occured, temp;
    if (max_occurences_in_row >= rows) {
        max_occurences_in_row = rows - 1;
    }
    for (int x = 0; x < rows; x++) {
        occured = pseudo_random(0, max_occurences_in_row);
        for (int y = 0; y < cols; y++) {
            if (occured > 0) {
                temp = pseudo_random(0, occurence_chance);
                if (temp == 0) {
                    colony[x][y] = true;
                    occured--;
                } else {
                    colony[x][y] = false;
                }
            } else {
                break;
            }
        }
    }
}

/**
    Generate random colony.

    @param rows Total row count of Colony.
    @param cols Total col count of Colony.
    @param colony Colony.
    @param max_occurences_in_row Maximum number of living cells per row.
    @param occurence_chance Chance 1:X for any cell to be alive.
    @param split_into_parts Split Colony into X parts for better average.
*/
template <const int rows, const int cols> void generateRandomColony(bool colony[rows][cols], int max_occurences_in_row, int occurence_chance, int split_into_parts) {
    int occured, temp;
    if (max_occurences_in_row >= rows) {
        max_occurences_in_row = rows - 1;
    }
    for (int i = 0; i < split_into_parts / 2; i++) {
        for (int j = 0; j < split_into_parts / 2; j++) {
            for (int x = 0; x < rows / (split_into_parts / 2); x++) {
                occured = pseudo_random(0, max_occurences_in_row / 2);
                for (int y = 0; y < cols / (split_into_parts / 2); y++) {
                    if (occured > 0) {
                        temp = pseudo_random(0, occurence_chance * 2);
                        if (temp == 0) {
                            colony[x + (rows / (split_into_parts / 2)) * i][y + (cols / (split_into_parts / 2)) * j] = true;
                            occured--;
                        } else {
                            colony[x + (rows / (split_into_parts / 2)) * i][y + (cols / (split_into_parts / 2)) * j] = false;
                        }
                    } else {
                        continue;
                    }
                }
            }
        }
    }
}

/**
    Check whether cell is alive. Out of range cell is considered dead.

    @param rows Total row count of Colony.
    @param cols Total col count of Colony.
    @param colony Colony.
    @param row Row of cell.
    @param col Column of cell.
    @return If cell is alive.
*/
template <const int rows, const int cols> bool isAlive(bool colony[rows][cols], const int& row, const int& col) {
    return ((row >= 0 && row < rows && col >= 0 && col < cols) ? colony[row][col] : false);
}

/**
    Check how similar is cell configuration according to specified configuration.

    @param rows Total row count of Colony.
    @param cols Total col count of Colony.
    @param pattern_rows Total row count of Pattern.
    @param pattern_cols Total col count of Pattern.
    @param colony Colony.
    @param left_row Row of cell (Left-most row cell of template).
    @param left_col Column of cell (Left-most column cell of template).
    @param pattern Sub-colony of Colony.
    @return How many cells are equal.
*/
template <const int rows, const int cols, const int pattern_rows, const int pattern_cols> unsigned int similarityIndex(bool colony[rows][cols], const int& left_row, const int& left_col, bool pattern[pattern_rows][pattern_cols]) {
    unsigned int similarity = 0;
    for (int x = 0; x < pattern_rows; x++) {
        for (int y = 0; y < pattern_cols; y++) {
            if (colony[left_row + x][left_col + y] == pattern[x][y]) similarity++;
        }
    }
    return similarity;
}

/**
    Check whether is cell configuration equal according to specified configuration.

    @param rows Total row count of Colony.
    @param cols Total col count of Colony.
    @param pattern_rows Total row count of Pattern.
    @param pattern_cols Total col count of Pattern.
    @param colony Colony.
    @param pattern Sub-colony of Colony.
    @param row Row of cell (Left-most row cell of template).
    @param col Column of cell (Left-most column cell of template).
    @return If colony has specified pattern.
*/
template <const int rows, const int cols, const int pattern_rows, const int pattern_cols> bool hasPattern(bool colony[rows][cols], bool pattern[pattern_rows][pattern_cols], int& row, int& col) {
    for (row = 0; row < (rows - pattern_rows + 1); row++) {
        for (col = 0; col < (cols - pattern_cols + 1); col++) {
            if (similarityIndex<rows, cols, pattern_rows, pattern_cols>(colony, row, col, pattern) == pattern_rows * pattern_cols) {
                return true;
            }
        }
    }
    row = -1;
    col = -1;
    return false;
}

template <const int rows, const int cols> unsigned int areAll(bool colony[rows][cols], bool state) {
    unsigned int are = 0;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (colony[x][y] == state) are++;
        }
    }
    return are;
}

template <const int rows, const int cols, const int area> unsigned int areInState(bool colony[rows][cols], const int& row, const int& col, bool outsideState) {
    unsigned int inState = 0;
    for (int x = row - 1; x < row - 1 + area; x++) {
        for (int y = col - 1; y < col - 1 + area; y++) {
            if (x == row && y == col) continue;
            if (isAlive<rows, cols>(colony, x, y) == outsideState) inState++;
        }
    }
    return inState;
}

template <const int rows, const int cols> void printColony(bool colony[rows][cols], std::ostream& stream) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            stream << (colony[x][y] ? "X " : ". ");
        }
        stream << std::endl;
    }
}

template <const int rows, const int cols> void copyColony(bool colony[rows][cols], bool newColony[rows][cols]) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            colony[x][y] = newColony[x][y];
        }
    }
}

template <const int rows, const int cols> void updateColony(bool colony[rows][cols], bool newColony[rows][cols]) {
    unsigned int t = 0;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            t = areInState<rows, cols, 3>(colony, x, y, true);
            newColony[x][y] = (colony[x][y] ? ((t < 2 || t > 3) ? false : true) : (t == 3));
        }
    }
    copyColony<rows, cols>(colony, newColony);
}

int main()
{
    int c;
    generateRandomColony<20, 20>(Colony, 20, 2);
    std::cout << "Generated: " << areAll<20, 20>(Colony, true) << " living cells." << std::endl;

    while (1) {
        printColony<20, 20>(Colony, std::cout);
        std::cout << "How many cycles to generate: ";
        std::cin >> c;
        if (c <= 0) break;
        else {
            for (int i = 0; i < c; i++) {
               updateColony<20, 20>(Colony, Colony2);
            }
        }
    }

	return 0;
}
