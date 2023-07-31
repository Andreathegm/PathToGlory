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

const std::pair<int, int> &GameCharacter::getPosition() const {
    return position;
}

void GameCharacter::setPosition(const std::pair<int, int> &position) {
    GameCharacter::position = position;
}

void GameCharacter::move_to_position(const std::pair<int, int> &Newpos) {
    position=Newpos;

}
