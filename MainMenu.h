//
// Created by HP on 13/08/2023.
//

#ifndef PATHTOGLORY_MAINMENU_H
#define PATHTOGLORY_MAINMENU_H
#include <SFML/Graphics.hpp>
#define MaxMenu 3
class MainMenu {
public:
    MainMenu(float width,float height);
    ~MainMenu()=default;

    //methods
    void moveUp();
    void moveDown();
    void Draw(sf::RenderWindow& rederTarget);

    //GETTER AND SETTER
    int MainMenuSelected() const;
    void setMainmenuSelected(int mainmenuSelected);
    const sf::Text *getMainmenu() const;

private:
    int MainmenuSelected;
    sf::Font MenuFont;
    sf::Text _mainmenu[MaxMenu];




};


#endif //PATHTOGLORY_MAINMENU_H
