#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <unordered_set>
#include "Algorithms.hpp"
#include "Graph.hpp"
const int INF = numeric_limits<int>::max(); // Represents infinity

using namespace std;
using namespace ariel;


namespace Algorithms{
    int isConnected(ariel::graph g){
        bool* visited = new bool[g.getV()]{false};
        // Start DFS from the first vertex
        g.DFS(0, visited);
        // Check if all vertices are connected
        for (std::vector<int>::size_type i = 0; i < g.getV(); i++){
            if (!visited[i]) {
                delete[] visited;
                cout<<"false"<<endl;
                return false;
            }
        }
        delete[] visited;
        cout<<"true"<<endl;
        return true;
    }

    int shortestPath(ariel::graph g,std::vector<int>::size_type start,std::vector<int>::size_type end){//use bellman-ford
        vector<int>::size_type n = (vector<int>::size_type)g.getV();

        // Initialize distances with infinity
        vector<int> dist(n, INF);
        dist[start] = 0;

        // Relax edges repeatedly n-1 times
        for (vector<int>::size_type i = 0; i < n - 1; ++i) {
            for (vector<int>::size_type u = 0; u < n; ++u) {
                for (vector<int>::size_type v = 0; v < n; ++v) {
                    if (g.getAdjMat()[u][v] != INF && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.getAdjMat()[u][v]; // Relax edge
                    }
                }
            }
        }

        // Check for negative cycles
        for (vector<int>::size_type u = 0; u < n; ++u) {
            for (vector<int>::size_type v = 0; v < n; ++v) {
                if (g.getAdjMat()[u][v] != INF && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                    // Negative cycle detected
                    cout << "Graph contains negative cycle." << endl;
                    return -1;
                }
            }
        }

        // Reconstruct the shortest path
        vector<int> shortestPath;
        vector<int>::size_type cur = (vector<int>::size_type)end;
        while (cur != start){
            shortestPath.push_back(cur);
            for (vector<int>::size_type v = 0; v < n; ++v) {
                if (g.getAdjMat()[v][cur] != INF && dist[cur] == dist[v] + g.getAdjMat()[v][cur]) {
                    cur = v;
                    break;
                }
            }
        }
        shortestPath.push_back(start);
        //reverse(shortestPath.begin(), shortestPath.end());
        if (!shortestPath.empty()) {
            cout << "Shortest path from " << start << " to " << end << ": ";
            for (vector<int>::size_type i = 0; i < shortestPath.size(); ++i) {
                cout << shortestPath[i];
                if (i < shortestPath.size() - 1){
                    cout << " <- ";
                }
            }
            cout << endl;
        }
        return 1;
    }

    bool hasCycleDFS( vector<vector<int>> graph, vector<int>::size_type u, vector<int>::size_type parent, vector<bool>& visited) {
        visited[u] = true;

        for (vector<int>::size_type v = 0; v < graph.size(); ++v) {
            if (graph[u][v] && !visited[v]) {
                if (hasCycleDFS(graph, v, u, visited))
                    return true;
            } else if (graph[u][v] && v != parent) {
                return true;
            }
        }

        return false;
    }

    int isContainsCycle(ariel::graph g){//not working need to fix!!!!!!!!!
        vector<int>::size_type n = (vector<int>::size_type)g.getV();
        vector<bool> visited(n, false);

        for (vector<int>::size_type u = 0; u < n; ++u) {
            if (!visited[u] && hasCycleDFS(g.getAdjMat(), u, (vector<int>::size_type)-1, visited))
                return true;
        }

        return false;
    }

    int isBipartite(ariel::graph g){//not working for bigger mat!!!!!!!!!!
        vector<int>::size_type n = (vector<int>::size_type)g.getV();
        vector<int> colors(n, -1); // Initialize all vertices with no color
        vector<unordered_set<int>> groups(2); // Two groups of vertices

        // Perform BFS to color vertices and check bipartiteness
        for (vector<int>::size_type i = 0; i < n; ++i) {
            if (colors[i] != -1) continue; // Skip already colored vertices
            colors[i] = 0; // Color the starting vertex with 0
            groups[0].insert(i); // Add it to the first group

            queue<int> q;
            q.push(i);

            while (!q.empty()) {
                vector<int>::size_type u = (vector<int>::size_type)q.front();
                q.pop();

                for (vector<int>::size_type v = 0; v < n; ++v) {
                    if (g.getAdjMat()[u][v] != 0) {
                        if (colors[v] == -1) {
                            colors[v] = 1 - colors[u]; // Color opposite to u
                            groups[(vector<int>::size_type)colors[v]].insert(v); // Add to corresponding group
                            q.push(v);
                        } else if (colors[v] == colors[u]) {
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

    int negativeCycle(ariel::graph g){//do relax v times and check if in the last relax there was a change
        vector<int>::size_type n = (vector<int>::size_type)g.getV();

        // Initialize distances with infinity
        vector<int> dist(n, INF);

        // Relax edges repeatedly
        for (vector<int>::size_type i = 0; i < n - 1; ++i) {
            for (vector<int>::size_type u = 0; u < n; ++u) {
                for (vector<int>::size_type v = 0; v < n; ++v) {
                    if (g.getAdjMat()[u][v] != INF && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.getAdjMat()[u][v]; // Relax edge
                    }
                }
            }
        }

        // Check for negative cycles
        for (vector<int>::size_type u = 0; u < n; ++u) {
            for (vector<int>::size_type v = 0; v < n; ++v) {
                if (g.getAdjMat()[u][v] != INF && dist[u] != INF && dist[u] + g.getAdjMat()[u][v] < dist[v]) {
                    // Negative cycle detected
                    cout << "Graph contains negative cycle." << endl;
                    return 1;
                }
            }
        }
        return 0;
    }
}