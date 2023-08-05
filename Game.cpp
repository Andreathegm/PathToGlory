//
// Created by HP on 31/07/2023.
//

#include "Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
  /*  for(int i=0;i<map.getGridLenght();i++){
        for(int j=0;j<map.getGridLenght();j++){
            window->draw(map.getTiles()[i][j]->getSprite());
        }
    }*/

}
Game::~Game() {
    delete window;
}

void Game::update() {
    pollEvents();

}

void Game::render() {
    window->clear(sf::Color(230,0,0,255));
    window->display();



}

void Game::initVariables() {
    window= nullptr;


}

void Game::initWindow() {
    videoMode.width=1920;
    videoMode.height=1080;
    window= new sf::RenderWindow(sf::VideoMode(videoMode),"PathToGlory",sf::Style::Titlebar |  sf::Style::Close);


}

const bool Game::IsRunning() {
    return window->isOpen();
}

void Game::pollEvents() {
    while(window->pollEvent(event)){
        switch(event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::Escape)
                    window->close();
                break;
        }
    }

}

