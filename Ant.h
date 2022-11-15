//
// Created by joseph on 11/15/22.
//

#ifndef QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
#define QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H

#include <random>
#include "Graph.h"

class Ant {
private:

    Graph graph;
    std::vector<int> tabuList;
    std::vector<int> remainingFacilities;

    std::discrete_distribution<> distribution( );

    void traverseGraph();

    void addPheromone(std::vector<std::vector<float>> pheromone);

public:
    Ant(Graph graph1);



};


#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
