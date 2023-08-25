//
// Created by HP on 30/07/2023.
//

#ifndef PATHTOGLORY_GAMECHARACTER_H
#define PATHTOGLORY_GAMECHARACTER_H


#include <iostream>
#include "Animation.h"
#include "GameMap.h"
class GameCharacter {

public:
    //constructor and distructor
    GameCharacter(sf::Texture& texture,sf::Vector2f pos,GameMap* map);
    explicit GameCharacter(GameMap* map);
    explicit GameCharacter();
    ~GameCharacter()=default;

    //GETTER AND SETTER
    // position
    sf::Vector2f &getPosition() ;
    void setPosition(const sf::Vector2f &position);

    // sprite
    sf::Sprite &getGcSprite() ;
    void setGcSprite(const sf::Sprite &gcSprite);

    // texture
    const sf::Texture &getGctexture() const;
    void setGctexture(const sf::Texture &gctexture);



    //METHOD
   //dynamic move
    void move(std::string dir);
    void UpdateAnimation(int row,float deltatime);
    void setTexturerect(sf::IntRect rect);

    //Check  collision for the walls and the grid
    void collision(float offset_x,float offset_y,bool downmovement=false);
    void GridCollision();


    //draw and animation
    void draw(sf::RenderWindow& window);
    Animation *getAnimation() const;

private:

    // position and setting
    sf::Vector2f position;
    sf::Sprite gcSprite;
    sf::Texture gctexture;
    Animation* animation;
    GameMap* map;


};


#endif //PATHTOGLORY_GAMECHARACTER_H
