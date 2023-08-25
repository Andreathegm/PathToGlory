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
    GameTile(float x, float y, const sf::Color& fillColor = sf::Color::Transparent,bool access=true,int G=0,int H=0 );
    ~GameTile()=default;



   //overloaded function
    bool operator<(const GameTile& other) const;
    bool operator>(const GameTile& other) const;

    //METHODS
    void draw(sf::RenderWindow& window) const;
    float EuclidianDistance(const GameTile& targetTile);
    int f_cost() const ;

    //Getter and Setter

    //info about position
    sf::Vector2f getPos() const;
    void setPos(const sf::Vector2f &posi);
     sf::RectangleShape &getTile() ;
    float getGridSizeF() const;

    // access to the grid tile
    void setAccessible(bool accessibl);
    bool isAccessible() const;

    // info for a* algorithm
    void setG(int G);
    int getG() const;
    void setH(int H);
    int getH() const;
    GameTile* getParent() const;
    void setParent(GameTile *Parent);

    //Texture for walls
    sf::Sprite getObsSprite();
    sf::Sprite& getO_sprite();
    void setObsSpriteTexture(const sf::Texture& ob_texture,std::string="Stright");

    //set whether drawing texture
    bool isVisible() const;
    void setVisible(bool visible);

    // central Block for autonomy of placing blocks (the sprite that is represented by a tower has it TRUE)
    bool isCenter() const;
    void setCenter(bool center);



private:
    sf::Vector2f pos;
    sf::RectangleShape tile;
    float gridSizeF=100.f;
    int g,h;
    GameTile* parent;
    sf::Sprite obs_sprite;


    bool accessible;
    bool visible;
    bool scalable=false;  //check if the sprite has been scaled
    bool center;

};


#endif //PATHTOGLORY_GAMETILE_H
