
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

class GameCharacterTest : public ::testing::Test{
public:

protected:
    void SetUp() override {
    map=new GameMap(5);
    Collision::CreateTextureAndBitmask(CharacterTexture,"C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing2_.png");
    Collision::CreateTextureAndBitmask(WallTexture,"C:/Users/HP/CLionProjects/PathToGlory/Resources/NewWall3.png");
    character.Linkmap(map);
    character.setPosition(sf::Vector2f(10,0));
    character.ApplayTextureToSprite(CharacterTexture);
    character.setAnimation(new Animation(&CharacterTexture, sf::Vector2u(11, 4), 0.1));
    }
    void TearDown() override {
    delete map;
    }
GameMap* map;
sf::Texture WallTexture;
sf::Texture CharacterTexture;
GameCharacter character;
};
TEST_F(GameCharacterTest, MoveUp) {
    character.setPosition(sf::Vector2f(0.0f, 0.0f));
    character.move("W");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.0f);
    EXPECT_EQ(newPosition.y, -0.5f);
}

TEST_F(GameCharacterTest, MoveLeft) {
    character.setPosition(sf::Vector2f(0.0f, 0.0f));
    character.move("A");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, -0.5f);
    EXPECT_EQ(newPosition.y, 0.0f);
}
TEST_F(GameCharacterTest, MoveDown) {
    character.setPosition(sf::Vector2f(0.0f, 0.0f));
    character.move("S");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.0f);
    EXPECT_EQ(newPosition.y, 0.5f);
}

TEST_F(GameCharacterTest, MoveRight) {
    character.setPosition(sf::Vector2f(0.0f, 0.0f));
    character.move("D");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.5f);
    EXPECT_EQ(newPosition.y, 0.0f);
}
TEST_F(GameCharacterTest, InvaliDirection) {
    character.setPosition(sf::Vector2f(0.0f, 0.0f));
    character.move("F");

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 0.0f);
    EXPECT_EQ(newPosition.y, 0.0f);
}
TEST_F(GameCharacterTest,Grid_LeftCollision){
    character.setPosition(sf::Vector2f(0.0f, 0.0f));
    character.move("A");
    character.GridCollision();

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x,0.0);
    EXPECT_EQ(newPosition.y,0.0);

}

TEST_F(GameCharacterTest,Grid_TopCollision){
    character.setPosition(sf::Vector2f(5.0f, 0.0f));
    character.move("W");
    character.GridCollision();

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x,5.0);
    EXPECT_EQ(newPosition.y,0.0);
}
TEST_F(GameCharacterTest,Grid_DownCollision) {
    character.setPosition(sf::Vector2f(5.0f,(map->getMapsize()-1)*map->getTilemap()[0][0]->getGridSizeF()));
    character.move("S");
    character.GridCollision();

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x, 5.0);
    EXPECT_EQ(newPosition.y,((map->getMapsize()-1)*(map->getTilemap()[0][0]->getGridSizeF()))-0.5);
}

TEST_F(GameCharacterTest,Wall) {
    character.getGcSprite().scale(sf::Vector2f(0.8, 0.8));

    map->getTilemap()[0][0]->setVisible(false);
    map->getTilemap()[0][0]->setObsSpriteTexture(WallTexture,"x_dir");
    map->getTilemap()[0][0]->setAccessible(false);

    character.collision(character.getGcSprite().getGlobalBounds().width,
                        character.getGcSprite().getGlobalBounds().height/2);

    sf::Vector2f newPosition = character.getPosition();
    EXPECT_EQ(newPosition.x,9.5 );
    EXPECT_EQ(newPosition.y,0);
}
TEST_F(GameCharacterTest, UpdateTest) {
    character.UpdateAnimation(0,0.1);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().x, 1);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().y, 0);

    character.UpdateAnimation(0,0.01);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().x, 1);
    EXPECT_EQ(character.getAnimation()->getCurrentimage().y, 0);
}