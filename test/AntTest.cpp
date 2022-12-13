//
// Created by joseph on 11/17/22.
//


#include <gtest/gtest.h>
#include "../src/Graph.h"
#include "../src/Ant.h"

TEST(randomWalk, traverseGraphTest) {
    Graph Graph1;
    Ant Ant1(&Graph1);

    ASSERT_TRUE(Ant1.getTabuList().empty());

    Ant1.traverseGraph();

    EXPECT_FALSE(Ant1.getTabuList().empty());

    std::vector<int> tabuList;
    tabuList = Ant1.getTabuList();

    bool containsDuplicate = false;

    for (int j = 0; j < (int) tabuList.size(); j++) {
        for (int i = 0; i < (int) tabuList.size(); ++i) {
            if (i == j) {
                continue;
            } else {
                if (tabuList.at(i) == tabuList.at(j)) {
                    containsDuplicate = true;
                }
            }
        }
    }
    ASSERT_FALSE(containsDuplicate);
}

TEST(pheromone, addPheromoneValues) {
    Graph Graph1;
    Ant Ant1(&Graph1);
    Ant1.traverseGraph();
    std::vector<std::vector<float>> newPheromone;
    std::vector<float> newPheromoneRow = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    for (int i = 0; i<50; i++){
        newPheromone.emplace_back(newPheromoneRow);
    }

    /*
    Ant1.addPheromone(newPheromone);
    for(int i=0; i<50; i++) {
        for(int j=0; j<50; j++) {
            if (i == j) { continue;}
            ASSERT_TRUE(Graph1.getPheromone(i, j) == 2);
        }
    }
     */
}

