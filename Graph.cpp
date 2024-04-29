#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph{
private:
    int V; // Number of vertices
    int** adjMat; // Adjacency matrix that represent the edges of the graph

public:
    Graph(int v) : V(v) {
        // Dynamically allocate memory for the adjacency matrix
        adjMat = new int*[V];
        for (int i = 0; i < V; i++) {
            adjMat[i] = new int[V];
            // Initialize all elements to 0
            for (int j = 0; j < V; ++j) {
                adjMat[i][j] = 0;
            }
        }
    }
    // Destructor to deallocate memory
    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] adjMat[i];
        }
        delete[] adjMat;
    }

     // Function to add an edge to the graph
    void addEdge(int u, int v) {
        adjMat[u][v] = 1;
        adjMat[v][u] = 1; // If it's an undirected graph
    }

    // Function to build the neighbor matrix using BFS
    int** buildNeighborMatrix() {
        int** neighborMatrix = new int*[V];
        for (int i = 0; i < V; ++i) {
            neighborMatrix[i] = new int[V];
            // Initialize all elements to 0
            for (int j = 0; j < V; ++j) {
                neighborMatrix[i][j] = 0;
            }
        }

        // Perform BFS from each vertex
        for (int i = 0; i < V; ++i) {
            std::queue<int> q;
            bool* visited = new bool[V] {false};

            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v = 0; v < V; ++v) {
                    if (adjMat[u][v] == 1 && !visited[v]) {
                        neighborMatrix[i][v] = 1;
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }

            delete[] visited;
        }

        return neighborMatrix;
    }
    void loadGraph(vector<vector<int>> g){
        
    }
};

int main() { // Create a graph with 5 vertices
    Graph g(5);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Build the neighbor matrix
    int** neighborMatrix = g.buildNeighborMatrix();

    // Print the neighbor matrix
    std::cout << "Neighbor Matrix:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << neighborMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Deallocate memory for neighbor matrix
    for (int i = 0; i < 5; ++i) {
        delete[] neighborMatrix[i];
    }
    delete[] neighborMatrix;

    return 0;
}