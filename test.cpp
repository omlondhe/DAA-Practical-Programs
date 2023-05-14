#include <bits/stdc++.h>
using namespace std;

void print(int n, int arr[]) { for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }

// Merge Sort
void merge(int start1, int end1, int end2, int arr[]) {
    const int n = end1 - start1 + end2 - end1 + 3;
    int temp[n];
    int k = 0;
    int i = start1;
    int j = end1 + 1;

    while (i <= end1 || j <= end2) {
        if (i <= end1 && j <= end2) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        } else if (i <= end1) temp[k++] = arr[i++];
        else if (j <= end2) temp[k++] = arr[j++];
    }

    for (int i = start1, j = 0; i <= end2; i++, j++) arr[i] = temp[j];
}

void mergeSort(int start, int end, int arr[]) {
    if (start >= end) return;
    int mid = start + ((end - start) >> 1);
    mergeSort(start, mid, arr);
    mergeSort(mid + 1, end, arr);
    merge(start, mid, end, arr);
}

// Quick Sort
int getPivot(int start, int end, int arr[]) {
    int pivot = start;
    int i = start + 1;
    int j = end;

    while (i <= j) {
        if (i < arr[pivot]) i++;
        else if (j >= arr[pivot]) j--;
        else swap(arr[i], arr[j]);
    }

    swap(arr[pivot], arr[j]);
    return j;
}
void quickSort(int start, int end, int arr[]) {
    if (start >= end) return;
    int pivot = getPivot(start, end, arr);
    quickSort(start, pivot - 1, arr);
    quickSort(pivot + 1, end, arr);
}

// N Queens
// void printBoard(int n, vector<vector<char>>& board) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) cout << (board[i][j] == 'Q' ? 'Q' : '-') << " ";
//         cout << "\n";
//     }
//     cout << "\n";
// }
// bool isSafe(int n, int row, int col, vector<vector<char>>& board) {
//     int leftCol = col - 1;
//     int rightCol = col + 1;
//     row--;

//     while (row >= 0) {
//         if (board[row][col] == 'Q') return false;
//         if (leftCol >= 0 && board[row][leftCol] == 'Q') return false;
//         if (rightCol < n && board[row][rightCol] == 'Q') return false;
//         leftCol--; row--; rightCol++;
//     }

//     return true;
// }
// void nQueens(int row, int n, vector<vector<char>>& board) {
//     if (row == n) {
//         printBoard(n, board);
//         return;
//     }

//     for (int col = 0; col < n; col++) {
//         if (isSafe(n, row, col, board)) {
//             board[row][col] = 'Q';
//             nQueens(row + 1, n, board);
//             board[row][col] = '0';
//         }
//     }
// }
// void nQueens(int n) {
//     vector board(n, vector<char>(n, '0'));
//     nQueens(0, n, board);
// }

// 0/1 KnapSack
// int knapsack(int index, int weight, int weights[], int costs[], vector<vector<int>>& memo) {
//     if (index == 0) return weights[index] <= weight ? costs[index] : 0; 
//     if (memo[index][weight] != -1) return memo[index][weight];

//     int pick = (weights[index] <= weight) ? knapsack(index - 1, weight - weights[index], weights, costs, memo) + costs[index] : 0;
//     int skip = knapsack(index - 1, weight, weights, costs, memo);
//     return memo[index][weight] = max(pick, skip);
// }
// void knapsack(int n, int weight, int weights[], int costs[]) {
//     vector memo(n, vector<int>(weight + 1, -1));
//     cout << knapsack(n - 1, weight, weights, costs, memo);
// }

