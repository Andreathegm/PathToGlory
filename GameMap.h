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
     void reset(bool act=false);  // Reset the map : boolean argument is used to do full reset(false) or partial(false)

     //getter and setter
     const std::vector<std::vector<GameTile*>> &getTilemap() const;
     int getMapsize() const;
private:
    std::vector<std::vector<GameTile*>> tilemap;
    int mapSize;


};


#endif //PATHTOGLORY_GAMEMAP_H
