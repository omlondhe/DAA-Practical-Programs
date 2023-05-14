#include<iostream>
#include<vector>
using namespace std;

void printBoard(int n, vector<vector<char>>& board) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << (board[i][j] == 'Q' ? 'Q' : '-') << " ";
        cout << "\n";
    }
    cout << "\n";
}
bool isSafe(int n, int row, int col, vector<vector<char>>& board) {
    int leftCol = col - 1;
    int rightCol = col + 1;
    row--;

    while (row >= 0) {
        if (board[row][col] == 'Q') return false;
        if (leftCol >= 0 && board[row][leftCol] == 'Q') return false;
        if (rightCol < n && board[row][rightCol] == 'Q') return false;
        leftCol--; row--; rightCol++;
    }

    return true;
}
void nQueens(int row, int n, vector<vector<char>>& board) {
    if (row == n) {
        printBoard(n, board);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(n, row, col, board)) {
            board[row][col] = 'Q';
            nQueens(row + 1, n, board);
            board[row][col] = '0';
        }
    }
}
void nQueens(int n) {
    vector<vector<char>> board(n, vector<char>(n, '0'));
    nQueens(0, n, board);
}

int main() {
    int n;
    nQueens(5);
    return 0;
}
