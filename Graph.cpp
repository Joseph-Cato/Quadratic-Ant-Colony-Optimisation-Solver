//
// Created by joseph on 11/15/22.
//

#include <fstream>
#include <random>
#include <sstream>
#include "Graph.h"

std::mutex Graph::pheromoneMutex;

Graph::Graph() {
    std::vector<int> temp;
    int lineCounter = 0;

    std::fstream file;
    file.open("../dataSet.txt", std::ios::in);

    if (file.is_open()) {

        std::string line;
        while (std::getline(file, line)) {
            if (lineCounter == 0) {
                temp = lineToVector(line);
                numberOfLocations = temp.front();
                numberOfFacilities = numberOfLocations;
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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> realDistribution(0.0,1.0);
    std::vector<double> pheromoneRow;

    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j < numberOfLocations; j++) {
            pheromoneRow.emplace_back( realDistribution(generator) );
        }
        pheromone.emplace_back(pheromoneRow);
        pheromoneRow.clear();
    }

};

std::vector<int> Graph::lineToVector(std::string string) {
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

};

int Graph::getDistance(int startLocation, int endLocation) {
    return Graph::distances.at(startLocation).at(endLocation);
}

int Graph::getFlow(int startFacility, int endFacility) {
    return flows.at(startFacility).at(endFacility);
}

int Graph::getNumberOfLocations() {
    return numberOfLocations;
}

void Graph::addPheromone(std::vector<std::vector<float>> pheromoneAddition) {
    for (int i = 0; i < numberOfLocations; i++) {
        for (int j = 0; j <numberOfLocations; j++) {
            float newPheromoneValue = pheromone.at(i).at(j) + pheromoneAddition.at(i).at(j);
            pheromone.at(i).at(j) = newPheromoneValue;
        }
    }
}