//
// Created by joseph on 11/17/22.
//

#include <gtest/gtest.h>
#include "../src/Graph.h"

TEST(Contructor, DefaultConstructor) {
    Graph graph1;

    EXPECT_EQ(graph1.getALPHA(), 2);
    EXPECT_EQ(graph1.getBETA(), 1);

    EXPECT_EQ(graph1.getDistance(4,5), 89 );
    EXPECT_EQ(graph1.getDistance(1,2), 21);

    EXPECT_EQ(graph1.getFlow(3,2), 55);
    EXPECT_EQ(graph1.getFlow(50,3), 42);

    EXPECT_EQ(graph1.getPheromone(4,4), 0);
    EXPECT_EQ(graph1.getPheromone(33,46), 1);

    EXPECT_EQ(graph1.getNumberOfLocations(), 50);

    std::vector<double> expectedIPVector;
    for (int i = 0; i < 50; ++i) {
        expectedIPVector.push_back(1.0);
    }
    EXPECT_EQ(graph1.getInitialPheromone(), expectedIPVector );
}

TEST(Contructor, OverloadedConstructor) {
    Graph graph1("/home/joseph/Documents/Quadratic-Ant-Colony-Optimisation-Solver/res/dataSet.txt",5,6);

    EXPECT_EQ(graph1.getALPHA(), 5);
    EXPECT_EQ(graph1.getBETA(), 6);

    EXPECT_EQ(graph1.getDistance(4,5), 89 );
    EXPECT_EQ(graph1.getDistance(1,2), 21);

    EXPECT_EQ(graph1.getFlow(3,2), 55);
    EXPECT_EQ(graph1.getFlow(50,3), 42);

    EXPECT_EQ(graph1.getPheromone(4,4), 0);
    EXPECT_EQ(graph1.getPheromone(33,46), 1);

    EXPECT_EQ(graph1.getNumberOfLocations(), 50);

    std::vector<double> expectedIPVector;
    for (int i = 0; i < 50; ++i) {
        expectedIPVector.push_back(1.0);
    }
    EXPECT_EQ(graph1.getInitialPheromone(), expectedIPVector );
}

TEST(DataManipulation, AddPheromoneTest) {
    Graph graph1;


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}