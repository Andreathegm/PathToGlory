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
    GameCharacter(sf::Texture& texture,int hp,int att,int def,sf::Vector2f pos);
    ~GameCharacter()=default;

    //getter and setter

    //name
    const std::string &getName() const;
    void setName(const std::string &name);

    //hp
    int getHp() const;
    void setHp(int hp);

    //attack
    int getAttack() const;
    void setAttack(int attack);

    //defense
    int getDefense() const;
    void setDefense(int defense);

    // position
     sf::Vector2f &getPosition() ;
    void setPosition(const sf::Vector2f &position);

    // sprite
     sf::Sprite &getGcSprite() ;
    void setGcSprite(const sf::Sprite &gcSprite);

    // texture
    const sf::Texture &getGctexture() const;
    void setGctexture(const sf::Texture &gctexture);

    void setTexturerect(sf::IntRect rect);


    // method
    void move();
    void attack(GameCharacter& enemy);

    // set direction and perceiving changes
    void Setdirection(const sf::Vector2f& dir);
    void Update(float dt);

    //draw
    void draw(sf::RenderWindow& window);


private:
    //name and Carateristic
    std::string name;
    int HP,Attack,defense;

    // position and setting
    static constexpr float speed =100.f;
    sf::Vector2f vel ={ 0.0f , 0.0f};
    sf::Vector2f position;
    sf::Sprite gcSprite;
    sf::Texture gctexture;


};


#endif //PATHTOGLORY_GAMECHARACTER_H
