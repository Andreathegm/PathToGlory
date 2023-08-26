//
// Created by HP on 21/08/2023.
//
#include <gtest/gtest.h>
#include "../GameMap.h"
void setTile(GameTile* tile,bool Acces=false,bool center=true,bool visibl=true,sf::Color color=sf::Color::Blue){
    tile->setAccessible(Acces);
    tile->setCenter(center);
    tile->setVisible(visibl);
    tile->getTile().setFillColor(color);
}
void AsserTile(GameTile* tile,bool Acces,bool center,bool visibl,sf::Color color){
    ASSERT_EQ(tile->isAccessible(),Acces );
    ASSERT_EQ(tile->isVisible(),visibl);
    ASSERT_EQ(tile->isCenter(),center);
    ASSERT_EQ(tile->getTile().getFillColor(),color);
}


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
    setTile(tile);
    AsserTile(tile,false,true,true,sf::Color::Blue);
    map->reset();
    for(std::vector<GameTile*> i : map->getTilemap()){
        for(auto &k : i ){
            AsserTile(k, true,false,false,sf::Color::Transparent);
        }
    }
}
TEST(GamMapTest,PartialReset){
    auto* map=new GameMap(5);
    auto tile=map->getTilemap()[1][1];
    setTile(tile);
    AsserTile(tile,false,true,true,sf::Color::Blue);


    auto start=map->getTilemap()[0][0];
    auto destination=map->getTilemap()[4][4];
    map->aStar(start,destination);

    map->reset(true);

    for(std::vector<GameTile*> i : map->getTilemap()){
        for(auto &k : i ){
            if(k!=tile){
                AsserTile(k,true,false,false,sf::Color::Transparent);
            }
            else{
                AsserTile(k,false,true,true,sf::Color::Blue);

            }
        }
    }
}