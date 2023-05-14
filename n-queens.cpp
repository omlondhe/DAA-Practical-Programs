#include<iostream>
#include<vector>
using namespace std;

class NQueens {
    private: 
        int n;
        vector<vector<char>> arr;
        vector<vector<vector<char>>> ans;

    public:
        NQueens(int n) { 
            this->n = n;
            arr.resize(n, vector<char>(n, '0')); 
        }

        bool isSafe(int row, int col) {
            if (row >= n || col >= n) return false;

            int r = row - 1;
            int left = col - 1;
            int right = col + 1;

            while (r >= 0) {
                if (arr[r][col] == 'Q') return false;
                if (left >= 0 && arr[r][left] == 'Q') return false;
                if (right < n && arr[r][right] == 'Q') return false;
                r--;
                left--;
                right--;
            }

            return true;
        }

        void solve(int row) {
            if (row == n) {
                ans.push_back(arr);
                return;
            }

            for (int col = 0; col < n; col++) {
                if (isSafe(row, col)) {
                    arr[row][col] = 'Q';
                    solve(row + 1);
                    arr[row][col] = '0';
                }
            }
        }

        void print() {
            for (int i = 0; i < ans.size(); i++) {
                cout << "Solution " << i + 1 << ":\n";
                for (int k = 0; k < n; k++) cout << "----";
                cout << "\n";
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        cout << "| " << (ans[i][j][k] == 'Q' ? "Q" : " ") << (k == n - 1 ? " |" : " ");
                    }
                    cout << "\n";
                    for (int k = 0; k < n; k++) cout << "----";
                    cout << "\n";
                }
                cout << "\n";
            }
        }
};

int main() {
    int n;
    cout << "Enter the value of n:\t";
    cin >> n;

    NQueens *nQueens = new NQueens(n);
    nQueens->print();
    nQueens->solve(0);
    nQueens->print();

    return 0;
}
