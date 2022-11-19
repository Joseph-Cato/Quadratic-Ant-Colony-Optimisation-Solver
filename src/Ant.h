//
// Created by joseph on 11/15/22.
//

#ifndef QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
#define QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H

#include <random>
#include <thread>
#include <ctime>
#include "Graph.h"

class Ant {
private:

    Graph *graph;
    std::vector<int> tabuList;
    std::vector<double> weights;
    void traverseGraph();

    void addPheromone(std::vector<std::vector<float>> pheromone);

public:
    explicit Ant(Graph *graph1);

    [[nodiscard]] std::vector<int> getTabuList();

    void testTraverseGraph(); //TODO - remove

};


#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
