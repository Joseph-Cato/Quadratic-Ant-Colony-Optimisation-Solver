//
// Created by joseph on 11/15/22.
//

#ifndef QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
#define QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H

#include <random>
#include <thread>
#include <time.h>
#include "Graph.h"

class Ant {
private:

    Graph graph;
    std::vector<int> tabuList;

    void traverseGraph();

    void addPheromone(std::vector<std::vector<float>> pheromone);

public:
    Ant(Graph graph1);

    static std::vector<std::vector<float>> copyFloatVector(std::vector<std::vector<double>>);

};


#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
