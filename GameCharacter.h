//
// Created by HP on 30/07/2023.
//

#ifndef PATHTOGLORY_GAMECHARACTER_H
#define PATHTOGLORY_GAMECHARACTER_H


#include <iostream>

class GameCharacter {

public:
    GameCharacter(std::string name,int hp,int att,int def):name(name),Attack(att),defense(def) {
        position={0,0};
    };

    const std::string &getName() const;

    void setName(const std::string &name);

    int getHp() const;

    void setHp(int hp);

    int getAttack() const;

    void setAttack(int attack);

    int getDefense() const;

    void setDefense(int defense);

    ~GameCharacter(){};

    void attack(GameCharacter& enemy);

    const std::pair<int, int> &getPosition() const;

    void setPosition(const std::pair<int, int> &position);

    void move_to_position(const std::pair<int, int> &Newpos);


private:

    std::string name;
    int HP,Attack,defense;
    std::pair<int,int> position;

};


#endif //PATHTOGLORY_GAMECHARACTER_H
