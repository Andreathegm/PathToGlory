#include <iostream>
#include <sstream>

#include "GameCharacter.h"
#include "Game.h"
#include "collision.h"
int main() {
    //Init game

    float gridSizeF = 100.f;
    auto gridSizeU = static_cast<unsigned>(gridSizeF);

   //create the map
   GameMap map(20);

   //var for a* alghoritm
    std::vector<sf::Vector2f> bestPath;
    GameTile* start;
    GameTile* destination;
    int currentPathIndex = 0;
    bool isPathComplete = false;
    bool active[]={false , false,false}; // when the first two are set to true a* starts

    // adjustable walls
    GameTile* BlockBlocks;
    GameTile* misclick[]={nullptr, nullptr}; //keep track of the pointer to the block,reset to standard value
     int clickcounter[]={0,0,0}; // for how many times you click the wanting wall block

     // create the Character
    sf::Texture heroTexture;
    Collision::CreateTextureAndBitmask(heroTexture,"C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing1_.png");
    GameCharacter hero(heroTexture, 10, 20, 30, sf::Vector2f(10, 10));
    hero.getGcSprite().scale(sf::Vector2f(0.8,0.8));

    /*sf::CircleShape blocks;
    blocks.setRadius(3);
    blocks.setFillColor(sf::Color::Blue);*/


   /* sf::CircleShape pointer;
    pointer.setRadius(3);
    pointer.setFillColor(sf::Color::Blue);*/

    //animation
    Animation animation(&heroTexture,sf::Vector2u(11,4),0.1);


    // time
    float dt = 0.0;
    sf::Clock dtClock;
    sf::Clock animation_Clock;
    float deltatime;
    float delayTime = 0.5f;

    // several mouse_positions
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    //font and text set up
    sf::Font font;
    font.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/Roboto-Italic.ttf");
    sf::Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10.f, 10.f);
    text.setString("TEST");
    text.setFont(font);

    // walls texture
    sf::Texture obs_text;
    Collision::CreateTextureAndBitmask(obs_text,"C:/Users/HP/CLionProjects/PathToGlory/Resources/NewWall3.png");



    //Init window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PathToGlory");
    window.setFramerateLimit(120);

    //init View
    sf::View view;;
    view.setSize(1920.f, 1080.f);

    //zoom view
    float zoomFactor=1.0f;
    float maxzoom=0.8;
    float minizoom=1.11;
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    float viewspeed = 10.f;
    view.zoom(zoomFactor);
    window.setView(view);


