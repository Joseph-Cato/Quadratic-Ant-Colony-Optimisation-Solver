//
// Created by joseph on 11/15/22.
//

#include <map>
#include <utility>
#include <iostream>
#include "Ant.h"

Ant::Ant(Graph *graph1 ){
    graph = graph1;
    tabuList.clear();
}

void Ant::traverseGraph() {
    //TODO - create more efficient sampler (discrete distribution without replacement) https://www.sciencedirect.com/science/article/abs/pii/S002001900500298X?via%3Dihub

    // Getting and configuring heuristic matrix
    std::vector<std::vector<float>> heuristicMatrix;
    heuristicMatrix = graph->getHeuristicMatrix();

    // Randomness
    static thread_local std::mt19937* randomGenerator = nullptr;
    if (!randomGenerator) {
        // Uses hashed thread ID + time to have unique seed for each run and each ant
        randomGenerator = new std::mt19937 ((std::hash<std::thread::id>{} (std::this_thread::get_id() ) ) + clock() );
    }

    // -------- First Step --------

    // Distribution for first traversal
    std::discrete_distribution<> firstDistribution( graph->getInitialPheromone().begin(),
                                                    graph->getInitialPheromone().end() );


    // First traversal from imaginary start node
    int firstNode = firstDistribution(*randomGenerator);
    tabuList.emplace_back(firstNode);


    // Zero out first node column of heuristic matrix so probability of returning to that node = 0
    for (int i = 0; i < graph->getNumberOfLocations(); i++) {
        heuristicMatrix[i][firstNode] = 0;
    }

    int lastNode = firstNode;


    // -------- Main Loop --------
    for (int iteration = 1; iteration < graph->getNumberOfLocations(); iteration++) {
        weights.clear();

        // calculate probabilities of going to another node
        for (int i = 0; i < graph->getNumberOfLocations(); i++) {
            double pheromoneComponent = pow( (double) graph->getPheromone(lastNode, i), (double) graph->getALPHA());
            double heuristicComponent = pow( heuristicMatrix[lastNode][i], (double) graph->getBETA() );
            double weight = pheromoneComponent * heuristicComponent;
            weights.emplace_back( weight );
        }

        // Use probabilities as weights for new distribution and pick next node
        std::discrete_distribution<> nextDistribution ( weights.begin() , weights.end());

        int nextNode = nextDistribution( *randomGenerator );
        tabuList.emplace_back(nextNode);

        // Zero out column [nextNode] so node is not selected again
        for (int i = 0; i < graph->getNumberOfLocations(); i++) {
            heuristicMatrix[i][nextNode] = 0; //TODO - check
        }

        // Resets distribution for next iteration
        nextDistribution.reset();
        weights.clear();


        // Sets next node as last node for next loop iteration
        lastNode = nextNode;
    }
    // Avoiding memory leak
    //delete(randomGenerator); //TODO - check
}

float Ant::calculateInverseCost() {
    int totalCost = 0;
    for (int i = 0; i < graph->getNumberOfLocations()-1; i++) {
        // Cost is distance * flow
        totalCost += graph->getDistance(tabuList.at(i), tabuList.at(i+1)) * graph->getFlow(tabuList.at(i), tabuList.at(i+1));
    }
    // Returns inverse so to minimise cost we find the highest calculateInverseCost for any tabuList
    return ((float) 1 / (float) totalCost);
}

std::vector<int> Ant::getTabuList() {
    traverseGraph();
    return tabuList;
}


void Ant::updatePartialPheromone(float inverseCost) {
    graph->pheromoneMutex.lock();
    graph->addPartialPheromone(inverseCost, tabuList);
    graph->pheromoneMutex.unlock();
}







