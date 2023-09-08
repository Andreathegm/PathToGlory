//
// Created by HP on 13/08/2023.
//

#include <iostream>
#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) {
    if(!MenuFont.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/arial_light.ttf"))
        std::cout<<"No font found"<<std::endl;

    //Run button
    _mainmenu[0].setFont(MenuFont);
    _mainmenu[0].setFillColor(sf::Color::White);
    _mainmenu[0].setString("Run");
    _mainmenu[0].setCharacterSize(40);
    _mainmenu[0].setPosition(200,500);

    //Command button
    _mainmenu[1].setFont(MenuFont);
    _mainmenu[1].setFillColor(sf::Color::White);
    _mainmenu[1].setString("Commands");
    _mainmenu[1].setCharacterSize(40);
    _mainmenu[1].setPosition(200,550);

    //Exit
    _mainmenu[2].setFont(MenuFont);
    _mainmenu[2].setFillColor(sf::Color::White);
    _mainmenu[2].setString("Exit");
    _mainmenu[2].setCharacterSize(40);
    _mainmenu[2].setPosition(200,600);

    MainmenuSelected=-1;

}

void MainMenu::Draw(sf::RenderWindow &rederTarget) {
    for(const auto & i : _mainmenu)
    rederTarget.draw(i);

}

void MainMenu::moveUp() {
    if(MainmenuSelected-1>=0)
        //when selecting new Text the previous must turn white
        _mainmenu[MainmenuSelected].setFillColor(sf::Color::White);

    MainmenuSelected--;

    if(MainmenuSelected<=-1){
        _mainmenu[0].setFillColor(sf::Color::White);
        MainmenuSelected=MaxMenu-1;
    }

    _mainmenu[MainmenuSelected].setFillColor(sf::Color::Green);

}

void MainMenu::moveDown() {
    if(MainmenuSelected+1<=MaxMenu && MainmenuSelected!=-1)
        _mainmenu[MainmenuSelected].setFillColor(sf::Color::White);

    MainmenuSelected++;

    if(MainmenuSelected==MaxMenu)
        MainmenuSelected=0;

    _mainmenu[MainmenuSelected].setFillColor(sf::Color::Green);



}

int MainMenu::MainMenuSelected() const {
    return MainmenuSelected;
}


void MainMenu::setMainmenuSelected(int mainmenuSelected) {
    MainmenuSelected = mainmenuSelected;
}

const sf::Text *MainMenu::getMainmenu() const {
    return _mainmenu;
}