// TSP Branch and Bound
const int INF = INT_MAX;
void printMatrix(int n, vector<vector<int>>& matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << (matrix[i][j] == INF ? "∞" : to_string((int)matrix[i][j])) << " ";
        cout << "\n";
    }
    cout << "------------\n";
}
class Node {
    public:
        int val;
        int cost;
        vector<int> path;
        unordered_set<int> set;
        vector<vector<int>> matrix;
        Node(int val, int cost, vector<int> path, vector<vector<int>>& matrix) {
            this->val = val;
            this->cost = cost;
            this->path = path;
            this->matrix = matrix;
            this->set = unordered_set<int>(path.begin(), path.end());
        }
        void addPath(int node) { 
            path.push_back(node); 
            set.insert(node); 
        }
};
class compare {
    public:
        bool operator() (Node* a, Node* b) {
            return a->cost >= b->cost;
        }
};
Node* reduceMatrix(int n, int from, int to, Node* node) {
    int reductionCost = node->cost;
    vector<vector<int>> matrix = node->matrix;

    if (from != -1 && to != -1) {
        reductionCost += matrix[from][to];
        matrix[from][to] = matrix[to][from] = INF;
        for (int i = 0; i < n; i++) matrix[from][i] = matrix[i][to] = INF;
        for (int p: node->path) matrix[to][p] = INF;
    }

    for (int i = 0; i < n; i++) {
        int mini = *min_element(matrix[i].begin(), matrix[i].end());
        if (mini == INF) continue;
        reductionCost += mini;
        for (int j = 0; j < n; j++) matrix[i][j] -= ((matrix[i][j] == INF || matrix[i][j] == 0) ? 0 : mini);
    }
    
    for (int j = 0; j < n; j++) {
        int mini = INF;
        for (int i = 0; i < n; i++) mini = min(mini, matrix[i][j]);
        if (mini == INF) continue;
        reductionCost += mini;
        for (int i = 0; i < n; i++) matrix[i][j] -= ((matrix[i][j] == INF || matrix[i][j] == 0) ? 0 : mini);
    }
    
    node->cost = reductionCost >= INF ? 0 : reductionCost;
    node->matrix = matrix;
    node->addPath(to == -1 ? 0 : to);
    return node;
}
bool isLeaf(int n, vector<vector<int>>& matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (matrix[i][j] != INF) return false;
    }
    return true;
}
void printPath(vector<int>& path) {
    cout << "Path: ";
    for (int p: path) cout << p << " -> ";
    cout << path[0];
    cout << "\n";
}
void tspBB() {
    int n = 5;
    vector<vector<int>> matrix = {   
        {INF, 20, 30, 10, 11},
        {15, INF, 16, 04, 02},
        {03, 05, INF, 02, 04},
        {19, 06, 18, INF, 03},
        {16, 04, 07, 16, INF},
    };

    int upperBound = INF;
    priority_queue<Node*, vector<Node*>, compare> minHeap;
    minHeap.push(reduceMatrix(n, -1, -1, new Node(0, 0, {}, matrix)));

    while (!minHeap.empty()) {
        Node* node = minHeap.top(); 
        minHeap.pop();
        int val = node->val;
        int cost = node->cost;
        vector<int> path = node->path;
        unordered_set<int> set = node->set;
        vector<vector<int>> matrix = node->matrix;
        if (cost > upperBound) continue;

        for (int i = 0; i < n; i++) {
            if (set.count(i)) continue;
            Node* currentNode = reduceMatrix(n, val, i, new Node(i, cost, path, matrix));
            if (isLeaf(n, currentNode->matrix)) {
                upperBound = cost;
                path.push_back(i);
                printPath(path);
                path.pop_back();
                continue;
            }
            minHeap.push(currentNode);
        }
    }
}

// TSP Generative Algorithm

// Dining Philosopher problem

// Threaded Matrix Multiplication

int main() {
    int n = 10;
    int arr[] = { 3, 6, 2, 8, 9, 5, 4, 7, 2, 8 };
    
    int weight = 10;
    int weights[] = { 2, 5, 3, 8, 6 };
    int costs[] = { 5, 3, 8, 7, 1 };

    while (true) {
        int operation;
        cout << "\n\nWhat operation you want to perform?\n";
        cout << "1.\tMerge sort\n";
        cout << "2.\tQuick sort\n";
        cout << "3.\tN Queens\n";
        cout << "3.\t0/1 Knapsack\n";
        cout << "5.\tTSP Branch and Bound\n";
        cout << "6.\tTSP Generative Algorithm\n";
        cout << "7.\tDining philosopher\n";
        cout << "8.\tThreaded matrix multiplication\n";
        cin >> operation;

        switch (operation) {
            case 1:
                mergeSort(0, n - 1, arr);
                print(n, arr);
                break;
            
            case 2:
                quickSort(0, n - 1, arr);
                print(n, arr);
                break;
            
            case 3:
                // nQueens(5);
                break;
            
            case 4:
                // knapsack(5, weight, weights, costs);
                break;
            
            case 5:
                tspBB();
                break;
            
            default:
                return 0;
        }
    }
    
    return 0;
}