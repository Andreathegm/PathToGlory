//
// Created by HP on 30/07/2023.
//
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



#ifndef PATHTOGLORY_GAMETILE_H
#define PATHTOGLORY_GAMETILE_H


class GameTile {
public:
    //cons and destructor
    GameTile(float x, float y, const sf::Color& fillColor = sf::Color::White);
    ~GameTile(){};


    //Getter and Setter
    const sf::Vector2f &getPos() const;
    void setPos(const sf::Vector2f &pos);
    const sf::RectangleShape &getTile() const;

    float getGridSizeF() const;



    void draw(sf::RenderWindow& window) const;

private:
    sf::Vector2f pos;
    sf::RectangleShape tile;
    float gridSizeF=100.f;



};


#endif //PATHTOGLORY_GAMETILE_H
