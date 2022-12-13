
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

    std::vector<std::vector<float>> pheromoneAddition; // Stores pheromone additions from ants so evaporation can be done at any stage

    /** Creates Ant object.
     *
     * @param graph1 Memory address of graph object the ant will interact with
     */
    explicit Ant(Graph *graph1);

    /** \brief Ant picks nodes at random based on pheromone (and optionally heuristic) until entire graph is traversed.
     *
     * Creates local version of heuristicMatrix - this is so already visited nodes can be zeroed out.
     * Meaning the weight calculation equals 0.
     *
     * Uses std::discrete_distribution to pick the next node from a list of weights calculated by:
     * weight(i->j) = (pheromoneComponent(i->j)^alpha) * (heuristicComponent(i->j)^beta)
     *
     */
    void traverseGraph();

    /**
     *
     * @return [std::vector<int>] tabuList (list of vistited nodes in order)
     */
    [[nodiscard]] std::vector<int> getTabuList();

    /** Increments the partial pheromone matrix at visited connections by inverseCost.
     *
     * @param inverseCost increment value
     */
    void updatePartialPheromone(float inverseCost);

    /** Calulates cost of graph traversal by summing all node connections such that:
     *
     * cost(i->j) = distance(i->j) * flow (i->j)
     *
     * @return cost of Ant objects graph traversal
     */
    int getCost();

    /** Increments the initial partial pheromone vector at starting node by inverse cost.
     *
     * @param inverseCost increment value
     */
    void updateInitialPartialPheromone(float inverseCost);
};



#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_ANT_H
