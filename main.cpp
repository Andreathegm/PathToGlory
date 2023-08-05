#include <iostream>
#include <sstream>

#include "GameCharacter.h"
#include "Game.h"
int main() {
    //Init game
    float gridSizeF = 100.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
   //create the map
    GameMap map(100);

    std::vector<sf::Vector2f> bestPath;
    GameTile* start;
    GameTile* destination;
    GameTile* misclick[]={nullptr, nullptr};
     int clickcounter[]={0,0};
    int currentPathIndex = 0;
    bool isPathComplete = false;
    bool active[]={false , false,false};


   /* bestPath=map.aStar(map.getTilemap()[0][0],map.getTilemap()[10][7]);
     for(auto i : bestPath)
         std::cout<<i.x<<" "<<i.y<<std::endl;*/
    GameCharacter hero("Resources/SpriteSheet.png", 10, 20, 30, sf::Vector2f(10, 10));
   // hero.move_to_position(bestPath);
   //  hero.setPosition(sf::Vector2f(hero.getPosition().x*gridSizeF,hero.getPosition().y*gridSizeF));
    float dt = 0;
    sf::Clock dtClock;
    float delayTime = 0.5f;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;
    sf::Font font;
    font.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/Roboto-Italic.ttf");
    sf::Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10.f, 10.f);
    text.setString("TEST");
    text.setFont(font);


//Init window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PathToGlory");
    window.setFramerateLimit(120);

//init View
    sf::View view;
    view.setSize(1920.f, 1080.f);
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    float viewspeed = 10.f;
    window.setView(view);

//Init game element


    sf::RectangleShape tileselector(sf::Vector2f(gridSizeF, gridSizeF));
    tileselector.setFillColor(sf::Color::Transparent);
    tileselector.setOutlineThickness(1.5);
    tileselector.setOutlineColor(sf::Color::Green);


    while (window.isOpen()) {
        //Update mouse position
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if (mousePosView.x >= 0)
            mousePosGrid.x = mousePosView.x / gridSizeU;
        if (mousePosView.y >= 0)
            mousePosGrid.y = mousePosView.y / gridSizeU;
        tileselector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        //start hero path
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            if(clickcounter[0]==1){
                misclick[0]->getTile().setFillColor(sf::Color::White);
                clickcounter[0]=0;
            }
            start=map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
            misclick[0]=start;
            start->getTile().setFillColor(sf::Color::Blue);
            mousePosGrid.x *= gridSizeF;
            mousePosGrid.x += gridSizeF / 4;
            mousePosGrid.y *= gridSizeF;
            hero.setPosition(static_cast<sf::Vector2f>(mousePosGrid));
            active[0]= true;
            clickcounter[0]++;

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
                        map.getTilemap()[bestPath[currentPathIndex].x][bestPath[currentPathIndex].y]->getTile().setFillColor(
                                sf::Color::Green);
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
        map.reset();
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
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();

        }
        //Update GC
        hero.move();
        //Update
        //to move the view num_lock on your keyboard need to be active
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
            view.move(-viewspeed , 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
            view.move(0, -viewspeed );
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
            view.move(0, viewspeed );
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
            view.move(viewspeed , 0);
        }



        //render
        window.clear();


        //render game elements
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





