

#include "gtest/gtest.h"
#include "../GameMap.h"

//function for comparing 2 floats
bool areEqual(float a, float b, float epsilon = 1e-3) {
    return std::abs(a - b) < epsilon;
}

TEST(Euristic,EuclidianDistance){
    auto* map=new GameMap(5);
    auto start=map->getTilemap()[0][0];
    auto destination=map->getTilemap()[4][4];
    float distance = start->EuclidianDistance(*destination);
    bool equal= areEqual(distance,5.656);
    EXPECT_EQ(equal,true);

    delete map;

}
TEST(F_cost,standarsum){
    auto* tile=new GameTile(100,0);
    tile->setH(3);
    tile->setG(6);
    int f_cost =tile->f_cost();
    EXPECT_EQ(f_cost,9);

    delete tile;
}
TEST(F_cost,After_a_star_algorithm){
    auto* map=new GameMap(5);
    auto start=map->getTilemap()[0][0];
    auto destination=map->getTilemap()[4][4];
    map->aStar(start,destination);
    int f_cost= map->getTilemap()[2][2]->f_cost();
    EXPECT_EQ(f_cost,56);

    delete map;
}


