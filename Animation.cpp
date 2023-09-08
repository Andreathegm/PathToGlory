//
// Created by HP on 09/08/2023.
//

#include "Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imagecount, float switch_time) {
    this->imagecount=imagecount;
    this->switch_time=switch_time;
    totaltime=0;
    currentimage.x=0;

    uvRect.width=texture->getSize().x/static_cast<float>(imagecount.x);
    uvRect.height=texture->getSize().y/static_cast<float>(imagecount.y);
}

void Animation::Update(int row, float delta_time) {
    currentimage.y=row;
    totaltime=delta_time;
    if(totaltime>=switch_time) {
        totaltime-=delta_time;
        currentimage.x++;

       // restart the cicle_frame
        if(currentimage.x>=imagecount.x)
            currentimage.x=0;
    }
    uvRect.left=currentimage.x* uvRect.width;
    uvRect.top=currentimage.y* uvRect.height;

}

const sf::Vector2u &Animation::getImagecount() const {
    return imagecount;
}

void Animation::setImagecount(const sf::Vector2u &imagecount) {
    Animation::imagecount = imagecount;
}

const sf::Vector2u &Animation::getCurrentimage() const {
    return currentimage;
}

void Animation::setCurrentimage(const sf::Vector2u &currentimage) {
    Animation::currentimage = currentimage;
}

float Animation::getTotaltime() const {
    return totaltime;
}

void Animation::setTotaltime(float totaltime) {
    Animation::totaltime = totaltime;
}

float Animation::getSwitchTime() const {
    return switch_time;
}

void Animation::setSwitchTime(float switchTime) {
    switch_time = switchTime;
}



