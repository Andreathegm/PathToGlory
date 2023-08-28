//
// Created by HP on 30/07/2023.
//

#include "GameCharacter.h"
#include "collision.h"


sf::Vector2f &GameCharacter::getPosition()  {
    return position;
}

 sf::Sprite &GameCharacter::getGcSprite()  {
    return gcSprite;
}

const sf::Texture &GameCharacter::getGctexture() const{
    return gctexture;
}

void GameCharacter::setPosition(const sf::Vector2f &position) {
    if(position.x>=0 && position.x<map->getMapsize()*map->getTilemap()[0][0]->getGridSizeF()
    && position.y>=0 && position.y<map->getMapsize()*map->getTilemap()[0][0]->getGridSizeF()){
    GameCharacter::position=position;
    gcSprite.setPosition(position);
    }

}

void GameCharacter::setGcSprite(const sf::Sprite &gcSprite) {
    GameCharacter::gcSprite = gcSprite;
}

void GameCharacter::setGctexture(const sf::Texture &gctexture) {
    GameCharacter::gctexture = gctexture;
}

GameCharacter::GameCharacter(sf::Texture& texture, sf::Vector2f pos,GameMap* map) :
animation( new Animation(&texture, sf::Vector2u(11, 4), 0.1)), position(pos),gctexture(texture),map(map) {

        gcSprite.setTexture(gctexture);
        gcSprite.setTextureRect(sf::IntRect(266, 226, 25, 55));
        gcSprite.scale(sf::Vector2f(1.5,1.5));
        gcSprite.setPosition(pos);





}

void GameCharacter::move(std::string dir) {

    if(dir=="W")
    setPosition(sf::Vector2f(position.x,position.y-0.5));
    else
        if(dir=="A")
            setPosition(sf::Vector2f(position.x-0.5,position.y));
        else
            if(dir=="S")
                setPosition(sf::Vector2f(position.x,position.y+0.5));
            else
                if(dir=="D")
                    setPosition(sf::Vector2f(position.x+0.5,position.y));

}

void GameCharacter::draw(sf::RenderWindow& window) {
    window.draw(gcSprite);

}

void GameCharacter::setTexturerect(sf::IntRect rect) {
    gcSprite.setTextureRect(rect);

}

void GameCharacter::UpdateAnimation(int row, float deltatime) {
    animation->Update(row,deltatime);

}

Animation *GameCharacter::getAnimation() const {
    return animation;
}

void GameCharacter::collision(float offset_x, float offset_y,bool downmovement) {

    sf::Vector2f actual_pos(position);

    auto collision = actual_pos.x + offset_x;
    auto collisiony = actual_pos.y + offset_y;

    auto gridSizeF=map->getTilemap()[0][0]->getGridSizeF();
    auto gridSizeU=static_cast<unsigned>(gridSizeF);
    if (collision > 0 && collision < map->getMapsize() * gridSizeF &&
        collisiony > 0 && collisiony < map->getMapsize() * gridSizeF &&
        !map->getTilemap()[collision / gridSizeU][collisiony / gridSizeU]->isAccessible()) {

        if (Collision::PixelPerfectTest(gcSprite, map->getTilemap()[collision / gridSizeU]
        [collisiony / gridSizeU]->getO_sprite()))


            if(offset_x>0 && offset_y>0 && !downmovement)
            move("A");
            else
                if(offset_x>0 && offset_y>0 )
                    move("W");
                else
                    if(offset_x>0)
                        move("S");
                    else
                        move("D");

    }
}

void GameCharacter::GridCollision() {
    auto gridSizeU=static_cast<unsigned >(map->getTilemap()[0][0]->getGridSizeF());

    //Check right_grid collision
    if (position.x <map->getTilemap()[0][position.y / gridSizeU]->getPos().x)
        setPosition(sf::Vector2f(0, position.y));

    // Check top_grid collision
    if (position.y <
        map->getTilemap()[position.x / gridSizeU][0]->getPos().y)
        setPosition(sf::Vector2f(position.x, 0));

    // Check down_grid collision
    if (static_cast<unsigned>(position.y) / gridSizeU == map->getMapsize() - 1 &&
        position.y + gcSprite.getGlobalBounds().height >
        map->getTilemap()[map->getMapsize() - 1][position.y / gridSizeU]->getPos().y +
        map->getTilemap()[map->getMapsize() - 1][position.y /
                                               gridSizeU]->getTile().getGlobalBounds().height)
        setPosition(sf::Vector2f(position.x,position.y - 1));

}

GameCharacter::GameCharacter() {


}

GameCharacter::GameCharacter(GameMap *map) {
    this->map=map;

}

void GameCharacter::Linkmap(GameMap *map) {
    this->map=map;

}

void GameCharacter::ApplayTextureToSprite(sf::Texture &texture) {
    gctexture=texture;
    gcSprite.setTexture(gctexture);
    gcSprite.setTextureRect(sf::IntRect(266, 226, 25, 55));
    gcSprite.scale(sf::Vector2f(1.5,1.5));


}

void GameCharacter::setAnimation(Animation *animation) {
    GameCharacter::animation = animation;
}






