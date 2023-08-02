#include <iostream>
#include <sstream>


#include "Game.h"
int main() {/*

    Game game;
    while (game.IsRunning()) {
        game.update();
        game.render();
    }*/
//Init game
float gridSizeF=100.f;
unsigned gridSizeU=static_cast<unsigned>(gridSizeF);
GameMap map(100);
float dt=0;
sf::Clock dtClock;
sf::Vector2i mousePosScreen;
sf::Vector2i mousePosWindow;
sf::Vector2f mousePosView;
sf::Vector2u mousePosGrid;
sf::Font font;
font.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/Roboto-Italic.ttf");
sf::Text text;
text.setCharacterSize(24);
text.setFillColor(sf::Color::Blue);
text.setPosition(10.f,10.f);
text.setString("TEST");
text.setFont(font);


//Init window
sf::RenderWindow window(sf::VideoMode(1920,1080),"PathToGlory");
window.setFramerateLimit(120);

//init View
sf::View view;
view.setSize(1920.f,1080.f);
view.setCenter(window.getSize().x/2,window.getSize().y/2);
float viewspeed=1000.f;
window.setView(view);

//Init game element


sf::RectangleShape tileselector(sf::Vector2f(gridSizeF,gridSizeF));
tileselector.setFillColor(sf::Color::Transparent);
tileselector.setOutlineThickness(1.5);
tileselector.setOutlineColor(sf::Color::Green);
/*
const int mapsize=10;
std::vector<std::vector<sf::RectangleShape>> tilemap;
tilemap.resize(mapsize,std::vector<sf::RectangleShape>());
for(int x =0;x<mapsize;x++){
    tilemap[x].resize(mapsize,sf::RectangleShape());
    for(int y =0;y<mapsize;y++){
        tilemap[x][y].setSize(sf::Vector2f(gridSizeF,gridSizeF));
        tilemap[x][y].setFillColor(sf::Color::White);
        tilemap[x][y].setOutlineColor(sf::Color::Black);
        tilemap[x][y].setOutlineThickness(1.f);
        tilemap[x][y].setPosition(x*gridSizeF,y*gridSizeF);
    }
}
*/


while(window.isOpen())
{
    //update dt
    dt=dtClock.restart().asSeconds();

    //Update mouse position
    mousePosScreen=sf::Mouse::getPosition();
    mousePosWindow=sf::Mouse::getPosition(window);
    window.setView(view);
    mousePosView=window.mapPixelToCoords(mousePosWindow);
    if(mousePosView.x>=0)
    mousePosGrid.x=mousePosView.x/gridSizeU;
     if(mousePosView.y>=0)
        mousePosGrid.y=mousePosView.y/gridSizeU;
     //update game elements
     tileselector.setPosition(mousePosGrid.x* gridSizeF,mousePosGrid.y* gridSizeF);

     //update UI
     std::stringstream ss ;
     ss <<"Screen "<< mousePosScreen.x<<" "<<mousePosScreen.y <<"\n" <<
    "Window "<< mousePosWindow.x<<" "<<mousePosWindow.y<<std::endl<<
    "View "<< mousePosView.x<<" "<<mousePosView.y<<std::endl<<
    "Grid "<< mousePosGrid.x<<" "<<mousePosGrid.y<<std::endl;

    text.setString(ss.str());
    //events
    sf::Event ev;
    while(window.pollEvent(ev))
    {
        if(ev.type==sf::Event::Closed)
            window.close();

    }
    //Update
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        view.move(-viewspeed* dt,0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        view.move(0,-viewspeed* dt);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        view.move(0,viewspeed* dt);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        view.move(viewspeed* dt,0);
    }

    //render
    window.clear();


    //render game elements
    window.setView(view);


    /*for(int x =0;x<mapsize;x++){
        for(int y =0;y<mapsize;y++){
         window.draw(tilemap[x][y]);
        }
    }*/
    map.draw(window);
   /* for(int x =0;x<game.getMap()->getMapsize();x++){
        for(int y =0;y<game.getMap()->getMapsize();y++){
            window.draw(game.getMap()->gettilemap()[x][y]->getTile());}}*/

    window.draw(tileselector);
    //render Ui
    window.setView(window.getDefaultView());
    window.draw(text);

    //done drawing
    window.display();


}
}






