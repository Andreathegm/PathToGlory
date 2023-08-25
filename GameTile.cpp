//
// Created by HP on 30/07/2023.
//

#include "GameTile.h"

sf::Vector2f GameTile::getPos() const {
      return pos;
}

void GameTile::setPos(const sf::Vector2f &posi) {
      pos=posi;
      obs_sprite.setPosition(posi.x*gridSizeF,posi.y*gridSizeF);
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
    tile.setOutlineThickness(4);
    tile.setOutlineColor(sf::Color::Black);
    tile.setPosition(x * gridSizeF, y * gridSizeF);

    //set up variables
    accessible = access;
    h = H;
    g = G;
    parent = nullptr;
    visible=true;
    center=false;
}
void GameTile::draw(sf::RenderWindow &window) const {
    window.draw(tile);
    if(visible)
    window.draw(obs_sprite);

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

float GameTile::EuclidianDistance(const GameTile &targetTile) {
    return sqrt((targetTile.pos.x-pos.x)*(targetTile.pos.x-pos.x)+(targetTile.pos.y-pos.y)*(targetTile.pos.y-pos.y));
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

void GameTile::setParent(GameTile *Parent) {
    parent=Parent;
}

bool GameTile::isAccessible() const {
    return accessible;
}

void GameTile::setAccessible(bool accessibl) {
    accessible=accessibl;
}

sf::Sprite GameTile::getObsSprite() {
    return obs_sprite;
}

void GameTile::setObsSpriteTexture(const sf::Texture &ob_texture,std::string direction) {
    obs_sprite.setTexture(ob_texture);
        if (direction == "Stright") {
            obs_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

        } else if (direction == "turn_right") {
            obs_sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

        } else if (direction == "turn_left") {
            obs_sprite.setTextureRect(sf::IntRect(48, 0, 16, 16));


        }
        else if (direction == "x_dir") {
            obs_sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));

        }
        else if(direction=="turn_right_top"){
            obs_sprite.setTextureRect(sf::IntRect(64, 0, 16, 16));}

        else if(direction=="turn_left_top"){
            obs_sprite.setTextureRect(sf::IntRect(80, 0, 16, 16));
        }
        else if(direction=="full"){
            obs_sprite.setTextureRect(sf::IntRect(64,16, 16, 16));
        }
        else if(direction=="3_right"){
            obs_sprite.setTextureRect(sf::IntRect(0,16, 16, 16));
        }
        else if(direction=="3_top"){
            obs_sprite.setTextureRect(sf::IntRect(16,16, 16, 16));
        }
        else if(direction=="3_down"){
            obs_sprite.setTextureRect(sf::IntRect(32,16, 16, 16));
        }
        else if(direction=="3_left"){
            obs_sprite.setTextureRect(sf::IntRect(48,16, 16, 16));
        }
        else if(direction=="4_dir"){
            obs_sprite.setTextureRect(sf::IntRect(96,0, 16, 16));
        }


        if(!scalable)
            obs_sprite.scale(6,6);
        scalable = true;

}
bool GameTile::isVisible() const {
     return visible;
}

void GameTile::setVisible(bool visible) {
     GameTile::visible = visible;
}

bool GameTile::isCenter() const {
     return center;
}

void GameTile::setCenter(bool cent) {
     center=cent;
}

sf::Sprite &GameTile::getO_sprite() {
    return obs_sprite;
}








