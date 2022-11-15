#include "Graph.h"

#include <random>
#include <iostream>

using namespace std;

#define MAX_EVALUATIONS 10000;


int main() {

    //Placeholder Variables
    int numberOfAnts = 5;

    Graph graph;

    std::cout << graph.getDistance(1, 4);

    std::random_device device;
    std::mt19937 gen(device());


    return 0;
}
