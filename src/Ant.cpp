//
// Created by joseph on 11/15/22.
//

#include <map>
#include <utility>
#include <iostream>
#include "Ant.h"

Ant::Ant(Graph *graph1 ){
    std::cout << "Creating ant object";
    graph = graph1;
    tabuList.clear();
}

void Ant::traverseGraph() {
    //TODO - create more efficient sampler (discrete distribution without replacement) https://www.sciencedirect.com/science/article/abs/pii/S002001900500298X?via%3Dihub
    std::cout << "Ant::traverseGraph()";

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

    std::cout << "Found tabuList: \n";
    for (int i = 0; i < 50; i++) {
        std::cout << tabuList[i] << " ";
    }
    std::cout << "\n";
    // Avoiding memory leak
    //delete(randomGenerator); //TODO - check
}

void Ant::addPheromone(std::vector<std::vector<float>> pheromone) {
    Graph::pheromoneMutex.lock();
    graph->addPheromone(std::move(pheromone));
    Graph::pheromoneMutex.unlock();
}

float Ant::calculateInverseCost() {
    int totalCost = 0;
    for (int i = 0; i < graph->getNumberOfLocations()-1; i++) {
        // Cost is distance * flow
        totalCost += graph->getDistance(tabuList.at(i), tabuList.at(i+1) * graph->getFlow(tabuList.at(i), tabuList.at(i+1)));
    }
    // Returns inverse so to minimise cost we find the highest calculateInverseCost for any tabuList
    return ((float) 1 / (float) totalCost);
}

std::vector<int> Ant::getTabuList() {
    traverseGraph();
    return tabuList;
}

void Ant::updatePheromone(float inverseCost) {
    std::cout << "\nAnt::updarePheromone( " << inverseCost << " )\n";

    // So for loops know when to stop without calling getter multiple times
    int numOfValues = graph->getNumberOfLocations();

    // Pads matrix with zeros
    pheromoneAddition = std::vector<std::vector<float>>(50);
    std::vector<float> pheromoneRow = std::vector<float>(50);
    /*
    for (int i = 0; i < numOfValues; i++) {
        for (int j = 0; j < numOfValues; j++) {
            pheromoneRow.emplace_back( 0 );
        }
        pheromoneAddition.emplace_back(pheromoneRow);
    }
     */
    std::cout << "vector size " << pheromoneAddition.size() << "\n";

    for (int i = 0; i < numOfValues; ++i) {
        pheromoneAddition[i][tabuList[i]] = inverseCost;
    }

    std::cout << "\n\n Printing pheromone addition (ant.ccp line 127):\n"; //TODO - remove
    for (int i = 0; i < numOfValues; i++) {
        for (int j = 0; j < numOfValues; j++) {
            std::cout << pheromoneAddition[i][j] << " ";
        }
        std::cout << "\n";
    }

    Graph::pheromoneMutex.lock();
    graph->addPartialPheromone(pheromoneAddition);
    Graph::pheromoneMutex.unlock();
}







