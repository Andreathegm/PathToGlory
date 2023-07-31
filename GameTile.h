//
// Created by HP on 30/07/2023.
//
#include <SFML/Graphics.hpp>
#ifndef PATHTOGLORY_GAMETILE_H
#define PATHTOGLORY_GAMETILE_H


class GameTile {
public:
    GameTile(){};


private:
    std::pair<int, int > pos;
    bool passable;
    bool free_exit;
    sf::Texture texture;
    sf::Sprite sprite;

};


#endif //PATHTOGLORY_GAMETILE_H
