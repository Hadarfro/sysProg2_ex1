#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "Algorithms.hpp"
#include "Graph.hpp"

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
        std::vector<int>::size_type numVertices = (std::vector<int>::size_type)g.getV();

        // Queue for BFS traversal
        std::queue<int> q;

        // Array to keep track of visited vertices
        std::vector<bool> visited(numVertices, false);

        // Array to keep track of distances from startVertex
        std::vector<int> distance(numVertices, std::numeric_limits<int>::max());

        // Enqueue the startVertex and mark it as visited with distance 0
        q.push(start);
        visited[start] = true;
        distance[start] = 0;

        // Perform BFS
        while (!q.empty()) {
            std::vector<int>::size_type u = (std::vector<int>::size_type)q.front();
            q.pop();

            if (u == end) {
                // Print the shortest path
                std::cout << "Shortest path between " << start << " and " << end << " is: ";
                std::cout << u;
                std::vector<int>::size_type parent = (std::vector<int>::size_type)distance[u];
                while (parent != start) {
                    std::cout << " <- " << parent;
                    parent = (std::vector<int>::size_type)distance[parent];
                }
                std::cout << " <- " << start << std::endl;
                return 1; // Return the destination vertex
            }

            // Visit all adjacent vertices of u
            for (std::vector<int>::size_type v = 0; v < numVertices; ++v) {
                 // Check if v is adjacent to u and not visited yet
                if (g.getAdjMat()[u][v] && !visited[v]) {
                    // Enqueue v, mark it as visited, and update its distance
                    q.push(v);
                    visited[v] = true;
                    distance[v] = u;
                }
            }
        }

        // If endVertex is unreachable from startVertex, return -1
        return -1;
        }

        int isContainsCycle(ariel::graph g){//problem!!!!!!!!!!!!!!!!
            // std::vector<int>::size_type v = (std::vector<int>::size_type)g.getV();
            // std::vector<int> parent(v, -1);
            // std::vector<bool> visited(v, false);
            // std::vector<int> cyclePath; // Vector to store the cycle path

            // for (std::vector<int>::size_type u = 0; u < v; ++u){
            //     // If vertex u is not visited, perform DFS traversal from u
            //     if (!visited[u]) {
            //         // if (g.DFSFindCycle(g.getAdjMat(), u, -1, visited, cyclePath)) {
            //         //     // If a cycle is found, print the cycle path
            //         //     std::cout << "Cycle found: ";
            //         //     for (int vertex : cyclePath) {
            //         //         std::cout << vertex << " ";
            //         //     }
            //         //     std::cout << std::endl;
            //         //     return 1; // Return 1 to indicate a cycle is found
            //         // }
            //     }
            // }
        return 0;
    }

    int isBipartite(ariel::graph g){
        // int n = g.getV();
        // vector<int> colors(n, -1); // Colors of vertices: -1 (unvisited), 0 and 1 (color groups)

        // for (int i = 0; i < n; ++i) {
        //     if (colors[i] == -1) { // If vertex i is unvisited, start BFS from it
        //         queue<int> q;
        //         q.push(i);
        //         colors[i] = 0; // Assign color 0 to vertex i

        //         while (!q.empty()) {
        //             int u = q.front();
        //             q.pop();

        //             for (int v = 0 ; i < n ;i++) {
        //                 if (colors[v] == -1) { // If vertex v is unvisited
        //                     colors[v] = 1 - colors[u]; // Assign opposite color to vertex v
        //                     q.push(v);
        //                 } 
        //                 else if (colors[v] == colors[u]) { // If adjacent vertices have the same color
        //                     return false; // Graph is not bipartite
        //                 }
        //             }
        //         }
        //     }
        // }

        return true; // Graph is bipartite
    }

    int negativeCycle(ariel::graph g){//do relax v times and check if in the last relax there was a change
        return 0;
    }
}