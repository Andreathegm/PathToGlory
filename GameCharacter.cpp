//
// Created by HP on 30/07/2023.
//

#include "GameCharacter.h"

const std::string &GameCharacter::getName() const {
    return name;
}

void GameCharacter::setName(const std::string &name) {
    GameCharacter::name = name;
}

int GameCharacter::getHp() const {
    return HP;
}

void GameCharacter::setHp(int hp) {
    HP = hp;
}

int GameCharacter::getAttack() const {
    return Attack;
}

void GameCharacter::setAttack(int attack) {
    Attack = attack;
}

int GameCharacter::getDefense() const {
    return defense;
}

void GameCharacter::setDefense(int defense) {
    GameCharacter::defense = defense;
}

void GameCharacter::attack(GameCharacter &enemy) {
    if(Attack>0) {
        enemy.HP = Attack - enemy.defense;
    }


}

const sf::Vector2f &GameCharacter::getPosition() const {
    return position;
}

const sf::Sprite &GameCharacter::getGcSprite() const {
    return gcSprite;
}

const sf::Texture &GameCharacter::getGctexture() const {
    return gctexture;
}

void GameCharacter::setPosition(const sf::Vector2f &position) {
    gcSprite.setPosition(position);

}

void GameCharacter::setGcSprite(const sf::Sprite &gcSprite) {
    GameCharacter::gcSprite = gcSprite;
}

void GameCharacter::setGctexture(const sf::Texture &gctexture) {
    GameCharacter::gctexture = gctexture;
}

GameCharacter::GameCharacter(std::string name, int hp, int att, int def, sf::Vector2f pos) {
    if(gctexture.loadFromFile(name)) {
        //setup Sprite
        gcSprite.setTexture(gctexture);
        gcSprite.setTextureRect(sf::IntRect(266, 226, 25, 55));
        gcSprite.scale(sf::Vector2f(1.5,1.5));
        gcSprite.setPosition(pos);
        //current_frame=sf::IntRect (266, 226, 25, 55);
        //animationTimer.restart();
    }
    GameCharacter::HP=hp;
    GameCharacter::Attack=att;
    GameCharacter::defense=def;


}

void GameCharacter::move() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        gcSprite.move(sf::Vector2f(0,-1));

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        gcSprite.move(sf::Vector2f(-1,0));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        gcSprite.move(sf::Vector2f(0,1));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        /*if(animationTimer.getElapsedTime().asSeconds()>=0.1){

            current_frame.left+=20;
        if(current_frame.left>=400)
            current_frame.left=0;
        animationTimer.restart();
        gcSprite.setTextureRect(current_frame);*/
        gcSprite.move(sf::Vector2f(1,0));
        }





}

void GameCharacter::draw(sf::RenderWindow& window) {
    window.draw(gcSprite);

}

void GameCharacter::move_to_position(std::vector<sf::Vector2f>& path) {
    for(const auto& i : path ) {
            position=i;
            gcSprite.setPosition(i.x*100,i.y*100);
    }
}


