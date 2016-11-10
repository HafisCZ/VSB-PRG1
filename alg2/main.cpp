#include <iostream>

const int N = 10;

bool Colony[N][N] =
{
	{true, true, false, false, true, true, true, true, false, false},
	{true, true, true, false, true, false, true, true, true, true},
	{true, true, true, false, true, true, true, false, true, true},
	{true, false, true, false, true, true, true, true, true, true},
	{true, true, true, false, true, false, true, false, false, true},
	{true, true, true, true, true, true, false, true, true, true},
	{false, true, true, true, true, true, false, true, false, true},
	{true, true, false, false, true, true, true, true, false, true},
	{false, true, true, true, true, false, true, true, true, true},
	{false, true, true, true, true, true, true, true, true, false}
};

bool pattern1[3][4] = {
{true, false, true, false},
{true, false, true, false},
{true, false, true, false}
};

// -UNUSED
template <const int rows, const int cols> bool isAlive(const bool colony[rows][cols], int row, int col) {
    return ((row >= 0 && row < rows && col >= 0 && col < cols) ? colony[row][col] : false);
}


template <const int rows, const int cols, const int pattern_rows, const int pattern_cols> unsigned int similarityIndex(const bool colony[rows][cols], const int& left_row, const int& left_col, bool pattern[pattern_rows][pattern_cols]) {
    unsigned int similarity = 0;
    for (int x = 0; x < pattern_rows; x++) {
        for (int y = 0; y < pattern_cols; y++) {
            if (colony[left_row + x][left_col + y] == pattern[x][y]) similarity++;
        }
    }
    return similarity;
}

template <const int rows, const int cols, const int pattern_rows, const int pattern_cols> bool hasPattern(const bool colony[rows][cols], bool pattern[pattern_rows][pattern_cols], int& row, int& col) {
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

void PrintColony(const bool Colony[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
		    std::cout << (Colony[i][j] ? "X" : ".");
		}
		std::cout << std::endl;
	}
}

int main()
{
	int x = 0, y = 0;
	PrintColony(Colony);
	bool p1 = hasPattern<N, N, 3, 4>(Colony, pattern1, x, y);
	if (p1) {
        std::cout << "Pattern1 se vyskytuje na: " << x << " " << y << std::endl;
	} else {
        std::cout << "Pattern1 se nevyskytuje - vraceno: " << x << " " << y << std::endl;
	}

	return 0;
}
