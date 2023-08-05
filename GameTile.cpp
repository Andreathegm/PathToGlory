//
// Created by HP on 30/07/2023.
//

#include "GameTile.h"

const sf::Vector2f GameTile::getPos() const {
    return pos;
}

void GameTile::setPos(const sf::Vector2f &posi) {
      pos=posi;
}


 sf::RectangleShape &GameTile::getTile()  {
    return tile;
}

float GameTile::getGridSizeF() const {
    return gridSizeF;
}


GameTile::GameTile(float x, float y, const sf::Color &fillColor,bool access,int G,int H ) {
    //set position

    pos.x = x;
    pos.y = y;
    //set up tile(rectangle shape)
    tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    tile.setFillColor(fillColor);
    tile.setOutlineThickness(1.5);
    tile.setOutlineColor(sf::Color::Black);
    tile.setPosition(x * gridSizeF, y * gridSizeF);

    //set up variables
    accessible = access;
    h = H;
    g = G;
    parent = nullptr;
}
void GameTile::draw(sf::RenderWindow &window) const {
    window.draw(tile);

}

int GameTile::f_cost() const {
    return g+h;
}

bool GameTile::operator<(const GameTile &other) const {
    return f_cost()> other.f_cost();
}

bool GameTile::operator>(const GameTile &other) const {
    return !operator<(other);
}

int GameTile::ManhattanDistance(const GameTile &targetTile) {
    return (std::abs(targetTile.pos.x-pos.x)+std::abs(targetTile.pos.y-pos.y));
}

void GameTile::setG(int G) {
    g=G;
}

void GameTile::setH(int H) {
    h=H;
}

int GameTile::getG() const {
    return g;
}

int GameTile::getH() const {
    return h;
}

GameTile *GameTile::getParent() const {
    return parent;
}

void GameTile::setParent(GameTile *parent) {
    GameTile::parent = parent;
}

bool GameTile::isAccessible() const {
    return accessible;
}

void GameTile::setAccessible(bool accessibl) {
    accessible=accessibl;
}






