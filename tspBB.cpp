#include <bits/stdc++.h>
using namespace std;

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

int main() {
    tspBB();
    return 0;
}