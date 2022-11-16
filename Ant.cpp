//
// Created by joseph on 11/15/22.
//

#include <map>
#include "Ant.h"

Ant::Ant( Graph graph1){
    graph = graph1;
}

void Ant::traverseGraph() {
    //TODO - create more efficient sampler (discrete distribution without replacement) https://www.sciencedirect.com/science/article/abs/pii/S002001900500298X?via%3Dihub

    // Getting and configuring heuristic matrix
    std::vector<std::vector<double>> heuristicMatrix;
    heuristicMatrix.assign(graph.getHeuristicMatrix().begin(), graph.getHeuristicMatrix().end());

    // Randomness
    static thread_local std::mt19937* randomGenerator = nullptr;
    if (!randomGenerator) {
        // Uses hashed thread ID + time to have unique seed for each run and each ant
        randomGenerator = new std::mt19937 ((std::hash<std::thread::id>{} (std::this_thread::get_id() ) ) + clock() );
    }
    // Distribution for first traversal
    std::discrete_distribution<> firstDistribution(graph.getInitialPheromone().begin(), graph.getInitialPheromone().end());

    // First traversal from imaginary start node
    int firstNode = firstDistribution(*randomGenerator);
    tabuList.emplace_back(firstNode);

    // Zero out first node column of heuristic matrix so probability of returning to that node = 0
    for (int i = 0; i < graph.getNumberOfLocations(); i++) {
        heuristicMatrix[i][firstNode] = 0;
    }

    int lastNode = firstNode;

    for (int iteration = 1; iteration < graph.getNumberOfLocations(); iteration++) {
        // calculate probabilities of going to another node
        std::vector<double> weights;
        for (int i = 0; i < graph.getNumberOfLocations(); i++) {
            weights.emplace_back( pow(graph.getPheromone(lastNode, i), graph.getALPHA()) * pow( heuristicMatrix[lastNode][i], graph.getBETA() ) );
        }

        // Use probabilities as weights for new distribution and pick next node
        std::discrete_distribution<> nextDistribution (weights.begin(), weights.end());

        int nextNode = nextDistribution( *randomGenerator );
        tabuList.emplace_back(nextNode);

        // Zero out column [nextNode] so node is not selected again
        for (int i = 0; i < graph.getNumberOfLocations(); i++) {
            heuristicMatrix[i][nextNode] = 0;
        }

        // Resets distribution for next iteration 
        nextDistribution.reset();

    }
}

void Ant::addPheromone(std::vector<std::vector<float>> pheromone) {
    Graph::pheromoneMutex.lock();
    graph.addPheromone(pheromone);
    Graph::pheromoneMutex.unlock();
}