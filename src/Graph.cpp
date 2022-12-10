//
// Created by joseph on 11/15/22.
//

#include <fstream>
#include <random>
#include <sstream>
#include <iostream>
#include "Graph.h"

std::mutex Graph::pheromoneMutex;

const std::vector<std::vector<double>> & Graph::getHeuristicMatrix() {
    return Graph::heuristicMatrix;
}


Graph::Graph() : Graph("/home/joseph/Documents/QACO/res/dataSet.txt", 2, 1){
}

Graph::Graph(const std::string& filePath, double ALPHA_VALUE, double BETA_VALUE) {

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

    // Generating initial pheromone levels
    std::vector<double> pheromoneRow;

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
    std::vector<double> heuristicRow;

    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            if (i == j) {
                heuristicRow.emplace_back(0);
            } else {
                double distance = distances.at(i).at(j);
                if (distance == 0) {
                    heuristicRow.emplace_back(0);
                } else {
                    heuristicRow.emplace_back((double) 1.0 / distances.at(i).at(j));
                }
            }
        }
        heuristicMatrix.emplace_back(heuristicRow);
        heuristicRow.clear();
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

const std::vector<double> & Graph::getInitialPheromone() {
    return initialPheromone;
}

int & Graph::getDistance(int startLocation, int endLocation) {
    return Graph::distances.at(startLocation-1).at(endLocation-1);
}

const int & Graph::getFlow(int startFacility, int endFacility) {
    return flows.at(startFacility-1).at(endFacility-1);
}

const double & Graph::getPheromone(int fromNode, int destinationNode) {
    return pheromone[fromNode-1][destinationNode-1];
}

const int & Graph::getNumberOfLocations() {
    return numberOfLocations;
}

void Graph::addPheromone(std::vector<std::vector<float>> pheromoneAddition) {
    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j <numberOfLocations; j++) {
            double newPheromoneValue = pheromone.at(i).at(j) + pheromoneAddition.at(i).at(j);
            pheromone.at(i).at(j) = newPheromoneValue;
        }
    }
}