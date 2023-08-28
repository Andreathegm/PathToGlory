//
// Created by HP on 31/07/2023.
//

#include "Game.h"

Game::Game(unsigned width,unsigned height) : window(new sf::RenderWindow(sf::VideoMode(width,height),"PathToGlory",sf::Style::Titlebar |  sf::Style::Close)) {
    videoMode.width=width;
    videoMode.height=height;
    map= nullptr;
}

Game::~Game() {}

void Game::display() {
    window->display();

}

const bool Game::IsRunning() {
    return window->isOpen();
}

void Game::pollEvents(sf::Vector2u& mousePosGrid,GameTile* BlockBlocks,sf::Texture& obs_text,bool& walking,float&zoomfactor,sf::View& view) {
        switch(event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::Escape)
                    window->close();
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A ||
                    event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D)
                    walking=false;
                    if(event.key.code==sf::Keyboard::X)
                        handleWallPlacement( mousePosGrid,BlockBlocks,obs_text);
                float maxzoom = 0.8;
                float minizoom = 1.11;
                if (event.key.code == sf::Keyboard::B) {
                    zoomfactor *= 0.98;
                    if (zoomfactor > maxzoom)
                        zoomfactor = maxzoom;
                    view.zoom(zoomfactor);
                } else if(event.key.code == sf::Keyboard::N) {
                    zoomfactor *= 1.06;
                    if (zoomfactor < minizoom)
                        zoomfactor = minizoom;
                    view.zoom(zoomfactor);

                }


        }


}

void Game::draw(sf::Drawable& drawable)  {
    window->draw(drawable);


}

void Game::draw(GameMap map) {
    map.draw(*window);

}

void Game::Linkmap(GameMap* map) {
    this->map=map;


}

bool Game::TileSelectorBoundaries(sf::Vector2f mousePosView) {
    auto gridSizeF= map->getTilemap()[0][0]->getGridSizeF();
    if (mousePosView.x >= 0 && mousePosView.x < map->getMapsize() * gridSizeF &&
        mousePosView.y >= 0 && mousePosView.y < map->getMapsize() * gridSizeF)
        return true;
    return false;
}



