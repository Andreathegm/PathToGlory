//
// Created by HP on 21/08/2023.
//
#include<gtest/gtest.h>
#include "../MainMenu.h"
#include"../MainMenu.cpp"

TEST(MainMenuTest,MoveUp){
    auto* menu=new MainMenu(1920,1080);
    ASSERT_EQ(menu->MainMenuSelected(),-1);
    menu->moveUp();
    ASSERT_EQ(menu->MainMenuSelected(),MaxMenu-1);
    ASSERT_EQ(menu->getMainmenu()[menu->MainMenuSelected()].getFillColor(),sf::Color::Green);
    menu->moveUp();
    ASSERT_EQ(menu->MainMenuSelected(),1);
    ASSERT_EQ(menu->getMainmenu()[menu->MainMenuSelected()].getFillColor(),sf::Color::Green);
    ASSERT_EQ(menu->getMainmenu()[menu->MainMenuSelected()+1].getFillColor(),sf::Color::White);
    delete menu;

}
TEST(MainMenuTest,moveDown){
    auto* menu=new MainMenu(1920,1080);
    ASSERT_EQ(menu->MainMenuSelected(),-1);
    menu->moveDown();
    ASSERT_EQ(menu->MainMenuSelected(),0);
    ASSERT_EQ(menu->getMainmenu()[menu->MainMenuSelected()].getFillColor(),sf::Color::Green);
    menu->setMainmenuSelected(2);
    menu->moveDown();
    ASSERT_EQ(menu->MainMenuSelected(),0);
    ASSERT_EQ(menu->getMainmenu()[menu->MainMenuSelected()].getFillColor(),sf::Color::Green);
    ASSERT_EQ(menu->getMainmenu()[MaxMenu-1].getFillColor(),sf::Color::White);
    delete menu;
}
