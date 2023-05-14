#include<iostream>
#include<bits/stdc++.h>

#define INF INT_MAX

using namespace std;

pair<int, vector<vector<int>>> reduceMatrix(int numberOfCities, vector<vector<int>> costMatrix) {
    int currentCost = 0;
    for(int i = 0; i < numberOfCities; i++) {
        int minVal = *min_element(costMatrix[i].begin(), costMatrix[i].end());
        if(minVal != INF) {
            currentCost += minVal;
            for(int j = 0; j < numberOfCities; j++) {
                if(costMatrix[i][j] != INF) costMatrix[i][j] -= minVal;
            }
        }
    }

    for(int i = 0; i < numberOfCities; i++) {
        int minVal = INF;
        for(int j = 0; j < numberOfCities; j++) {
            minVal = min(minVal, costMatrix[j][i]);
        }
        if(minVal != INF) {
            currentCost += minVal;
            for(int j = 0; j < numberOfCities; j++) {
                if(costMatrix[j][i] != INF) costMatrix[j][i] -= minVal;
            }
        }
    }

    return {currentCost, costMatrix};

}

void TSPLCBB(int numberOfCities, vector<vector<int>>& costMatrix) {
    pair<int, vector<vector<int>>> reducedMatrix = reduceMatrix(numberOfCities, costMatrix);
    priority_queue<pair<int, pair<vector<int>, vector<vector<int>>>>, vector<pair<int, pair<vector<int>, vector<vector<int>>>>>, greater<pair<int, pair<vector<int>, vector<vector<int>>>>>> pq;
    
    pq.push({reducedMatrix.first, {{0}, reducedMatrix.second}});
    
    while(!pq.empty()) {
        int currentCost = pq.top().first;
        vector<int> visitedCities = pq.top().second.first;
        vector<vector<int>> currentCostMatrix = pq.top().second.second;
        pq.pop();

        if(visitedCities.size() == numberOfCities){
            cout << endl << "Cost of Travelling: " << currentCost;
            cout << endl << "Path: 1";
            for(int k = 1; k < numberOfCities; k++) {
                cout << "->" << visitedCities[k]+1;
            }
            cout << "->1" << endl;
            cout << endl;
            continue;
        }

        for(int i = 0; i < numberOfCities; i++) {
            if(find(visitedCities.begin(), visitedCities.end(), i) == visitedCities.end()) {
                int newCurrentCost = currentCost;
                vector<int> newVisitedCities = visitedCities;
                vector<vector<int>> newCurrentMatrix = currentCostMatrix;
                int prevCity = visitedCities[visitedCities.size()-1];
                newCurrentMatrix[i][prevCity] = INF;
                newCurrentCost += newCurrentMatrix[prevCity][i];
                for(int j = 0; j < numberOfCities; j++) {
                    newCurrentMatrix[prevCity][j] = INF;
                    newCurrentMatrix[j][i] = INF;
                }
                newVisitedCities.push_back(i);
                pair<int, vector<vector<int>>> newReducedMatrix = reduceMatrix(numberOfCities, newCurrentMatrix);
                newCurrentCost += newReducedMatrix.first;
                pq.push({newCurrentCost,{newVisitedCities, newReducedMatrix.second}});
            }
        }
    }
}

int main() {
    // Default Test Cases:
    int numberOfCities = 5;
    vector<vector<int>> costMatrix = {   
        {INF, 20, 30, 10, 11},
        {15, INF, 16, 04, 02},
        {03, 05, INF, 02, 04},
        {19, 06, 18, INF, 03},
        {16, 04, 07, 16, INF},
    };

    TSPLCBB(numberOfCities, costMatrix);
    return 0;
}

/*
#include <iostream>
#include <algorithm>
using namespace std;

void tsp(int node, int cost, int minCost, int n, vector<bool>& visited, vector<int>& path, vector<int>& minPath, vector<vector<int>>& dist) {
    if (node == n) {
        // we have visited all nodes, update best path
        int newCost = cost + dist[path[n - 1]][path[0]];
        if (newCost < minCost) { minCost = newCost; minPath = path; }
        return;
    }

    // traverse all possible next nodes
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        int next_node = i;
        int next_cost = dist[path[node - 1]][next_node];
        if (cost + next_cost >= minCost) continue;

        // try this node
        path[node] = next_node;
        visited[next_node] = true;
        cost += next_cost;

        tsp(node + 1, cost, minCost, n, visited, path, minPath, dist);

        // backtrack
        visited[next_node] = false;
        cost -= next_cost;
    }
}

int main() {
    int n;
    cin >> n;

    int cost = 0;
    int minCost = 1e9;
    vector<bool> visited(n);
    vector<int> path(n), minPath(n);
    vector<vector<int>> dist(n, vector<int>(n));

    // read in distances
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> dist[i][j];

    // start from node 0
    path[0] = 0;
    visited[0] = true;

    tsp(1, cost, minCost, n, visited, path, minPath, dist);

    // output best path and cost
    cout << "Best Path: ";
    for (int i = 0; i < n; i++) cout << minPath[i] << " ";
    cout << "\nBest Cost: " << minCost << endl;

    return 0;
}



4
0 10 15 20
10 0 35 25 
15 35 0 30
20 25 30 0
*/
