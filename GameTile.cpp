//
// Created by HP on 30/07/2023.
//

#include "GameTile.h"

const sf::Vector2f &GameTile::getPos() const {
    return pos;
}

void GameTile::setPos(const sf::Vector2f &pos) {
    GameTile::pos = pos;
}


const sf::RectangleShape &GameTile::getTile() const {
    return tile;
}

float GameTile::getGridSizeF() const {
    return gridSizeF;
}


GameTile::GameTile(float x, float y, const sf::Color &fillColor) {
    tile.setSize(sf::Vector2f(gridSizeF,gridSizeF));
    tile.setFillColor(fillColor);
    tile.setOutlineThickness(1.5);
    tile.setOutlineColor(sf::Color::Black);
    tile.setPosition(x*gridSizeF,y*gridSizeF);

}

void GameTile::draw(sf::RenderWindow &window) const {
    window.draw(tile);

}
