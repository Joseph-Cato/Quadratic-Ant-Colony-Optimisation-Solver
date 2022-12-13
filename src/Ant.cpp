//
// Created by joseph on 11/15/22.
//

#include <map>
#include <iostream>
#include "Ant.h"

Ant::Ant(Graph *graph1 ){
    graph = graph1;
    tabuList.clear();
}

void Ant::traverseGraph() {
    //TODO - Create no local heuristic option by setting heuristic matrix as 1's (apart from diagonal)

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
    tabuList.clear();
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

        // Adds node to tabuList
        tabuList.emplace_back(nextNode);

        // Zero out column [nextNode] so node is not selected again
        for (int i = 0; i < graph->getNumberOfLocations(); i++) {
            heuristicMatrix[i][nextNode] = 0;
        }

        // Resets distribution for next iteration
        nextDistribution.reset();

        // Sets next node as last node for next loop iteration
        lastNode = nextNode;
    }
}

int Ant::getCost() {
    int totalCost = 0;
    for (int i = 0; i < graph->getNumberOfLocations()-1; i++) {
        // Cost addition is distance * flow
        int node = tabuList[i];
        int nextNode = tabuList[i+1];
        totalCost = totalCost + graph->getDistance(node, nextNode) * graph->getFlow(node, nextNode);
    }
    // Returns inverse so to minimise cost we find the highest calculateInverseCost for any tabuList
    return totalCost;
}

std::vector<int> Ant::getTabuList() {
    return tabuList;
}


void Ant::updatePartialPheromone(float inverseCost) {
    Graph::pheromoneMutex.lock();
    graph->addPartialPheromone(inverseCost, tabuList);
    Graph::pheromoneMutex.unlock();
}