//Init game element

   // tile selector
    sf::RectangleShape tileselector(sf::Vector2f(gridSizeF, gridSizeF));
    tileselector.setFillColor(sf::Color::Transparent);
    tileselector.setOutlineThickness(1.5);

   //main cicle
   animation_Clock.restart();
    while (window.isOpen()) {

        //Update mouse position
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);

        //Check if mousePosView is outside the screen
         if (mousePosView.x >= 0 && mousePosView.x<map.getMapsize()*gridSizeF &&
                 mousePosView.y >= 0 && mousePosView.y<map.getMapsize()*gridSizeF){
             mousePosGrid.x = static_cast<unsigned >(mousePosView.x) / gridSizeU;
             mousePosGrid.y =static_cast<unsigned > (mousePosView.y) / gridSizeU;
             tileselector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
             tileselector.setOutlineColor(sf::Color::Green);

         }
         else{
            tileselector.setOutlineColor(sf::Color::Transparent);
         }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
            view.move(-viewspeed , 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
            view.move(0, -viewspeed );
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
            view.move(0, viewspeed );
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
            view.move(viewspeed , 0);
        }



        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
            if (ev.type == sf::Event::KeyReleased) {
                if (ev.key.code == sf::Keyboard::X) {
                    if (mousePosGrid.x >= 0 && mousePosGrid.x < map.getMapsize() && mousePosGrid.y >= 0 &&
                        mousePosGrid.y < map.getMapsize())
                        BlockBlocks = map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
                    else
                        break;
                    //Check if tile has already been assigned
                    if (!BlockBlocks->isAccessible()) {
                        BlockBlocks->setAccessible(true);
                        BlockBlocks->setVisible(false);

                    }
                    else
                    {
                        //set up variables for the block (aka wall)
                        BlockBlocks->setPos(sf::Vector2f(mousePosGrid.x, mousePosGrid.y));
                        BlockBlocks->setVisible(true);
                        BlockBlocks->setAccessible(false);

                        //if all 8 tile -> draw a tower sprite
                        if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0 &&
                            mousePosGrid.x - 1 >= 0 && mousePosGrid.y + 1 >= 0
                            && mousePosGrid.x + 1 < map.getMapsize() && mousePosGrid.y - 1 < map.getMapsize() &&
                            mousePosGrid.x - 1 < map.getMapsize() && mousePosGrid.y + 1 < map.getMapsize() &&

                            !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y - 1]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y - 1]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y + 1]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y + 1]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible()) {
                            BlockBlocks->setObsSpriteTexture(obs_text, "full");
                            BlockBlocks->setCenter(true);

                            //if both horizontal and vertical not accessible , draw a 4connected wall
                        } else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0
                                   && mousePosGrid.x - 1 >= 0 && mousePosGrid.y + 1 >= 0
                                   && mousePosGrid.x + 1 < map.getMapsize() && mousePosGrid.y - 1 < map.getMapsize() &&
                                   mousePosGrid.x - 1 < map.getMapsize() && mousePosGrid.y + 1 < map.getMapsize() &&
                                   !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isCenter() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isCenter() &&
                                   !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter() &&
                                   !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()) {

                            BlockBlocks->setObsSpriteTexture(obs_text, "4_dir");
                            map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                      "x_dir");
                            map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                      "x_dir");

                        }
                            //Now drawing 3connected wall if 3 tile are not accesible

                            //1) Top
                        else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.x - 1 >= 0 && mousePosGrid.y + 1 >= 0
                                 && mousePosGrid.x + 1 < map.getMapsize() && mousePosGrid.x - 1 < map.getMapsize() &&
                                 mousePosGrid.y + 1 < map.getMapsize() &&
                                 !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()

                                ) {
                            if (mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map.getMapsize() &&
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y - 1]->isAccessible() &&
                                map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y - 1]->isAccessible()) {

                                BlockBlocks->setObsSpriteTexture(obs_text, "3_top");
                                map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                          "x_dir");
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                          "x_dir");
                            } else {
                                BlockBlocks->setObsSpriteTexture(obs_text, "3_top");
                            }

                            //Down
                        } else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.x - 1 >= 0 && mousePosGrid.y - 1 >= 0
                                   && mousePosGrid.x + 1 < map.getMapsize() && mousePosGrid.x - 1 < map.getMapsize() &&
                                   mousePosGrid.y - 1 < map.getMapsize() &&
                                   !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isCenter() &&
                                   !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter() &&
                                   !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()
                                ) {
                            if (mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map.getMapsize() &&
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y + 1]->isAccessible() &&
                                map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y + 1]->isAccessible()) {

                                BlockBlocks->setObsSpriteTexture(obs_text, "3_down");
                                map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                          "x_dir");
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                          "x_dir");
                            } else {
                                BlockBlocks->setObsSpriteTexture(obs_text, "3_down");
                            }
                            //Left
                        } else if (mousePosGrid.x - 1 >= 0 && mousePosGrid.y - 1 >= 0 && mousePosGrid.y + 1 >= 0
                                   && mousePosGrid.x - 1 < map.getMapsize() && mousePosGrid.y - 1 < map.getMapsize() &&
                                   mousePosGrid.y + 1 < map.getMapsize() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                                   !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()
                                ) {
                            BlockBlocks->setObsSpriteTexture(obs_text, "3_left");
                            map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                      "x_dir");


                        }
                            //Right
                        else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0 && mousePosGrid.y + 1 >= 0 &&
                                 mousePosGrid.x + 1 < map.getMapsize() && mousePosGrid.y - 1 < map.getMapsize() &&
                                 mousePosGrid.y + 1 < map.getMapsize() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()
                                ) {
                            BlockBlocks->setObsSpriteTexture(obs_text, "3_right");
                            map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                      "x_dir");

                        }
                            //drawing 2connected wall

                            //1) Right
                        else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0 &&
                                 mousePosGrid.x + 1 < map.getMapsize() && mousePosGrid.y - 1 < map.getMapsize() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()
                                ) {
                            if (mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map.getMapsize() &&
                                map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y + 1]->isAccessible()
                                && map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y - 1]->isAccessible()) {
                                BlockBlocks->setObsSpriteTexture(obs_text, "turn_right");
                                map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                          "x_dir");
                                map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setPos(
                                        sf::Vector2f(mousePosGrid.x + 1, mousePosGrid.y));

                            } else {
                                BlockBlocks->setObsSpriteTexture(obs_text, "turn_right");

                            }
                        }
                            //2) Left_top
                        else if (mousePosGrid.x - 1 >= 0 && mousePosGrid.y + 1 >= 0
                                 && mousePosGrid.x - 1 < map.getMapsize() && mousePosGrid.y + 1 < map.getMapsize() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()) {
                            if (mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map.getMapsize() &&
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y - 1]->isAccessible() &&
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y + 1]->isAccessible()) {
                                BlockBlocks->setObsSpriteTexture(obs_text, "turn_left_top");
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                          "x_dir");
                                map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setPos(
                                        sf::Vector2f(mousePosGrid.x - 1, mousePosGrid.y));
                            } else {
                                BlockBlocks->setObsSpriteTexture(obs_text, "turn_left_top");
                            }

                        }
                            // Left_Bottom
                        else {
                            if (mousePosGrid.x - 1 >= 0 && mousePosGrid.y - 1 >= 0
                                && mousePosGrid.x - 1 < map.getMapsize() && mousePosGrid.y - 1 < map.getMapsize() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isCenter() &&
                                !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()
                                    ) {
                                if (mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map.getMapsize() &&
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y + 1]->isAccessible() &&
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y - 1]->isAccessible()) {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_left");
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                              "x_dir");
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setPos(
                                            sf::Vector2f(mousePosGrid.x - 1, mousePosGrid.y));
                                } else {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_left");

                                }
                            }

                                // Right_Top
                            else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y + 1 >= 0
                                     && mousePosGrid.x + 1 < map.getMapsize() &&
                                     mousePosGrid.y + 1 < map.getMapsize() &&
                                     !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                                     !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                                     !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isCenter() &&
                                     !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()) {
                                if (mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map.getMapsize() &&
                                    map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y - 1]->isAccessible()
                                    && map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y + 1]->isAccessible()) {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_right_top");
                                    map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                              "x_dir");
                                    map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setPos(
                                            sf::Vector2f(mousePosGrid.x + 1, mousePosGrid.y));
                                } else {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_right_top");

                                }
                            }

                                // X_direction_right
                            else if (mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map.getMapsize() &&
                                     mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map.getMapsize() &&
                                     mousePosGrid.x - 1 >= 0 && mousePosGrid.x - 1 < map.getMapsize() &&
                                     mousePosGrid.x + 1 >= 0 && mousePosGrid.x + 1 < map.getMapsize() &&
                                     !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                                     !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isCenter() &&
                                     !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isCenter() &&
                                     !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter() &&
                                     !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()
                                    ) {
                                if (!map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y + 1]->isAccessible()
                                    || !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y - 1]->isAccessible())
                                    BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");

                                else {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                              "x_dir");
                                }
                            }
                                //X_direction_left
                            else if (mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map.getMapsize() &&
                                     mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map.getMapsize() &&
                                     mousePosGrid.x + 1 >= 0 && mousePosGrid.x + 1 < map.getMapsize() &&
                                     !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                                     !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isCenter() &&
                                     !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isCenter() &&
                                     !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()
                                    ) {

                                if ((!map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y - 1]->isAccessible()
                                     || !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y + 1]->isAccessible())) {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                                } else {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                                    map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                                                              "x_dir");

                                }

                            } //Straight wall between two obstacles
                            else if (mousePosGrid.x - 1 >= 0 && mousePosGrid.x - 1 < map.getMapsize() &&
                                     mousePosGrid.x + 1 >= 0 && mousePosGrid.x + 1 < map.getMapsize() &&
                                     !map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible()
                                     && !map.getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible()) {
                                BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");

                            } else if (mousePosGrid.y == 0 || mousePosGrid.y == map.getMapsize() - 1) {
                                if (mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map.getMapsize() &&
                                    !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible()) {
                                    BlockBlocks->setObsSpriteTexture(obs_text);
                                } else {
                                    if (mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map.getMapsize() &&
                                        !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible())
                                        BlockBlocks->setObsSpriteTexture(obs_text);
                                    else {
                                        BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                                    }
                                }
                            } else {
                                BlockBlocks->setObsSpriteTexture(obs_text);
                            }

                        }

                    }
                }
                else {

                    if (ev.key.code == sf::Keyboard::B){
                        zoomFactor *= 0.98;
                        if(zoomFactor>maxzoom)
                            zoomFactor=maxzoom;
                        view.zoom(zoomFactor);
                        }
                    else if(ev.key.code == sf::Keyboard::N){
                        zoomFactor *= 1.06;
                        if( zoomFactor<minizoom)
                          zoomFactor=minizoom;
                        view.zoom(zoomFactor);

                    }


                }



            }
        }



        //start hero path
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            if(clickcounter[0]==1){
                misclick[0]->getTile().setFillColor(sf::Color::White);
                clickcounter[0]=0;
            }
            //Check if the start position is allowed
            if(mousePosView.x >= 0 && mousePosView.x<map.getMapsize()*gridSizeF &&
               mousePosView.y >= 0 && mousePosView.y<map.getMapsize()*gridSizeF){
            start = map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
            if(start->isAccessible()) {
                misclick[0] = start;
                start->getTile().setFillColor(sf::Color::Blue);
                mousePosGrid.x *= gridSizeU;
                mousePosGrid.x += gridSizeU / 4;
                mousePosGrid.y *= gridSizeU;
                hero.setPosition(static_cast<sf::Vector2f>(mousePosGrid));
                active[0] = true;
                clickcounter[0]++;
            }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if(clickcounter[1]==1){
                misclick[1]->getTile().setFillColor(sf::Color::White);
                clickcounter[1]=0;
            }
            destination=map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
            misclick[1]=destination;
            destination->getTile().setFillColor(sf::Color::Red);
            active[1]=true;
            clickcounter[1]++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            map.reset();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            map.reset(true);
        if(active[0] && active[1]) {
            bestPath = map.aStar(start, destination);

            if (!isPathComplete) {
                // Ottieni il tempo trascorso fin dall'ultima chiamata di restart()
                float elapsedTime = dtClock.getElapsedTime().asSeconds();

                // Esegui il corpo del ciclo solo se è passato almeno 0.5 secondi
                if (elapsedTime >= delayTime) {
                    if (currentPathIndex < bestPath.size()) {
                        // Effettua qui le operazioni del ciclo che desideri eseguire con l'intervallo desiderato
                        hero.setPosition(sf::Vector2f(bestPath[currentPathIndex].x * gridSizeF,
                                                      bestPath[currentPathIndex].y * gridSizeF));
                        map.getTilemap()[bestPath[currentPathIndex].x][bestPath[currentPathIndex].y]->getTile().setFillColor(sf::Color::Green);
                        // Incrementa l'indice per passare alla prossima posizione nel vettore path
                        currentPathIndex++;

                        // Resetta il timer per il prossimo intervallo
                        dtClock.restart().asSeconds();
                    } else {
                        // Il percorso è terminato, imposta la variabile di completamento a true
                        isPathComplete = true;
                        currentPathIndex=0;
                        active[2]= true;
                    }
                }
            }
        }
    if(active[2]) {
       // map.reset();
        for(bool & i : active)
            i=false;
        isPathComplete= false;
    }



       //update game elements
        //update UI
        std::stringstream ss;
        ss << "Screen " << mousePosScreen.x << " " << mousePosScreen.y << "\n" <<
           "Window " << mousePosWindow.x << " " << mousePosWindow.y << std::endl <<
           "View " << mousePosView.x << " " << mousePosView.y << std::endl <<
           "Grid " << mousePosGrid.x << " " << mousePosGrid.y << std::endl;

        text.setString(ss.str());
        //events

       // Input for moving the hero
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            deltatime=animation_Clock.getElapsedTime().asSeconds();
            animation.Update(0,deltatime);
            if(deltatime>=0.1)
                animation_Clock.restart();
            hero.setPosition(sf::Vector2f(hero.getPosition().x,hero.getPosition().y-1));
            sf::Vector2f actual_pos(hero.getPosition());
            auto collision = actual_pos.x+hero.getGcSprite().getGlobalBounds().width/2;
            auto collisiony= actual_pos.y;
            if(collision>0 && collision<map.getMapsize()*gridSizeF &&
               collisiony>0 && collisiony<map.getMapsize()*gridSizeF &&
               !map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->isAccessible()){
                if(Collision::PixelPerfectTest(hero.getGcSprite(),map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->getObsSprite()))
                    hero.setPosition(sf::Vector2f (actual_pos.x,actual_pos.y+1));


            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            deltatime=animation_Clock.getElapsedTime().asSeconds();
            animation.Update(3,deltatime);
            if(deltatime>=0.1)
                animation_Clock.restart();
            hero.setPosition(sf::Vector2f(hero.getPosition().x-1,hero.getPosition().y));

            sf::Vector2f actual_pos(hero.getPosition());
            auto collision = actual_pos.x;
            auto collisiony= actual_pos.y+hero.getGcSprite().getGlobalBounds().height/2;
            if(collision>0 && collision<map.getMapsize()*gridSizeF &&
               collisiony>0 && collisiony<map.getMapsize()*gridSizeF &&
               !map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->isAccessible()){
                if(Collision::PixelPerfectTest(hero.getGcSprite(),map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->getObsSprite()))
                    hero.setPosition(sf::Vector2f (actual_pos.x+1,actual_pos.y));


            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            deltatime=animation_Clock.getElapsedTime().asSeconds();
            animation.Update(2,deltatime);
            if(deltatime>=0.1)
                animation_Clock.restart();
            hero.setPosition(sf::Vector2f(hero.getPosition().x,hero.getPosition().y+1));

            sf::Vector2f actual_pos(hero.getPosition());
            auto collision = actual_pos.x+hero.getGcSprite().getGlobalBounds().width/2;
            auto collisiony= actual_pos.y+hero.getGcSprite().getGlobalBounds().height;
            if(collision>0 && collision<map.getMapsize()*gridSizeF &&
               collisiony>0 && collisiony<map.getMapsize()*gridSizeF &&
               !map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->isAccessible()){
                if(Collision::PixelPerfectTest(hero.getGcSprite(),map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->getObsSprite()))
                    hero.setPosition(sf::Vector2f (actual_pos.x,actual_pos.y-1));


            }

        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            deltatime=animation_Clock.getElapsedTime().asSeconds();
            animation.Update(1,deltatime);
            if(deltatime>=0.1)
                animation_Clock.restart();
            hero.setPosition(sf::Vector2f(hero.getPosition().x+1,hero.getPosition().y));
            auto actual_pos=hero.getPosition();
            auto collision = actual_pos.x+hero.getGcSprite().getGlobalBounds().width;
            auto collisiony= actual_pos.y+hero.getGcSprite().getGlobalBounds().height/2;
            if(collision>0 && collision<map.getMapsize()*gridSizeF &&
               collisiony>0 && collisiony<map.getMapsize()*gridSizeF &&
               !map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->isAccessible()){
                if(Collision::PixelPerfectTest(hero.getGcSprite(),map.getTilemap()[collision/gridSizeU][collisiony/gridSizeU]->getObsSprite()))
                    hero.setPosition(sf::Vector2f (actual_pos.x-1,actual_pos.y));
            }
            //check right collision with grid
            if(static_cast<unsigned >(hero.getPosition().x)/gridSizeU==map.getMapsize()-1){
            if(actual_pos.x+hero.getGcSprite().getGlobalBounds().width>2008)
            hero.setPosition(sf::Vector2f (hero.getPosition().x-1,hero.getPosition().y));}
        }



        //Update Animation
       sf::IntRect rectangle{

               static_cast<int>(animation.uvRect.left),
               static_cast<int>(animation.uvRect.top),
               static_cast<int>(animation.uvRect.width),
               static_cast<int>(animation.uvRect.height ),

       };


      hero.setTexturerect(rectangle);
      //Collision with the grid

      //Check left collision
      if(hero.getPosition().x<map.getTilemap()[0][hero.getPosition().y/gridSizeU]->getPos().x)
          hero.setPosition(sf::Vector2f (0,hero.getPosition().y));
      // Check top_grid collision
      if(hero.getPosition().y<map.getTilemap()[hero.getPosition().x/gridSizeU][0]->getPos().y)
            hero.setPosition(sf::Vector2f (hero.getPosition().x,0));
      // Check down_grid collision
      if(hero.getPosition().y/gridSizeU==map.getMapsize()-1 && hero.getPosition().y+hero.getGcSprite().getGlobalBounds().height>map.getTilemap()[map.getMapsize()-1][hero.getPosition().y/gridSizeU]->getPos().y+
      map.getTilemap()[map.getMapsize()-1][hero.getPosition().y/gridSizeU]->getTile().getGlobalBounds().height)
            hero.setPosition(sf::Vector2f (hero.getPosition().x,hero.getPosition().y-1));



        //render
        window.clear();
        //render game elements,drawing

        window.setView(view);

        map.draw(window);

        hero.draw(window);

        window.draw(tileselector);
        //render Ui

        window.setView(window.getDefaultView());

        window.draw(text);

        //done drawing
        window.display();

    }
}