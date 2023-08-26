//
// Created by HP on 09/08/2023.
//

#ifndef PATHTOGLORY_ANIMATION_H
#define PATHTOGLORY_ANIMATION_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Animation {
public:
    //const and destructor
    Animation(){};
    Animation(sf::Texture* texture,sf::Vector2u imagecount,float switch_time);


    //methods
    void Update(int row,float delta_time);

    //GETTER AND SETTER
    const sf::Vector2u &getImagecount() const;
    void setImagecount(const sf::Vector2u &imagecount);
    const sf::Vector2u &getCurrentimage() const;
    void setCurrentimage(const sf::Vector2u &currentimage);
    float getTotaltime() const;
    void setTotaltime(float totaltime);
    float getSwitchTime() const;
    void setSwitchTime(float switchTime);


public:
    //SpriteSheet_Selector
    sf::FloatRect  uvRect;

private:
    sf::Vector2u imagecount;
    sf::Vector2u currentimage;

    // time for animations
    float totaltime;
    float switch_time;

};


#endif //PATHTOGLORY_ANIMATION_H
