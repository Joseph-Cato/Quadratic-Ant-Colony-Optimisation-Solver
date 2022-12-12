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


public:

    std::vector<std::vector<float>> pheromoneAddition;

    explicit Ant(Graph *graph1);

    void traverseGraph();

    [[nodiscard]] std::vector<int> getTabuList();

    void addPheromone(std::vector<std::vector<float>> pheromone);

    float calculateInverseCost();

    void updatePheromone(float inverseCost);

};



#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
