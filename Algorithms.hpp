/*
 * Author: Hadar Froimowich.
 * ID: 213118458
 * Email: hadarfro12@gmail.com
 */
#include "Graph.hpp"
#include <iostream>
#include <vector>

using namespace std; 
using namespace ariel;

namespace Algorithms{
    int isConnected(ariel::graph g);
    int shortestPath(ariel::graph g,size_t start,size_t end);
    int isContainsCycle(ariel::graph g);
    int isBipartite(ariel::graph g);
    int negativeCycle(ariel::graph g);
    bool hasCycleDFS( vector<vector<int>> graph, size_t u, size_t parent, vector<bool>& visited,vector<int>& cycleVertices);
};
