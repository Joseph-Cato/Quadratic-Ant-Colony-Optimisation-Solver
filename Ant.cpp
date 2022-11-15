//
// Created by joseph on 11/15/22.
//

#include "Ant.h"

Ant::Ant(Graph graph1) {
    graph = graph1;
}

void Ant::traverseGraph() {
    for (int i = 0; i < graph.getNumberOfLocations(); i++) {
        //set first in tabu list
        // remove from possible reselection
    }
}

void Ant::addPheromone(std::vector<std::vector<float>> pheromone) {
    Graph::pheromoneMutex.lock();
    graph.addPheromone(pheromone);
    Graph::pheromoneMutex.unlock();
}