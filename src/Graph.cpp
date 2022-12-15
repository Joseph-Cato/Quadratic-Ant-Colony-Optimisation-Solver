//
// Created by joseph on 11/15/22.
//

#include <fstream>
#include <random>
#include <sstream>
#include <iostream>
#include "Graph.h"

std::mutex Graph::pheromoneMutex;

std::vector<int> Graph::lineToVector(const std::string& string) {
    std::vector<int> vector;
    std::istringstream reader(string);
    do
    {
        // read as many numbers as possible.
        for (int number; reader >> number;) {
            vector.emplace_back(number);
        }
        // consume and discard token from stream.
        if (reader.fail())
        {
            reader.clear();
            std::string token;
            reader >> token;
        }
    }
    while (!reader.eof());

    return vector;

}

const std::vector<std::vector<float>> & Graph::getHeuristicMatrix() {
    return Graph::heuristicMatrix;
}

Graph::Graph() : Graph("/home/joseph/Documents/QACO/res/dataSet.txt", 2, 1, false){
}

Graph::Graph(const std::string& filePath, double ALPHA_VALUE, double BETA_VALUE, bool heuristic) {

    pheromone.clear();

    // Set ALPHA and BETA instance variables
    ALPHA = ALPHA_VALUE;
    BETA = BETA_VALUE;

    std::vector<int> dataRow; /** Variable used to construct rows of matrices */
    int lineCounter = 0;

    // Opens file
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (file.is_open()) {
        // Parses lines based on how many lines there will be according to the first value specified
        std::string line;
        while (std::getline(file, line)) {
            if (lineCounter == 0) {
                // Gets number of locations/facilities (only one variable is used
                dataRow = lineToVector(line);
                numberOfLocations = dataRow.front();
                lineCounter++;

            } else if (lineCounter > 1 && lineCounter < numberOfLocations + 2) {
                // Gets distance matrix
                dataRow = lineToVector(line);
                distances.emplace_back(dataRow);
                lineCounter++;

            } else if (lineCounter > numberOfLocations + 2) {
                // Gets flow matrix
                dataRow = lineToVector(line);
                flows.emplace_back(dataRow);
                lineCounter++;

            } else {
                // Skips empty lines
                lineCounter++;
            }
        }
    } else {
        throw std::runtime_error("FATAL: Dataset file could not be opened.\n" + filePath);
    }

    file.close();

    pheromone.clear();

    // The three loops below could be combined into one if you need more speed generating graph object -
    // current implementation is more readable

    // Generating initial pheromone levels
    std::vector<float> pheromoneRow;

    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            if (i != j) {
                // Initial pheromone value is 0.5
                pheromoneRow.emplace_back(0.5);
            } else {
                // Node cannot be visited from same node so major diagonal is made up of zeros
                pheromoneRow.emplace_back(0);
            }
        }
        pheromone.emplace_back(pheromoneRow);
        pheromoneRow.clear();
    }

    for (int i = 0; i < numberOfLocations; i++) {
        initialPheromone.emplace_back(1);
    }
    for (int i = 0; i < numberOfLocations; i++) {
        initialPartialPheromone.emplace_back(0);
    }

    // Generating Heuristic Matrix
    std::vector<float> heuristicRow;

    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            if (i == j) {
                // Node cannot be visited from same node so major diagonal is made up of zeros
                heuristicRow.emplace_back(0);
            } else {
                auto distance = (float) distances.at(i).at(j);
                if (distance == 0) {
                    // Node cannot be visited from same node so major diagonal is made up of zeros
                    heuristicRow.emplace_back(0);
                } else {
                    // heuristic is calculated as 1 / distance - including flow gave worse results
                    if (heuristic) {
                        heuristicRow.emplace_back(1.0 / distance);
                    } else {
                        // Since 1^n for any n equals 1. This means the heuristic component will have no effect.
                        heuristicRow.emplace_back(1.0);
                    }
                }
            }

        }
        heuristicMatrix.emplace_back(heuristicRow);
        heuristicRow.clear();
    }

    // Generating partial pheromone - numberOfLocations*numberOfLocations zeros matrix
    std::vector<float> partialPheromoneRow;

    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            partialPheromoneRow.emplace_back(0);
        }
        partialPheromone.emplace_back(partialPheromoneRow);
        partialPheromoneRow.clear();
    }
}

double Graph::getBETA() const {
    return BETA;
}

double Graph::getALPHA() const {
    return ALPHA;
}

const std::vector<float> & Graph::getInitialPheromone() {
    return initialPheromone;
}

int & Graph::getDistance(int startLocation, int endLocation) {
    return Graph::distances.at(startLocation).at(endLocation);
}

const int & Graph::getFlow(int startFacility, int endFacility) {
    return flows.at(startFacility).at(endFacility);
}

float  Graph::getPheromone(int fromNode, int destinationNode) {
    return pheromone.at(fromNode).at(destinationNode);
}

const int & Graph::getNumberOfLocations() const {
    return numberOfLocations;
}

void Graph::addPartialPheromone(float inverseCost, std::vector<int> tabuList) {

    for (int i = 0; i < (int) tabuList.size(); i += 2) {
        partialPheromone[ tabuList[i] ][ tabuList[i+1] ] += inverseCost;
    }

}

void Graph::addInitialPartialPheromone(float inverseCost, int firstNode) {

    initialPartialPheromone[firstNode] += inverseCost;
}

void Graph::evaporatePheromone(float evapRate) {
    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            pheromone[i][j] = pheromone[i][j] * (1-evapRate);
        }
    }
}

void Graph::addPheromone() {
    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            pheromone.at(i).at(j) += partialPheromone.at(i).at(j);
        }
    }
}

void Graph::addInitialPheromone() {
    for (int i = 0; i < numberOfLocations; i++) {
        initialPheromone[i] += initialPartialPheromone[i];
    }
}
