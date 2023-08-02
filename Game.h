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

#include "GameMap.h"
class Game {
public:
    Game();
    virtual ~Game();
    void update();
    void render();
    const bool IsRunning();
    void pollEvents();

    GameMap *getMap() const;

private:
    void initVariables();
    void initWindow();
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;
    GameMap* map;
};


#endif //PATHTOGLORY_GAME_H
