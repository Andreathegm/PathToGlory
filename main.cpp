#include <iostream>
#include <sstream>

#include "GameCharacter.h"
#include "Game.h"
#include "collision.h"
#include "MainMenu.h"
int main() {
    //Init game

    float gridSizeF = 100.f;
    auto gridSizeU = static_cast<unsigned>(gridSizeF);

    //create the map
    GameMap map(20);

    //var for a* alghoritm
    std::vector<sf::Vector2f> bestPath;
    GameTile *start;
    GameTile *destination;
    int currentPathIndex = 0;
    bool isPathComplete = false;
    bool active[] = {false, false, false}; // when the first two are set to true a* starts

    // adjustable walls
    //GameTile *BlockBlocks;
    GameTile *BlockBlocks= nullptr;
    GameTile *misclick[] = {nullptr, nullptr}; //keep track of the pointer to the block,reset to standard value
    int clickcounter[] = {0, 0, 0}; // for how many times you click the wanting wall block

    // create the Character
    sf::Texture heroTexture;
    Collision::CreateTextureAndBitmask(heroTexture,"C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing2_.png");
    GameCharacter hero(heroTexture, sf::Vector2f(10, 10),&map);
    hero.getGcSprite().scale(sf::Vector2f(0.8, 0.8));




    bool walking = false;


    // time
    float dt = 0.0;
    sf::Clock dtClock;
    float delayTime = 0.5f;
    sf::Clock animation_Clock;
    float deltatime;

    // several mouse_positions
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    //FONT AND TEXT SET UP
    sf::Font font;
    font.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/Roboto-Italic.ttf");
    sf::Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10.f, 10.f);
    text.setString("TEST");
    text.setFont(font);

    //WALL TEXTURE
    sf::Texture obs_text;
    Collision::CreateTextureAndBitmask(obs_text, "C:/Users/HP/CLionProjects/PathToGlory/Resources/NewWall3.png");

    //Init MainWindow
    sf::RenderWindow MainWindow(sf::VideoMode(1920, 1080), "Main Menu' ", sf::Style::Default);
    MainMenu mainMenu(MainWindow.getSize().x, MainWindow.getSize().y);


    //Init BackgroundGridTexture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/background2.jpg"))
        return -1;
    sf::Sprite BackgroundSprite(backgroundTexture);
    BackgroundSprite.setScale(map.getMapsize() * gridSizeU / BackgroundSprite.getGlobalBounds().width,
                              map.getMapsize() * gridSizeU / BackgroundSprite.getGlobalBounds().height);


   //BackgroundTexture for main menu
   sf::Texture TextureMenu;
   if(!TextureMenu.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/PathB.png"))
       return -1;
   sf::Sprite  BackgroudMenu;
   BackgroudMenu.setPosition(0,0);
   BackgroudMenu.setTexture(TextureMenu);


   //BackgroundTexture for CommandWin
    sf::Texture TextureCommand;
    if(!TextureCommand.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/CommandWin.png"))
        return -1;
    sf::Sprite  BackCommands;
    BackCommands.setPosition(0,0);
    BackCommands.setTexture(TextureCommand);

    //init View
    sf::View view;
    view.setSize(1920.f, 1080.f);

    //zoom view
    float zoomFactor = 1.0f;
    float viewspeed = 2.f;
    view.zoom(zoomFactor);




//Init game element

    // tile selector
    sf::RectangleShape tileselector(sf::Vector2f(gridSizeF, gridSizeF));
    tileselector.setFillColor(sf::Color::Transparent);
    tileselector.setOutlineThickness(1.5);

    //Whole game cicle start
    while (MainWindow.isOpen()) {
        sf::Event event;
        while (MainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                MainWindow.close();

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up)
                    mainMenu.moveUp();

                if (event.key.code == sf::Keyboard::Down)
                    mainMenu.moveDown();

                if (event.key.code == sf::Keyboard::Return) {
                    sf::RenderWindow COMMANDS(sf::VideoMode(1920, 1080), "Commanads");
                    Game game(1920, 1080);
                    game.Linkmap(&map);
                    game.getView().setCenter(game.getVideoMode().width / 2, game.getVideoMode().height / 2);
                    game.setView(view);

                    //wheter you have selected open different window
                    int selection = mainMenu.MainMenuSelected();
                    if (selection == 0) {


                        //Game cicle
                        animation_Clock.restart();
                        while (game.IsRunning()) {
                            mousePosScreen = sf::Mouse::getPosition();
                            mousePosWindow = sf::Mouse::getPosition(game.getWindow());
                            game.setView(view);
                            mousePosView = game.getWindow().mapPixelToCoords(mousePosWindow);

                            if (game.TileSelectorBoundaries(mousePosView)) {
                                mousePosGrid.x = static_cast<unsigned >(mousePosView.x) / gridSizeU;
                                mousePosGrid.y = static_cast<unsigned > (mousePosView.y) / gridSizeU;
                                tileselector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
                                tileselector.setOutlineColor(sf::Color::Green);
                            } else {
                                tileselector.setOutlineColor(sf::Color::Transparent);
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
                                view.move(-viewspeed, 0);
                            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
                                view.move(0, -viewspeed);
                            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
                                view.move(0, viewspeed);
                            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
                                view.move(viewspeed, 0);
                            }
                          //  sf::Event ev;
                            while(game.pollEvent())
                            game.pollEvents(mousePosGrid, BlockBlocks, obs_text,walking,zoomFactor,view);



                            //start hero path
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                                if (clickcounter[0] == 1) {
                                    misclick[0]->getTile().setFillColor(sf::Color::Transparent);
                                    clickcounter[0] = 0;
                                }
                                //Check if the start position is allowed
                                if (mousePosView.x >= 0 && mousePosView.x < map.getMapsize() * gridSizeF &&
                                    mousePosView.y >= 0 && mousePosView.y < map.getMapsize() * gridSizeF) {

                                    start = map.getTilemap()[mousePosGrid.x][mousePosGrid.y];

                                    if (start->isAccessible()) {
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
                                if (clickcounter[1] == 1) {
                                    misclick[1]->getTile().setFillColor(sf::Color::Transparent);
                                    clickcounter[1] = 0;
                                }
                                if (map.getTilemap()[mousePosGrid.x][mousePosGrid.y]->isAccessible()) {

                                    destination = map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
                                    misclick[1] = destination;
                                    destination->getTile().setFillColor(sf::Color::Red);
                                    active[1] = true;
                                    clickcounter[1]++;
                                }
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                                map.reset();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                                map.reset(true);

                            //if both start and destination have been selected
                            if (active[0] && active[1]) {
                                bestPath = map.aStar(start, destination);

                                if (!isPathComplete) {
                                    // obtain elapsed time from latest call to restart
                                    float elapsedTime = dtClock.getElapsedTime().asSeconds();


                                    if (elapsedTime >= delayTime) {
                                        if (currentPathIndex < bestPath.size()) {

                                            hero.setPosition(sf::Vector2f(bestPath[currentPathIndex].x * gridSizeF,
                                                                          bestPath[currentPathIndex].y * gridSizeF));

                                            map.getTilemap()[bestPath[currentPathIndex].x][bestPath[currentPathIndex].y]->getTile().setFillColor(
                                                    sf::Color::Green);
                                            // Increment Path Index to move to next position
                                            currentPathIndex++;

                                            //restart timer for next interval
                                            dtClock.restart().asSeconds();
                                        } else {
                                            //Path is complete , reset flags for other following paths
                                            isPathComplete = true;
                                            currentPathIndex = 0;
                                            active[2] = true;

                                        }
                                    }
                                }
                            }
                            if (active[2]) {
                                for (bool &i: active)
                                    i = false;
                                isPathComplete = false;
                            }

                            //update UI
                            std::stringstream ss;
                            ss << "Screen " << mousePosScreen.x << " " << mousePosScreen.y << "\n" <<
                               "Window " << mousePosWindow.x << " " << mousePosWindow.y << std::endl <<
                               "View " << mousePosView.x << " " << mousePosView.y << std::endl <<
                               "Grid " << mousePosGrid.x << " " << mousePosGrid.y << std::endl;

                            text.setString(ss.str());

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                                walking = true;
                                deltatime = animation_Clock.getElapsedTime().asSeconds();

                                hero.UpdateAnimation(0, deltatime);
                                if (deltatime >= 0.1)
                                    animation_Clock.restart();
                                hero.move("W");
                                hero.collision(hero.getGcSprite().getGlobalBounds().width / 2, 0);

                            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                                walking = true;
                                deltatime = animation_Clock.getElapsedTime().asSeconds();
                                hero.UpdateAnimation(3, deltatime);

                                if (deltatime >= 0.1)
                                    animation_Clock.restart();

                                hero.move("A");
                                hero.collision(0, hero.getGcSprite().getGlobalBounds().height / 2);

                            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                                walking = true;
                                deltatime = animation_Clock.getElapsedTime().asSeconds();
                                hero.UpdateAnimation(2, deltatime);

                                if (deltatime >= 0.1)
                                    animation_Clock.restart();

                                hero.move("S");
                                hero.collision(hero.getGcSprite().getGlobalBounds().width / 2,
                                               hero.getGcSprite().getGlobalBounds().height, true);

                            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                                walking = true;
                                deltatime = animation_Clock.getElapsedTime().asSeconds();
                                hero.UpdateAnimation(1, deltatime);

                                if (deltatime >= 0.1)
                                    animation_Clock.restart();

                                hero.move("D");

                                auto actual_pos = hero.getPosition();
                                hero.collision(hero.getGcSprite().getGlobalBounds().width,
                                               hero.getGcSprite().getGlobalBounds().height / 2);

                                //check right collison  with right edge of the  grid
                                if (static_cast<unsigned >(hero.getPosition().x) / gridSizeU == map.getMapsize() - 1) {
                                    if (actual_pos.x + hero.getGcSprite().getGlobalBounds().width > 2008)
                                        hero.setPosition(sf::Vector2f(hero.getPosition().x - 1, hero.getPosition().y));
                                }
                            }



                            //Update Animation
                            sf::IntRect rectangle{
                                    static_cast<int>(hero.getAnimation()->uvRect.left),
                                    static_cast<int>(hero.getAnimation()->uvRect.top),
                                    static_cast<int>(hero.getAnimation()->uvRect.width),
                                    static_cast<int>(hero.getAnimation()->uvRect.height ),

                            };


                            hero.setTexturerect(rectangle);

                            hero.GridCollision();

                            //if hero is walking set view on him
                            if (walking) {
                                view.setCenter(hero.getPosition().x, hero.getPosition().y);
                                tileselector.setOutlineColor(sf::Color::Transparent);
                            }

                            COMMANDS.close();
                            game.clear();

                            //render game elements,drawing
                            game.setView(view);
                            game.getWindow().draw(BackgroundSprite);
                            map.draw(game.getWindow());
                            game.draw(hero.getGcSprite());

                            game.draw(tileselector);
                            game.draw(text);
                            auto def_View = game.getDefaultView();
                            game.setView(def_View);
                            //done drawing
                            game.display();

                        }
                    }
                    else if (selection == 1) {
                        while (COMMANDS.isOpen()) {
                            sf::Event ev;
                            while (COMMANDS.pollEvent(ev)) {
                                if(ev.type==sf::Event::Closed)
                                    COMMANDS.close();
                            }

                          //  window.close();
                            game.close();
                            COMMANDS.clear();
                            COMMANDS.draw(BackCommands);
                            COMMANDS.display();

                        }

                    }
                    if (selection == 2) {
                        MainWindow.close();
                        break;
                    }
                }
            }
        }
        MainWindow.clear();
        MainWindow.draw(BackgroudMenu);
        mainMenu.Draw(MainWindow);
        MainWindow.display();
    }

}