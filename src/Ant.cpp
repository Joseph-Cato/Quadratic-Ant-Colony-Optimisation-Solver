//
// Created by joseph on 11/15/22.
//

#include <map>
#include <utility>
#include <iostream>
#include "Ant.h"

Ant::Ant(Graph *graph1 ){
    graph = graph1;
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

    // Distribution for first traversal
    std::discrete_distribution<> firstDistribution( graph->getInitialPheromone().begin(),
                                                    graph->getInitialPheromone().end() );


    // First traversal from imaginary start node
    int firstNode = firstDistribution(*randomGenerator);
    tabuList.emplace_back(firstNode);

    //TODO remove
    std::cout << "---------------------- Iteration 0 ----------------------\n";
    std::cout << "Weights: ";
    for (double i: graph->getInitialPheromone()) {
        std::cout << i << ", ";
    }
    std::cout << "\n";
    std::cout << "Node 1: " << firstNode << "\n\n Initial Heuristic Matrix\n";

    /*
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            std::cout << heuristicMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
     */


    // Zero out first node column of heuristic matrix so probability of returning to that node = 0
    for (int i = 0; i < graph->getNumberOfLocations(); i++) {
        heuristicMatrix[i][firstNode-1] = 0;
    }

    /*
    std::cout << "\n\nAfter zero-ing column:\n";
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            std::cout << heuristicMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
     */

    int lastNode = firstNode;

    for (int iteration = 1; iteration < graph->getNumberOfLocations(); iteration++) {

        std::cout << "---------------------- Iteration " << iteration << "----------------------\n";


        // calculate probabilities of going to another node
        std::vector<double> weights;
        for (int i = 1; i < graph->getNumberOfLocations()+1; i++) {
            weights.emplace_back(  pow( (double) graph->getPheromone(lastNode, i), (double) graph->getALPHA()) * pow( (double) heuristicMatrix[i-1][lastNode-1], (double) graph->getBETA() ) );
        }

        /*
        std::cout << "\nHeuristic Matrix:\n\n";

        for (int i = 0; i < 50; ++i) {
            for (int j = 0; j < 50; ++j) {
                std::cout << heuristicMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
         */

        std::cout << "\n\n5th Weight Values:\n    Pheromone Value: " << graph->getPheromone(lastNode, 5) << "\n   Alpha: " << graph->getALPHA();
        std::cout << "\n    Heuristic: " << heuristicMatrix[lastNode-1][4] << "\n   Beta: " << graph->getBETA() << "\n";


        std::cout << "Weights: ";
        for (double i: weights) {
            std::cout << (double) i << ", ";
        }


        // Use probabilities as weights for new distribution and pick next node
        std::discrete_distribution<> nextDistribution ( weights.cbegin() , weights.cend());

        std::cout << "\nProbabilities: ";
        for (int i = 0; i < 50; i++) {
            std::cout << (double) nextDistribution.probabilities()[i] << ", ";
        }
        std::cout << "\n";

        int nextNode = nextDistribution( *randomGenerator );
        tabuList.emplace_back(nextNode);

        std::cout << "Next Node: " << nextNode << "\n";

        // Zero out column [nextNode] so node is not selected again
        for (int i = 0; i < graph->getNumberOfLocations(); i++) {
            heuristicMatrix[i][nextNode] = 0;
        }

        // Resets distribution for next iteration
        nextDistribution.reset();
        weights.clear();


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