void Game::handleWallPlacement(sf::Vector2u & mousePosGrid, GameTile *BlockBlocks,sf::Texture& obs_text ) {
        if (mousePosGrid.x >= 0 && mousePosGrid.x < map->getMapsize() &&
            mousePosGrid.y >= 0 &&
            mousePosGrid.y < map->getMapsize()&& map->getTilemap()[mousePosGrid.x]
            [mousePosGrid.y]->getTile().getFillColor()!=sf::Color::Blue &&
            map->getTilemap()[mousePosGrid.x]
            [mousePosGrid.y]->getTile().getFillColor()!=sf::Color::Red)
            BlockBlocks = map->getTilemap()[mousePosGrid.x][mousePosGrid.y];
        else
            return;

        //Check if tile has already been assigned
        if (!BlockBlocks->isAccessible()) {
            BlockBlocks->setAccessible(true);
            BlockBlocks->setVisible(false);

        } else {
            //set up variables for the block (aka wall)
            BlockBlocks->setPos(sf::Vector2f(mousePosGrid.x, mousePosGrid.y));
            BlockBlocks->setVisible(true);
            BlockBlocks->setAccessible(false);

            //if all 8 tile -> draw a tower sprite
            if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0 &&
                mousePosGrid.x - 1 >= 0 && mousePosGrid.y + 1 >= 0
                && mousePosGrid.x + 1 < map->getMapsize() &&
                mousePosGrid.y - 1 < map->getMapsize() &&
                mousePosGrid.x - 1 < map->getMapsize() &&
                mousePosGrid.y + 1 < map->getMapsize() &&

                !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isAccessible() &&
                !map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isAccessible() &&
                !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y -
                                                      1]->isAccessible() &&
                !map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y -
                                                      1]->isAccessible() &&
                !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y +
                                                      1]->isAccessible() &&
                !map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y +
                                                      1]->isAccessible() &&
                !map->getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible() &&
                !map->getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible()) {
                BlockBlocks->setObsSpriteTexture(obs_text, "full");
                BlockBlocks->setCenter(true);

                //if both horizontal and vertical not accessible , draw a 4connected wall
            } else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0
                       && mousePosGrid.x - 1 >= 0 && mousePosGrid.y + 1 >= 0
                       && mousePosGrid.x + 1 < map->getMapsize() &&
                       mousePosGrid.y - 1 < map->getMapsize() &&
                       mousePosGrid.x - 1 < map->getMapsize() &&
                       mousePosGrid.y + 1 < map->getMapsize() &&
                       !map->getTilemap()[mousePosGrid.x +
                                         1][mousePosGrid.y]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x -
                                         1][mousePosGrid.y]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                         1]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                         1]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                         1]->isCenter() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                         1]->isCenter() &&
                       !map->getTilemap()[mousePosGrid.x +
                                         1][mousePosGrid.y]->isCenter() &&
                       !map->getTilemap()[mousePosGrid.x -
                                         1][mousePosGrid.y]->isCenter()) {

                BlockBlocks->setObsSpriteTexture(obs_text, "4_dir");
                map->getTilemap()[mousePosGrid.x +
                                 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                         "x_dir");
                map->getTilemap()[mousePosGrid.x -
                                 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                         "x_dir");

            }
                //Now drawing 3connected wall if 3 tile are not accesible

                //1) Top
            else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.x - 1 >= 0 &&
                     mousePosGrid.y + 1 >= 0
                     && mousePosGrid.x + 1 < map->getMapsize() &&
                     mousePosGrid.x - 1 < map->getMapsize() &&
                     mousePosGrid.y + 1 < map->getMapsize() &&
                     !map->getTilemap()[mousePosGrid.x +
                                       1][mousePosGrid.y]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                       1]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x -
                                       1][mousePosGrid.y]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                       1]->isCenter() &&
                     !map->getTilemap()[mousePosGrid.x -
                                       1][mousePosGrid.y]->isCenter() &&
                     !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()

                    ) {
                if (mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map->getMapsize() &&
                    map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y -
                                                         1]->isAccessible() &&
                    map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y -
                                                         1]->isAccessible()) {

                    BlockBlocks->setObsSpriteTexture(obs_text, "3_top");
                    map->getTilemap()[mousePosGrid.x +
                                     1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                             "x_dir");
                    map->getTilemap()[mousePosGrid.x -
                                     1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                             "x_dir");
                } else {
                    BlockBlocks->setObsSpriteTexture(obs_text, "3_top");
                }

                //Down
            } else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.x - 1 >= 0 &&
                       mousePosGrid.y - 1 >= 0
                       && mousePosGrid.x + 1 < map->getMapsize() &&
                       mousePosGrid.x - 1 < map->getMapsize() &&
                       mousePosGrid.y - 1 < map->getMapsize() &&
                       !map->getTilemap()[mousePosGrid.x +
                                         1][mousePosGrid.y]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                         1]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x -
                                         1][mousePosGrid.y]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                         1]->isCenter() &&
                       !map->getTilemap()[mousePosGrid.x +
                                         1][mousePosGrid.y]->isCenter() &&
                       !map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()
                    ) {
                if (mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map->getMapsize() &&
                    map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y +
                                                         1]->isAccessible() &&
                    map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y +
                                                         1]->isAccessible()) {

                    BlockBlocks->setObsSpriteTexture(obs_text, "3_down");
                    map->getTilemap()[mousePosGrid.x +
                                     1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                             "x_dir");
                    map->getTilemap()[mousePosGrid.x -
                                     1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                             "x_dir");
                } else {
                    BlockBlocks->setObsSpriteTexture(obs_text, "3_down");
                }
                //Left
            } else if (mousePosGrid.x - 1 >= 0 && mousePosGrid.y - 1 >= 0 &&
                       mousePosGrid.y + 1 >= 0
                       && mousePosGrid.x - 1 < map->getMapsize() &&
                       mousePosGrid.y - 1 < map->getMapsize() &&
                       mousePosGrid.y + 1 < map->getMapsize() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                         1]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                         1]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x -
                                         1][mousePosGrid.y]->isAccessible() &&
                       !map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()
                    ) {
                BlockBlocks->setObsSpriteTexture(obs_text, "3_left");
                map->getTilemap()[mousePosGrid.x -
                                 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                         "x_dir");


            }
                //Right
            else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0 &&
                     mousePosGrid.y + 1 >= 0 &&
                     mousePosGrid.x + 1 < map->getMapsize() &&
                     mousePosGrid.y - 1 < map->getMapsize() &&
                     mousePosGrid.y + 1 < map->getMapsize() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                       1]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                       1]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x +
                                       1][mousePosGrid.y]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()
                    ) {
                BlockBlocks->setObsSpriteTexture(obs_text, "3_right");
                map->getTilemap()[mousePosGrid.x +
                                 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                         "x_dir");

            }
                //drawing 2connected wall

                //1) Right
            else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y - 1 >= 0 &&
                     mousePosGrid.x + 1 < map->getMapsize() &&
                     mousePosGrid.y - 1 < map->getMapsize() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                       1]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x +
                                       1][mousePosGrid.y]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                       1]->isCenter() &&
                     !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->isCenter()
                    ) {
                if (mousePosGrid.y + 1 >= 0 && mousePosGrid.y + 1 < map->getMapsize() &&
                    map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y +
                                                         1]->isAccessible()
                    && map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y -
                                                            1]->isAccessible()) {
                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_right");
                    map->getTilemap()[mousePosGrid.x +
                                     1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                             "x_dir");
                    map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setPos(
                            sf::Vector2f(mousePosGrid.x + 1, mousePosGrid.y));

                } else {
                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_right");

                }
            }
                //2) Left_top
            else if (mousePosGrid.x - 1 >= 0 && mousePosGrid.y + 1 >= 0
                     && mousePosGrid.x - 1 < map->getMapsize() &&
                     mousePosGrid.y + 1 < map->getMapsize() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                       1]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x -
                                       1][mousePosGrid.y]->isAccessible() &&
                     !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                       1]->isCenter() &&
                     !map->getTilemap()[mousePosGrid.x -
                                       1][mousePosGrid.y]->isCenter()) {
                if (mousePosGrid.y - 1 >= 0 && mousePosGrid.y - 1 < map->getMapsize() &&
                    map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y -
                                                         1]->isAccessible() &&
                    map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y +
                                                         1]->isAccessible()) {
                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_left_top");
                    map->getTilemap()[mousePosGrid.x -
                                     1][mousePosGrid.y]->setObsSpriteTexture(obs_text,
                                                                             "x_dir");
                    map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setPos(
                            sf::Vector2f(mousePosGrid.x - 1, mousePosGrid.y));
                } else {
                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_left_top");
                }

            }
                // Left_Bottom
            else {
                if (mousePosGrid.x - 1 >= 0 && mousePosGrid.y - 1 >= 0
                    && mousePosGrid.x - 1 < map->getMapsize() &&
                    mousePosGrid.y - 1 < map->getMapsize() &&
                    !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                      1]->isAccessible() &&
                    !map->getTilemap()[mousePosGrid.x -
                                      1][mousePosGrid.y]->isAccessible() &&
                    !map->getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isCenter() &&
                    !map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->isCenter()
                        ) {
                    if (mousePosGrid.y + 1 >= 0 &&
                        mousePosGrid.y + 1 < map->getMapsize() &&
                        map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y +
                                                             1]->isAccessible() &&
                        map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y -
                                                             1]->isAccessible()) {
                        BlockBlocks->setObsSpriteTexture(obs_text, "turn_left");
                        map->getTilemap()[mousePosGrid.x -
                                         1][mousePosGrid.y]->setObsSpriteTexture(
                                obs_text,
                                "x_dir");
                        map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setPos(
                                sf::Vector2f(mousePosGrid.x - 1, mousePosGrid.y));
                    } else {
                        BlockBlocks->setObsSpriteTexture(obs_text, "turn_left");

                    }
                }

                    // Right_Top
                else if (mousePosGrid.x + 1 >= 0 && mousePosGrid.y + 1 >= 0
                         && mousePosGrid.x + 1 < map->getMapsize() &&
                         mousePosGrid.y + 1 < map->getMapsize() &&
                         !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                           1]->isAccessible() &&
                         !map->getTilemap()[mousePosGrid.x +
                                           1][mousePosGrid.y]->isAccessible() &&
                         !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                           1]->isCenter() &&
                         !map->getTilemap()[mousePosGrid.x +
                                           1][mousePosGrid.y]->isCenter()) {
                    if (mousePosGrid.y - 1 >= 0 &&
                        mousePosGrid.y - 1 < map->getMapsize() &&
                        map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y -
                                                             1]->isAccessible()
                        && map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y +
                                                                1]->isAccessible()) {
                        BlockBlocks->setObsSpriteTexture(obs_text, "turn_right_top");
                        map->getTilemap()[mousePosGrid.x +
                                         1][mousePosGrid.y]->setObsSpriteTexture(
                                obs_text,
                                "x_dir");
                        map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y]->setPos(
                                sf::Vector2f(mousePosGrid.x + 1, mousePosGrid.y));
                    } else {
                        BlockBlocks->setObsSpriteTexture(obs_text, "turn_right_top");

                    }
                }

                    // X_direction_right
                else if (mousePosGrid.y + 1 >= 0 &&
                         mousePosGrid.y + 1 < map->getMapsize() &&
                         mousePosGrid.y - 1 >= 0 &&
                         mousePosGrid.y - 1 < map->getMapsize() &&
                         mousePosGrid.x - 1 >= 0 &&
                         mousePosGrid.x - 1 < map->getMapsize() &&
                         mousePosGrid.x + 1 >= 0 &&
                         mousePosGrid.x + 1 < map->getMapsize() &&
                         !map->getTilemap()[mousePosGrid.x -
                                           1][mousePosGrid.y]->isAccessible() &&
                         !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                           1]->isCenter() &&
                         !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                           1]->isCenter() &&
                         !map->getTilemap()[mousePosGrid.x -
                                           1][mousePosGrid.y]->isCenter() &&
                         !map->getTilemap()[mousePosGrid.x +
                                           1][mousePosGrid.y]->isCenter()
                        ) {
                    if (!map->getTilemap()[mousePosGrid.x - 1][mousePosGrid.y +
                                                              1]->isAccessible()
                        || !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y -
                                                                 1]->isAccessible())
                        BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");

                    else {
                        BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                        map->getTilemap()[mousePosGrid.x -
                                         1][mousePosGrid.y]->setObsSpriteTexture(
                                obs_text,
                                "x_dir");
                    }
                }
                    //X_direction_left
                else if (mousePosGrid.y - 1 >= 0 &&
                         mousePosGrid.y - 1 < map->getMapsize() &&
                         mousePosGrid.y + 1 >= 0 &&
                         mousePosGrid.y + 1 < map->getMapsize() &&
                         mousePosGrid.x + 1 >= 0 &&
                         mousePosGrid.x + 1 < map->getMapsize() &&
                         !map->getTilemap()[mousePosGrid.x +
                                           1][mousePosGrid.y]->isAccessible() &&
                         !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                           1]->isCenter() &&
                         !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                           1]->isCenter() &&
                         !map->getTilemap()[mousePosGrid.x +
                                           1][mousePosGrid.y]->isCenter()
                        ) {

                    if ((!map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y -
                                                               1]->isAccessible()
                         || !map->getTilemap()[mousePosGrid.x + 1][mousePosGrid.y +
                                                                  1]->isAccessible())) {
                        BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                    } else {
                        BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                        map->getTilemap()[mousePosGrid.x +
                                         1][mousePosGrid.y]->setObsSpriteTexture(
                                obs_text,
                                "x_dir");

                    }

                } //Straight wall between two obstacles
                else if (mousePosGrid.x - 1 >= 0 &&
                         mousePosGrid.x - 1 < map->getMapsize() &&
                         mousePosGrid.x + 1 >= 0 &&
                         mousePosGrid.x + 1 < map->getMapsize() &&
                         !map->getTilemap()[mousePosGrid.x -
                                           1][mousePosGrid.y]->isAccessible()
                         && !map->getTilemap()[mousePosGrid.x +
                                              1][mousePosGrid.y]->isAccessible()) {
                    BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");

                } else if (mousePosGrid.y == 0 ||
                           mousePosGrid.y == map->getMapsize() - 1) {
                    if (mousePosGrid.y + 1 >= 0 &&
                        mousePosGrid.y + 1 < map->getMapsize() &&
                        !map->getTilemap()[mousePosGrid.x][mousePosGrid.y +
                                                          1]->isAccessible()) {
                        BlockBlocks->setObsSpriteTexture(obs_text);
                    } else {
                        if (mousePosGrid.y - 1 >= 0 &&
                            mousePosGrid.y - 1 < map->getMapsize() &&
                            !map->getTilemap()[mousePosGrid.x][mousePosGrid.y -
                                                              1]->isAccessible())
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

 sf::View Game::getView() {
    return view;
}

const sf::VideoMode &Game::getVideoMode() const {
    return videoMode;
}

void Game::setView(sf::View& view) {
    this->view=view;
    window->setView(view);

}

 sf::RenderWindow& Game::getWindow() {
    return *window;
}

void Game::close() {
    window->close();

}

void Game::clear() {
    window->clear();

}

sf::View Game::getDefaultView() {
    return window->getDefaultView();
}

const sf::Event &Game::getEvent() const {
    return event;
}

void Game::setEvent(const sf::Event &event) {
    Game::event = event;
}

bool Game::pollEvent() {
    if(window->pollEvent(event)){
        return true;}
    return false;
}

Game::Game() {
    map= nullptr;

}

void Game::SetWindow(sf::RenderWindow *new_window) {
    window=new_window;
}



