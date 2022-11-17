#include "Graph.h"
#include "Ant.h"

#include <iostream>

using namespace std;

#define MAX_EVALUATIONS 10000;


int main() {
    Graph Graph1;
    Ant Ant1(&Graph1);
    Ant1.testTraverseGraph();

    double n = pow( (double) 1.0, (double) 2) * pow( (double) 0.025641, (double) 1.0);
    std::cout << "\n\n\n" << n;
    return 0;
}
