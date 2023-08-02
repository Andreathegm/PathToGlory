//
// Created by HP on 30/07/2023.
//

#ifndef PATHTOGLORY_GAMEMAP_H
#define PATHTOGLORY_GAMEMAP_H

#include "GameTile.h"
#include <vector>
#include <memory>
class GameMap {
public:
    //cons and des
    GameMap();
    GameMap(int mapSize);
    void draw(sf::RenderWindow& window) const;
    ~GameMap();

     //method

    //getter and setter

    const std::vector<std::vector<std::unique_ptr<GameTile>>> &getTilemap() const;

    int getMapsize() const;

private:
    std::vector<std::vector<std::unique_ptr<GameTile>>> tilemap;
    int mapSize;


};


#endif //PATHTOGLORY_GAMEMAP_H
