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

    Ant1.testTraverseGraph();

    EXPECT_FALSE(Ant1.getTabuList().empty());

}