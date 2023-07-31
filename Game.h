//
// Created by HP on 31/07/2023.
//

#ifndef PATHTOGLORY_GAME_H
#define PATHTOGLORY_GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Game {
public:
    Game();
    virtual ~Game(){};

    void update();
    void render();
private:
    void initVariables();
    void initWindow();
    sf::RenderWindow* window;
    sf::Event event;


};


#endif //PATHTOGLORY_GAME_H
