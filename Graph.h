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
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<int>> flows;
    int numberOfLocations;
    int numberOfFacilities;

    static std::vector<int> lineToVector(std::string string);



public:

    static std::mutex pheromoneMutex;

    Graph();

    int getDistance(int startLocation, int endLocation);

    int getFlow(int startFacility, int endFacility);

    int getNumberOfLocations();

    void addPheromone(std::vector<std::vector<float>> pheromoneAddition);

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
