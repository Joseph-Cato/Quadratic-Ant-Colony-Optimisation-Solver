//
// Created by joseph on 11/15/22.
//

#ifndef QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H
#define QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H

#include <vector>
#include <mutex>

class Graph {
private:

    std::vector<std::vector<double>> pheromone;
    std::vector<double> initialPheromone;
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<int>> flows;
    std::vector<std::vector<double>> heuristicMatrix;
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

    [[nodiscard]] const std::vector<double> & getInitialPheromone();

    [[nodiscard]] int & getDistance(int startLocation, int endLocation);

    [[nodiscard]] const int & getFlow(int startFacility, int endFacility);

    [[nodiscard]] const int & getNumberOfLocations();

    [[nodiscard]] const std::vector<std::vector<double>> & getHeuristicMatrix();

    void addPheromone(std::vector<std::vector<float>> pheromoneAddition);

    [[nodiscard]] const double & getPheromone(int fromNode, int destinationNode);

    /*
    void printDistances() { //Testing func
        for (int i = 0; i < numberOfLocations; i++) {
            for (int j = 0; j < numberOfLocations; j++) {
                std::cout << getDistance(i,j) << " ";
            }
            std::cout << "\n";
        }
    }

    void printFlows() { //Testing fun
        for (int i = 0; i < numberOfLocations; i++) {
            for (int j = 0; j < numberOfLocations; j++) {
                std::cout << getFlow(i,j) << " ";
            }
            std::cout << "\n";
        }
    }
     */

};


#endif //QUADRATIC_ANT_COLONY_OPTIMISATION_SOLVER_GRAPH_H
