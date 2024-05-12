/*
 * Author: Hadar Froimowich.
 * ID: 213118458
 * Email: hadarfro12@gmail.com
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include "Graph.hpp"

using namespace std;

    namespace ariel{
        graph::graph(){//defult constractor
            this->V = 0;

        }
        // Destructor to deallocate memory
        graph::~graph() {
            this->adjMat.clear();
        }

        // Depth-First Search (DFS)
        void graph::DFS(unsigned int v, bool visited[]) {
            visited[v] = true;
            for (unsigned int i = 0; i < V; ++i) {
                if (this->adjMat[v][i] && !visited[i]) {
                    DFS(i, visited);
                }
            }
        }

        int graph::printPath(std::vector<int>& parent, unsigned int u) {
            std::vector<int> path;
            unsigned int v = u;
            int t = (int)u;

            // Construct the cycle path
            do {
                path.push_back((int)v);
                t = parent[v];
                v = (unsigned int)t;
            } while (v != u && t != u);

            // Print the cycle
            std::cout << "Cycle: ";
            for (unsigned int i = path.size() - 1; i >= 0; --i) {
                std::cout << path[i] << " ";
            }
            std::cout << std::endl;
            return 1;
        }

        int graph::getV(){
            return this->V;
        }

        vector<vector<int>> graph::getAdjMat(){
            return this->adjMat;
        }

        void graph::loadGraph(vector<vector<int>> g) {
            // Reinitialize the current graph object with the new graph data
            if(g.size() != g[0].size()||g.size() == 0){
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix or is empty.");
            }
            this->V = g.size();
            this->adjMat = g;
        }

        void graph::printGraph(){//print the number of vertex and edges
            // Print the neighbor matrix
            int count = 0;
            for (unsigned int i = 0; i < this->V; ++i) {
                for (unsigned int j = 0; j < this->V; ++j) {
                    if(this->adjMat[i][j] != 0){
                        count++;
                    }
                }
            }
            cout << "Graph with " << this->V << " vertices and " << count << " edges" << endl;
        }
        
    };
