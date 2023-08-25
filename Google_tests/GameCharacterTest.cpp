
// Created by HP on 17/08/2023.
//

#include "../GameCharacter.h"
#include "../GameCharacter.cpp"
#include "../GameTile.h"
#include "../GameTile.cpp"
#include "../GameMap.h"
#include "../GameMap.cpp"
#include "../collision.h"
#include "../collision.cpp"
#include "../Animation.h"
#include "../Animation.cpp"
#include "gtest/gtest.h"



TEST(GameCharacterTest, MoveUp) {
    GameCharacter character;
    character.setPosition(sf::Vector2f(0.0f, 0.0f));

    character.move("W");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.0f);
    EXPECT_EQ(newPosition.y, -0.5f);
}
TEST(GameCharacterTest, MoveLeft) {
    GameCharacter character;
    character.setPosition(sf::Vector2f(0.0f, 0.0f));

    character.move("A");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, -0.5f);
    EXPECT_EQ(newPosition.y, 0.0f);
}
TEST(GameCharacterTest, MoveDown) {
    GameCharacter character;
    character.setPosition(sf::Vector2f(0.0f, 0.0f));

    character.move("S");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.0f);
    EXPECT_EQ(newPosition.y, 0.5f);
}

TEST(GameCharacterTest, MoveRight) {
    GameCharacter character;
    character.setPosition(sf::Vector2f(0.0f, 0.0f));

    character.move("D");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.5f);
    EXPECT_EQ(newPosition.y, 0.0f);
}
TEST(GameCharacterTest, InvaliDirection) {
    GameCharacter character;
    character.setPosition(sf::Vector2f(0.0f, 0.0f));

    character.move("F");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.0f);
    EXPECT_EQ(newPosition.y, 0.0f);
}
TEST(GridCollisonTest,LeftCollison){
    auto map=new GameMap(5);
    GameCharacter character(map);
    character.setPosition(sf::Vector2f(0.0f, 0.0f));
    character.move("A");
    character.GridCollision();

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x,0.0);
    EXPECT_EQ(newPosition.y,0.0);
    delete map;
}
TEST(GridCollisonTest,TopCollision){
    auto map=new GameMap(5);
    GameCharacter character(map);
    character.setPosition(sf::Vector2f(5.0f, 0.0f));
    character.move("W");
    character.GridCollision();

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x,5.0);
    EXPECT_EQ(newPosition.y,0.0);
    delete map;
}
TEST(GridCollisonTest,DownCollision) {
    auto map = new GameMap(5);
    GameCharacter character(map);
    character.setPosition(sf::Vector2f(5.0f,(map->getMapsize()-1)*map->getTilemap()[0][0]->getGridSizeF()));
    character.move("S");
    character.GridCollision();

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 5.0);
    EXPECT_EQ(newPosition.y,((map->getMapsize()-1)*(map->getTilemap()[0][0]->getGridSizeF()))-0.5);
    delete map;
}

//TODO Wallcollision
/*TEST(WallCollisonTest,RightWall) {
    sf::Texture texture;
    texture.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing2_.png");
    sf::Texture wallTexture;
    wallTexture.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/NewWall3.png");
    auto map = new GameMap(5);
    GameCharacter character(texture,sf::Vector2f(63.5,0),map);
    character.move("D");
    map->getTilemap()[1][0]->setPos(sf::Vector2f(1,0));
    map->getTilemap()[1][0]->setObsSpriteTexture(wallTexture);
    map->getTilemap()[1][0]->setAccessible(false);

    character.collision(character.getGcSprite().getGlobalBounds().width,
                        character.getGcSprite().getGlobalBounds().height/2);

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x,150 );
    EXPECT_EQ(newPosition.y,0);
    delete map;
}*/
TEST(CharacterAnimation, UpdateTest) {
    GameMap* map=new GameMap(5);
    sf::Texture texture;
    texture.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing2_.png");
    GameCharacter character(texture,sf::Vector2f(10,10),map);


    character.UpdateAnimation(0,0.1);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().x, 1);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().y, 0);

    character.UpdateAnimation(0,0.01);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().x, 1);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().y, 0);
    delete map;
}