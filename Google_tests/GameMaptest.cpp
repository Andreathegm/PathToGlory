//
// Created by HP on 21/08/2023.
//
#include <gtest/gtest.h>
#include "../GameMap.h"

TEST(GamMapTest,aStar){
    int value=0;
    auto* map=new GameMap(5);
    auto start= map->getTilemap()[0][0];
    auto destination=map->getTilemap()[4][4];
    std::vector<sf::Vector2f> path = map->aStar(start,destination);
    for(auto& i : path){
        ASSERT_EQ(i.x,value);
        ASSERT_EQ(i.y,value++);
    }
}
TEST(GamMapTest,Fullreset){
    auto* map=new GameMap(5);
    auto tile=map->getTilemap()[4][4];
    tile->setAccessible(false);
    tile->setCenter(true);
    tile->setVisible(true);
    tile->getTile().setFillColor(sf::Color::Blue);
    ASSERT_EQ(tile->isAccessible(), false);
    ASSERT_EQ(tile->isVisible(),true);
    ASSERT_EQ(tile->isCenter(),true);
    ASSERT_EQ(tile->getTile().getFillColor(),sf::Color::Blue);
    map->reset();
    for(std::vector<GameTile*> i : map->getTilemap()){
        for(auto &k : i ){
            ASSERT_EQ(k->isAccessible(), true);
            ASSERT_EQ(k->isVisible(),false);
            ASSERT_EQ(k->isCenter(),false);
            ASSERT_EQ(k->getTile().getFillColor(),sf::Color::Transparent);
        }
    }
}
TEST(GamMapTest,PartialReset){
    auto* map=new GameMap(5);
    auto tile=map->getTilemap()[1][1];
    tile->setAccessible(false);
    tile->setCenter(true);
    tile->setVisible(true);
    tile->getTile().setFillColor(sf::Color::Blue);
    auto start=map->getTilemap()[0][0];
    auto destination=map->getTilemap()[4][4];
    map->aStar(start,destination);

    map->reset(true);

    for(std::vector<GameTile*> i : map->getTilemap()){
        for(auto &k : i ){
            if(k!=tile){
            ASSERT_EQ(k->isAccessible(), true);
            ASSERT_EQ(k->isVisible(),false);
            ASSERT_EQ(k->isCenter(),false);
            ASSERT_EQ(k->getTile().getFillColor(),sf::Color::Transparent);
            }
            else{
                ASSERT_EQ(k->isAccessible(), false);
                ASSERT_EQ(k->isVisible(),true);
                ASSERT_EQ(k->isCenter(),true);
                ASSERT_EQ(k->getTile().getFillColor(),sf::Color::Blue);

            }
        }
    }
}