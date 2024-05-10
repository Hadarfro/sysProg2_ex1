#include "Graph.hpp"
#include <iostream>
#include <vector>

using namespace std; 
using namespace ariel;
struct Edge {
    int source, destination, weight;
};
namespace Algorithms{
    int isConnected(ariel::graph g);
    int shortestPath(ariel::graph g,std::vector<int>::size_type start,std::vector<int>::size_type end);
    int isContainsCycle(ariel::graph g);
    int isBipartite(ariel::graph g);
    int negativeCycle(ariel::graph g);
    bool hasCycleDFS( vector<vector<int>> graph, vector<int>::size_type u, vector<int>::size_type parent, vector<bool>& visited);
};
