//
// Created by joseph on 11/15/22.
//

#include <map>
#include <utility>
#include <iostream>
#include "Ant.h"

Ant::Ant(Graph *graph1 ){
    graph = graph1;
    weights.reserve(50);
    tabuList.reserve(50);
    tabuList.clear();
}

void Ant::traverseGraph() {
    //TODO - create more efficient sampler (discrete distribution without replacement) https://www.sciencedirect.com/science/article/abs/pii/S002001900500298X?via%3Dihub

    // Getting and configuring heuristic matrix
    std::vector<std::vector<double>> heuristicMatrix;
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
    delete(randomGenerator);
}

void Ant::addPheromone(std::vector<std::vector<float>> pheromone) {
    Graph::pheromoneMutex.lock();
    graph->addPheromone(std::move(pheromone));
    Graph::pheromoneMutex.unlock();
}

std::vector<int> Ant::getTabuList() {
    return tabuList;
}

// TODO - remove
void Ant::testTraverseGraph() {
    traverseGraph();
}


