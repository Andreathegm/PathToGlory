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

sf::Vector2f &GameCharacter::getPosition()  {
    return position;
}

 sf::Sprite &GameCharacter::getGcSprite()  {
    return gcSprite;
}

const sf::Texture &GameCharacter::getGctexture() const{
    return gctexture;
}

void GameCharacter::setPosition(const sf::Vector2f &position) {
    GameCharacter::position=position;
    gcSprite.setPosition(position);


}

void GameCharacter::setGcSprite(const sf::Sprite &gcSprite) {
    GameCharacter::gcSprite = gcSprite;
}

void GameCharacter::setGctexture(const sf::Texture &gctexture) {
    GameCharacter::gctexture = gctexture;
}

GameCharacter::GameCharacter(sf::Texture& texture, int hp, int att, int def, sf::Vector2f pos) : position(pos) {

        gctexture=texture;
        gcSprite.setTexture(gctexture);
        gcSprite.setTextureRect(sf::IntRect(266, 226, 25, 55));
        gcSprite.scale(sf::Vector2f(1.5,1.5));
        gcSprite.setPosition(pos);


   // Rightwalk=new Animation(0, 0 ,43,58,13,gctexture);
    GameCharacter::HP=hp;
    GameCharacter::Attack=att;
    GameCharacter::defense=def;




}

void GameCharacter::move() {
   /* if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        dir.y=-1.0f;
        //gcSprite.move(sf::Vector2f(0,-1));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        dir.x=-1.0f;

      //  gcSprite.move(sf::Vector2f(-1,0));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        dir.y+=1.0f;
       // gcSprite.move(sf::Vector2f(0,1));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        dir.x+=1.0f;
       // gcSprite.move(sf::Vector2f(1,0));
        }*/







}

void GameCharacter::draw(sf::RenderWindow& window) {
    window.draw(gcSprite);

}


void GameCharacter::Setdirection(const sf::Vector2f &dir) {
    vel=dir*speed;

}

void GameCharacter::Update(float dt) {
    position+= vel* dt;

}

void GameCharacter::setTexturerect(sf::IntRect rect) {
    gcSprite.setTextureRect(rect);

}




