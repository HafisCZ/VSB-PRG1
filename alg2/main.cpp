#include <iostream>

bool Colony[6][6] =
{
	{false, false, false, false, false, false},
	{false, false, false, true, false, false},
	{false, true, false, false, true, false},
	{false, true, false, false, true, false},
	{false, false, true, false, false, false},
	{false, false, false, false, false, false}
};

bool Colony2[6][6] = {};

template <const int rows, const int cols> bool isAlive(bool colony[rows][cols], const int& row, const int& col) {
    return ((row >= 0 && row < rows && col >= 0 && col < cols) ? colony[row][col] : false);
}

template <const int rows, const int cols, const int pattern_rows, const int pattern_cols> unsigned int similarityIndex(bool colony[rows][cols], const int& left_row, const int& left_col, bool pattern[pattern_rows][pattern_cols]) {
    unsigned int similarity = 0;
    for (int x = 0; x < pattern_rows; x++) {
        for (int y = 0; y < pattern_cols; y++) {
            if (colony[left_row + x][left_col + y] == pattern[x][y]) similarity++;
        }
    }
    return similarity;
}

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
            stream << (colony[x][y] ? "X" : ".");
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
    char c;
    do {
        printColony<6, 6>(Colony, std::cout);
        updateColony<6, 6>(Colony, Colony2);
    } while ((c = std::cin.get()) != 'E');

	return 0;
}
