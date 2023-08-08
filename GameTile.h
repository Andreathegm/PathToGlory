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

#include<memory>
#include<cmath>

class GameTile {
public:
    //cons and destructor
    GameTile(float x, float y, const sf::Color& fillColor = sf::Color::White,bool access=true,int G=0,int H=0 );
    ~GameTile(){
        delete parent;
    };



   //overloaded function
    bool operator<(const GameTile& other) const;
    bool operator>(const GameTile& other) const;

    //method
    void draw(sf::RenderWindow& window) const;
    float ManhattanDistance(const GameTile& targetTile);
    int f_cost() const ;

    //getter and setter
    const sf::Vector2f getPos() const;
    void setPos(const sf::Vector2f &posi);
     sf::RectangleShape &getTile() ;
    float getGridSizeF() const;
    void setAccessible(bool accessibl);
    bool isAccessible() const;
    void setG(int G);
    int getG() const;
    void setH(int H);
    int getH() const;
    GameTile* getParent() const;
    void setParent(GameTile *parent);

     sf::Sprite getObsSprite();

    void setObsSpriteTexture(const sf::Texture& ob_texture,std::string="Stright");

    bool isVisible() const;

    void setVisible(bool visible);

    bool isCenter() const;

    void setCenter(bool center);

private:
    sf::Vector2f pos;
    sf::RectangleShape tile;
    float gridSizeF=100.f;
    int g,h;
    GameTile* parent;
    bool accessible;
    sf::Sprite obs_sprite;
    bool visible;
    bool scalable=false;
    bool center;

};


#endif //PATHTOGLORY_GAMETILE_H
