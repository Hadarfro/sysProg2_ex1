/*
 * Author: Hadar Froimowich.
 * ID: 213118458
 * Email: hadarfro12@gmail.com
 */
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include "Algorithms.hpp"
#include "Graph.hpp"
const int INF = numeric_limits<int>::max(); // infinity

using namespace std;
using namespace ariel;


namespace Algorithms {
    
    int isConnected(ariel::graph g){//done
        vector<int>::size_type n = (vector<int>::size_type)g.getV();
        if(g.getV() == 0){
            cout << "the graph is connected" << endl;
            return true;
        }
        // Initialize visited array
        vector<bool> visited(n, false);

        // Perform BFS from vertex 0
        queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            vector<int>::size_type u = (vector<int>::size_type)q.front();
            q.pop();
            
            // Visit all neighbors of u
            for (vector<int>::size_type v = 0; v < n; v++) {
                if (g.getAdjMat()[u][v] != 0 && !visited[v]) {
                    q.push(v);
                    visited[v] = true;
                }
            }
        }

        // Check if all vertices were visited
        for (vector<int>::size_type v = 0; v < n; v++) {
            if (!visited[v]) {
                cout << "the graph is not connected" << endl;
                return false; // Graph is not connected
            }
        }
        cout << "the graph is connected" << endl;
        return true; // Graph is connected
    }

    int shortestPath(ariel::graph g,std::vector<int>::size_type start,std::vector<int>::size_type end){//done
        vector<int>::size_type n = (vector<int>::size_type)g.getV();
        if(start == end){
            return 0;
        }
        // Initialize distances with infinity
        vector<int> dist(n, INF);
        dist[start] = 0;

        // Relax edges repeatedly n-1 times
        for (vector<int>::size_type i = 0; i < n - 1; i++) {
            for (vector<int>::size_type u = 0; u < n; u++) {
                for (vector<int>::size_type v = 0; v < n; ++v) {
                    if (g.getAdjMat()[u][v] != 0 && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.getAdjMat()[u][v]; // Relax edge
                    }
                }
            }
        }

        // Check for negative cycles
        for (vector<int>::size_type u = 0; u < n; ++u){
            for (vector<int>::size_type v = 0; v < n; ++v){
                if (g.getAdjMat()[u][v] != 0 && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                    // Negative cycle detected
                    cout << "Graph contains negative cycle." << endl;
                    return -1;
                }
            }
        }

        // Reconstruct the shortest path
        vector<int> shortestPath;
        vector<int>::size_type cur = (vector<int>::size_type)end;
        if(dist[cur] == INF){
            cout << "there is no path" << endl;
            return -1;
        }
        while (cur != start){
            shortestPath.push_back(cur);
            for (vector<int>::size_type v = 0 ; v < n ; ++v) {
                
                if (g.getAdjMat()[v][cur] != INF && dist[v] != INF && dist[cur] == dist[v] + g.getAdjMat()[v][cur]) {
                    cur = v;
                    break;
                } 
            }
        }
        shortestPath.push_back(start);
        reverse(shortestPath.begin(), shortestPath.end());
        int count = 0;
        if (!shortestPath.empty()) {
            cout << "Shortest path from " << start << " to " << end << ": ";
            for (vector<int>::size_type i = 0; i < shortestPath.size(); ++i) {
                cout << shortestPath[i];
                count = shortestPath[i];
                if (i < shortestPath.size() - 1){
                    cout << " -> ";
                }
            }
            cout << endl;
        }
        return count;
    }

    bool hasCycleDFS( vector<vector<int>> graph, vector<int>::size_type u, vector<int>::size_type parent, vector<bool>& visited,vector<int>& cycleVertices) {
        visited[u] = true;
        cycleVertices.push_back(u); // Add current vertex to the cycle

        for (size_t v = 0; v < graph.size(); ++v) {
             if (graph[u][v]) {
                if (!visited[v]) {
                    if (hasCycleDFS(graph, v, u, visited, cycleVertices)) {
                        return true;
                    }
                } else if (v != parent) {
                    // Back edge detected, indicating a cycle
                    cout << "Cycle detected: ";
                    for (size_t i = 0; i < cycleVertices.size(); ++i) {
                        cout << cycleVertices[i];
                        if (i < cycleVertices.size() - 1) {
                            cout << " -> ";
                        }
                    }
                    cout << endl;
                    return true;
                }
            }
        }
        // Remove current vertex from the cycle before backtracking
        cycleVertices.pop_back();
        return false;
    }

    int isContainsCycle(ariel::graph g){//not working need to fix!!!!!!!!!
        vector<int>::size_type n = (vector<int>::size_type)g.getV();
        vector<bool> visited(n, false);
        vector<int> cycleVertices;
        for (vector<int>::size_type u = 0; u < n; ++u) {
            if (!visited[u] && hasCycleDFS(g.getAdjMat(), u, (vector<int>::size_type)-1, visited,cycleVertices)){
                cout << "the graph Contains Cycle" << endl;
                return true;
            }
        }
        cout << "the graph is not Contains Cycle" << endl;
        return false;
    }

    int isBipartite(ariel::graph g){//done
        vector<int>::size_type n = (vector<int>::size_type)g.getV();
        vector<int> colors(n, -1); // Initialize all vertices with no color
        vector<unordered_set<int>> groups(2); // Two groups of vertices

        // Perform BFS to color vertices and check bipartiteness
        for (vector<int>::size_type i = 0; i < n; ++i) {
            if (colors[i] != -1){ 
                continue; // Skip already colored vertices
            }
            colors[i] = 0; // Color the starting vertex with 0
            groups[0].insert(i); // Add it to the first group
            queue<int> q;
            q.push(i);
            while(!q.empty()){
                vector<int>::size_type u = (vector<int>::size_type)q.front();
                q.pop();
                for (vector<int>::size_type v = 0; v < n; ++v) {
                    if (g.getAdjMat()[u][v] != 0) {
                        if (colors[v] == -1) {
                            colors[v] = 1 - colors[u]; // Color opposite to u
                            groups[(vector<int>::size_type)colors[v]].insert(v); // Add to corresponding group
                            q.push(v);
                        } 
                        else if (colors[v] == colors[u]) {
                            cout << "Graph is not bipartite" << endl;
                            return false; // Graph is not bipartite
                        }
                    }
                }
            }
        }

        // Print the two groups of vertices if the graph is bipartite
        cout << "Group 1: ";
        for (int vertex : groups[0]) {
            cout << vertex << " ";
        }
        cout << endl;

        cout << "Group 2: ";
        for (int vertex : groups[1]) {
            cout << vertex << " ";
        }
        cout << endl;

        return true; // Graph is bipartite
    }

    int negativeCycle(ariel::graph g){//done
        vector<int>::size_type n = (vector<int>::size_type)g.getV();

        // Initialize distances with infinity
        vector<int> dist(n, INF);
        dist[0] = 0;
        // Relax edges repeatedly
        for (vector<int>::size_type i = 0; i < n - 1; ++i) {
            for (vector<int>::size_type u = 0; u < n; ++u) {
                for (vector<int>::size_type v = 0; v < n; ++v) {
                    if (g.getAdjMat()[u][v] != 0 && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.getAdjMat()[u][v]; // Relax edge
                    }
                }
            }
        }

        // Check for negative cycles
        for (vector<int>::size_type u = 0; u < n; ++u) {
            for (vector<int>::size_type v = 0; v < n; ++v) {
                if (g.getAdjMat()[u][v] != 0 && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                    // Negative cycle detected
                    cout << "Graph contains negative cycle." << endl;
                    return true;
                }
            }
        }
        cout << "false" << endl;
        return false;
    }
}