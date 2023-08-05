//
// Created by HP on 30/07/2023.
//

#ifndef PATHTOGLORY_GAMEMAP_H
#define PATHTOGLORY_GAMEMAP_H

#include "GameTile.h"
#include <vector>
#include <unordered_map>
#include<queue>
#include <functional>

class GameMap {
public:
    //cons and des
    explicit GameMap(int mapSize);
    ~GameMap();

     //method
     std::vector<sf::Vector2f> aStar( GameTile* start, GameTile* destination);
    void draw(sf::RenderWindow& window) const;

    //getter and setter
    const std::vector<std::vector<GameTile*>> &getTilemap() const;
    int getMapsize() const;
    void reset();

private:
    std::vector<std::vector<GameTile*>> tilemap;
    int mapSize;


};


#endif //PATHTOGLORY_GAMEMAP_H
