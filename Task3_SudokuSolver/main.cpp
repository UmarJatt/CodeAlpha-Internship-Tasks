#include <iostream>
#include <vector>

using namespace std;

// Print the Sudoku board
void printSudoku(int board[9][9]) {
    cout << "----------------------" << endl;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            cout << board[r][c] << " ";
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
}

// Check if a number can be placed at a position
bool canPlace(int board[9][9], int row, int col, int num) {
    // Check row
    for (int i = 0; i < 9; i++)
        if (board[row][i] == num) return false;

    // Check column
    for (int i = 0; i < 9; i++)
        if (board[i][col] == num) return false;

    // Check 3x3 subgrid
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num) return false;

    return true;
}

// Find all numbers that can be placed at a position
vector<int> findPlaceable(int board[9][9], int row, int col) {
    vector<int> candidates;
    for (int i = 1; i <= 9; i++)
        if (canPlace(board, row, col, i))
            candidates.push_back(i);
    return candidates;
}

// Find the next empty cell
bool findNextEmptyCell(int board[9][9], int &row, int &col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (board[row][col] == 0)
                return true; // Found an empty cell
    return false; // No empty cells
}

// Solve Sudoku using backtracking
bool solveSudoku(int board[9][9]) {
    int row, col;
    if (!findNextEmptyCell(board, row, col))
        return true; // Puzzle solved

    vector<int> candidates = findPlaceable(board, row, col);
    for (int num : candidates) {
        board[row][col] = num;
        if (solveSudoku(board)) return true;
        board[row][col] = 0; // Backtrack
    }
    return false; // No solution found
}

int main() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "🧩 Original Sudoku:" << endl;
    printSudoku(board);

    if (solveSudoku(board)) {
        cout << "🎉 Sudoku solved!" << endl;
        printSudoku(board);
    } else {
        cout << "❌ No solution found." << endl;
    }

    return 0;
}