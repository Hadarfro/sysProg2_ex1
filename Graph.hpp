#include <iostream>
#include <vector>
#ifndef GRAPH_HPP
#define GRAPH_HPP

using namespace std; 
enum class State { UNDISCOVERED, DISCOVERED, PROCESSED };
namespace ariel{
    class graph{
        private:
            int V; // Number of vertices
            vector<vector<int>> adjMat; // Adjacency matrix that represent the edges of the graph

        public:
            
            graph();
            ~graph();
            int printPath(std::vector<int>& parent, unsigned int u);
            void loadGraph(vector<vector<int>> g);
            void printGraph();
            void DFS(unsigned int v, bool visited[]);
            int getV();
            vector<vector<int>> getAdjMat();
            bool hasCycleDFS(unsigned int node, vector<vector<int>>& graph, vector<State>& state);
    };
};
#endif // GRAPH_HPP