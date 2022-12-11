#include "Graph.h"
#include "Ant.h"

#include <iostream>


#define MAX_EVALUATIONS 10000;


int main() {
    Graph Graph1;
    Ant Ant1(&Graph1);
    Ant1.testTraverseGraph();

    return 0;
}
