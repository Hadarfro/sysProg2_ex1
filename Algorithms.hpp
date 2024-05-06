#include "Graph.hpp"
#include <iostream>
#include <vector>

using namespace std; 
using namespace ariel;
namespace Algorithms{
    int isConnected(ariel::graph g);
    int shortestPath(ariel::graph g,int start,int end);
    int isContainsCycle(ariel::graph g);
    int isBipartite(ariel::graph g);
    int negativeCycle(ariel::graph g);
};
