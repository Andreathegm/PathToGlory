//
// Created by HP on 30/07/2023.
//

#include "GameMap.h"



GameMap::~GameMap() {}

int GameMap::getMapsize() const {
    return mapSize;
}

GameMap::GameMap( int mapSize): mapSize(mapSize) {
    tilemap.resize(mapSize);
    for (int x = 0; x < mapSize; x++) {
        tilemap[x].resize(mapSize);
        for (int y = 0; y < mapSize; y++) {
            tilemap[x][y] = std::make_unique<GameTile>(static_cast<float>(x), static_cast<float>(y), sf::Color::White);
        }
        }
    }


void GameMap::draw(sf::RenderWindow &window) const {
    for (int x = 0; x < mapSize; x++) {
        for (int y = 0; y < mapSize; y++) {
            tilemap[x][y]->draw(window);

        }
    }
}

const std::vector<std::vector<std::unique_ptr<GameTile>>> &GameMap::getTilemap() const {
    return tilemap;
}
