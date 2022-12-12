//
// Created by joseph on 11/15/22.
//

#include <fstream>
#include <random>
#include <sstream>
#include <iostream>
#include "Graph.h"

std::mutex Graph::pheromoneMutex;

const std::vector<std::vector<float>> & Graph::getHeuristicMatrix() {
    return Graph::heuristicMatrix;
}

Graph::Graph() : Graph("/home/joseph/Documents/QACO/res/dataSet.txt", 2, 1){
}

Graph::Graph(const std::string& filePath, double ALPHA_VALUE, double BETA_VALUE) {

    pheromone.clear();

    ALPHA = ALPHA_VALUE;
    BETA = BETA_VALUE;

    std::vector<int> temp;
    int lineCounter = 0;

    std::fstream file;
    file.open(filePath, std::ios::in);

    if (file.is_open()) {

        std::string line;
        while (std::getline(file, line)) {
            if (lineCounter == 0) {
                temp = lineToVector(line);
                numberOfLocations = temp.front();
                lineCounter++;

            } else if (lineCounter > 1 && lineCounter < numberOfLocations + 2) {
                temp = lineToVector(line);
                distances.emplace_back(temp);
                lineCounter++;

            } else if (lineCounter > numberOfLocations + 2) {
                temp = lineToVector(line);
                flows.emplace_back(temp);
                lineCounter++;

            } else {
                lineCounter++;
            }
        }
    } else {
        throw std::runtime_error("FATAL: File could not be opened.");
    }

    file.close();

    pheromone.clear();

    //TODO combine for loop below into one?

    // Generating initial pheromone levels
    std::vector<float> pheromoneRow;

    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            if (i != j) {
                pheromoneRow.emplace_back(1);
            } else {
                pheromoneRow.emplace_back(0);
            }
        }
        pheromone.emplace_back(pheromoneRow);
        pheromoneRow.clear();
    }

    for (int i = 0; i < numberOfLocations; i++) {
        initialPheromone.emplace_back(1);
    }

    // Generating Heuristic Matrix
    std::vector<float> heuristicRow;

    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            if (i == j) {
                heuristicRow.emplace_back(0);
            } else {
                double distance = distances.at(i).at(j);
                if (distance == 0) {
                    heuristicRow.emplace_back(0);
                } else {
                    heuristicRow.emplace_back((float) (1.0 / distances.at(i).at(j)));
                }
            }
        }
        heuristicMatrix.emplace_back(heuristicRow);
        heuristicRow.clear();
    }

    // Generating partial pheromone
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

std::vector<int> Graph::lineToVector(const std::string& string) {
    std::vector<int> vector;
    std::istringstream reader(string);
    do
    {
        // read as many numbers as possible.
        for (int number; reader >> number;) {
            vector.push_back(number);
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

void Graph::addPheromone() { //TODO - could just add pheromone from ant::updatePheromone
    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            pheromone.at(i).at(j) += partialPheromone.at(i).at(j);
        }
    }
}

void Graph::evaporatePheromone(float evapRate) {
    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            pheromone[i][j] = pheromone[i][j] * (1-evapRate);
        }
    }
}

void Graph::addPartialPheromone(float inverseCost, std::vector<int> tabuList) {

    for (int i = 0; i < (int) tabuList.size(); i += 2) {
        partialPheromone[ tabuList[i] ][ tabuList[i+1] ] += inverseCost;
    }

}

std::vector<std::vector<float>> Graph::getPartialPheromone() {
    return partialPheromone;
}
