#include<bits/stdc++.h>
using namespace std;

// Recursion
int solveRecursion(int index, int weight, int profits[], int weights[]) {
    if (index == 0) return weights[index] <= weight ? profits[index] : 0;

    int take = 0;
    if (weights[index] <= weight) take = solveRecursion(index - 1, weight - weights[index], profits, weights) + profits[index];
    int notTake = solveRecursion(index - 1, weight, profits, weights);

    return max(take, notTake);
}

// Memoisation
int solveMemoization(int index, int weight, int profits[], int weights[], vector<vector<int>>& memo) {
    if (index == 0) return memo[index][weight] = weights[index] <= weight ? profits[index] : 0;
    if (memo[index][weight] != -1) return memo[index][weight];

    int take = 0;
    if (weights[index] <= weight) take = solveMemoization(index - 1, weight - weights[index], profits, weights, memo) + profits[index];
    int notTake = solveMemoization(index - 1, weight, profits, weights, memo);

    return memo[index][weight] = max(take, notTake);
}

// Tabulation
int solveTabulation(int n, int weight, int profits[], int weights[], vector<vector<int>>& dp) {
    for (int wt = 0; wt <= weight; wt++) {
        dp[0][wt] = weights[0] <= wt ? profits[0] : 0;
    }

    for (int index = 1; index < n; index++) {
        for (int wt = 0; wt <= weight; wt++) {
            int take = 0;
            if (weights[index] <= wt) take = dp[index - 1][wt - weights[index]]  + profits[index];
            int notTake = dp[index - 1][wt];
            dp[index][wt] = max(take, notTake);
        }
    }

    return dp[n - 1][weight];
}

// Space optimisation
int solveSpaceOptimisation(int n, int weight, int profits[], int weights[], vector<int>& prev) {
    vector<int> cur(weight + 1, 0);
    for (int wt = 0; wt <= weight; wt++) {
        prev[wt] = weights[0] <= wt ? profits[0] : 0;
    }

    for (int index = 1; index < n; index++) {
        for (int wt = 0; wt <= weight; wt++) {
            int take = 0;
            if (weights[index] <= wt) take = prev[wt - weights[index]]  + profits[index];
            int notTake = prev[wt];
            cur[wt] = max(take, notTake);
        }
        prev = cur;
    }

    return prev[weight];
}

int main() {
    clock_t start, end;

    cout << "Enter the number of items:\t";
    int n;
    cin >> n;

    cout << "Enter the weight capacity:\t";
    int weight;
    cin >> weight;

    cout << "Enter " << n << " profits:\n";
    int profits[n];
    for (int i = 0; i < n; i++) cin >> profits[i];

    cout << "Enter " << n << " weights:\n";
    int weights[n];
    for (int i = 0; i < n; i++) cin >> weights[i];

    cout << "\n";

    start = clock();
    int recursion = solveRecursion(n - 1, weight, profits, weights);
    end = clock();
    cout << "Result of Recursion: " << recursion << "\n";
    cout << "Time taken by Recursion: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms\n\n";

    start = clock();
    vector<vector<int>> memo(n, vector<int>(weight + 1, -1));
    int memoisation = solveMemoization(n - 1, weight, profits, weights, memo);
    end = clock();
    cout << "Result of Memoisation: " << memoisation << "\n";
    cout << "Time taken by Memoisation: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms\n\n";

    start = clock();
    vector<vector<int>> dp(n, vector<int>(weight + 1, 0));
    int tabulation = solveTabulation(n, weight, profits, weights, dp);
    end = clock();
    cout << "Result of Tabulation: " << tabulation << "\n";
    cout << "Time taken by Tabulation: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms\n\n";

    start = clock();
    vector<int> prev(weight + 1, 0);
    int spaceOptimisation = solveSpaceOptimisation(n, weight, profits, weights, prev);
    end = clock();
    cout << "Result of Space optimisation: " << spaceOptimisation << "\n";
    cout << "Time taken by Space optimisation: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms\n\n";

    return 0;
}

/**

6
10
20 5 10 40 15 25
1 2 3 8 7 4

*/
