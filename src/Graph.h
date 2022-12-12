//
// Created by joseph on 11/15/22.
//

#ifndef QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H
#define QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H

#include <vector>
#include <mutex>

class Graph {
private:

    std::vector<std::vector<float>> pheromone;
    std::vector<std::vector<float>> partialPheromone;
    std::vector<float> initialPheromone;
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<int>> flows;
    std::vector<std::vector<float>> heuristicMatrix;
    double ALPHA;
    double BETA;
    int numberOfLocations; // == numberOfFacilities



    static std::vector<int> lineToVector(const std::string& string);


public:

    static std::mutex pheromoneMutex;

    Graph();
    Graph(const std::string& filePath, double ALPHA_VALUE, double BETA_VALUE);

    [[nodiscard]] double getALPHA() const;

    [[nodiscard]] double getBETA() const;

    [[nodiscard]] const std::vector<float> & getInitialPheromone();

    [[nodiscard]] int & getDistance(int startLocation, int endLocation);

    [[nodiscard]] const int & getFlow(int startFacility, int endFacility);

    [[nodiscard]] const int & getNumberOfLocations() const;

    [[nodiscard]] const std::vector<std::vector<float>> & getHeuristicMatrix();

    void addPartialPheromone(std::vector<std::vector<float>> pheromoneAddition);

    [[nodiscard]] float getPheromone(int fromNode, int destinationNode);

    void evaporatePheromone(float evapRate);

    std::vector<std::vector<float>> getPartialPheromone();

    void addPheromone(std::vector<std::vector<float>> pheromoneAddition);

};


#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H
