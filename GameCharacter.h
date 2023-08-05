//
// Created by HP on 30/07/2023.
//

#ifndef PATHTOGLORY_GAMECHARACTER_H
#define PATHTOGLORY_GAMECHARACTER_H


#include <iostream>
#include <SFML/Graphics.hpp>// occhio
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "GameMap.h"
class GameCharacter {

public:
    //constructor and distructor
    GameCharacter(std::string name,int hp,int att,int def,sf::Vector2f pos);
    ~GameCharacter(){};

    //getter and setter
    const std::string &getName() const;
    void setName(const std::string &name);
    int getHp() const;
    void setHp(int hp);
    int getAttack() const;
    void setAttack(int attack);
    int getDefense() const;
    void setDefense(int defense);
    void attack(GameCharacter& enemy);
    const sf::Vector2f &getPosition() const;
    const sf::Sprite &getGcSprite() const;
    const sf::Texture &getGctexture() const;
    void setPosition(const sf::Vector2f &position);
    void setGcSprite(const sf::Sprite &gcSprite);
    void setGctexture(const sf::Texture &gctexture);

// method
    void move();
    void move_to_position(std::vector<sf::Vector2f>& path);
    void draw(sf::RenderWindow& window);


private:

    std::string name;
    int HP,Attack,defense;
    sf::Vector2f position;
    sf::Sprite gcSprite;
    sf::Texture gctexture;
    sf::IntRect current_frame;
    sf::Clock animationTimer;

};


#endif //PATHTOGLORY_GAMECHARACTER_H
