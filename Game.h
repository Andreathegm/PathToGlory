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
#include "GameCharacter.h"

class Game {
public:
    //Constructor and destructor & setup
    Game(unsigned width,unsigned height);
    Game();
    virtual ~Game();
    void Linkmap(GameMap* map);

    //METHODS

    //game open-close
    const bool IsRunning();
    void close();

    //Events
    bool pollEvent();
    virtual void pollEvents(sf::Vector2u & mousePosGrid,GameTile* BlockBlocks,sf::Texture& obs_text,bool& walking,float&zoomfactor,sf::View& view);
    bool TileSelectorBoundaries(sf::Vector2f mousePosView);
    void handleWallPlacement(sf::Vector2u & mousePosGrid,GameTile* BlockBlocks,sf::Texture& obs_text);//Change texture of the wall
    //from the surrounding


    //render
    void clear();
    void draw(sf::Drawable& drawable);
    void draw(GameMap map);
    void display();

    //GETTER AND SETTER

    //getter and setter for View
    void setView(sf::View& view);
    sf::View getDefaultView();
    sf::View getView() ;
    void SetWindow(sf::RenderWindow* new_window);

    //getter for the window
    const sf::VideoMode &getVideoMode() const;
    sf::RenderWindow &getWindow();
    
    const sf::Event &getEvent() const;

    void setEvent(const sf::Event &event);

private:
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;
    GameMap* map;
    sf::View view;
};


#endif //PATHTOGLORY_GAME_H
