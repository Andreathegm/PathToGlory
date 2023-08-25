//
// Created by HP on 21/08/2023.
//
#include <gtest/gtest.h>
#include "../Animation.h"


TEST(AnimationTest,switchImage){

    sf::Vector2u ImageCount(11,4);
    sf::Texture animation_texture;
    animation_texture.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing2_.png");
    sf::Vector2u size= animation_texture.getSize();
    auto width_per_frame=size.x/ImageCount.x;
    auto height_per_frame=size.y/ImageCount.y;
    Animation animation(&animation_texture,ImageCount,0.1);
    animation.Update(0,0.3);
    ASSERT_EQ(animation.getCurrentimage().y,0);
    ASSERT_EQ(animation.getCurrentimage().x,1);
    ASSERT_EQ(animation.uvRect.top,0*height_per_frame);
    ASSERT_EQ(animation.uvRect.left,1*width_per_frame);

    //Check if after last image restart from the beginning
    animation.setCurrentimage(sf::Vector2u (12,0));
    animation.Update(0,0.2);
    ASSERT_EQ(animation.getCurrentimage().x,0);
    ASSERT_EQ(animation.uvRect.top,0);
    ASSERT_EQ(animation.uvRect.left,0);
}
TEST(AnimationTest,Not_switching){
    sf::Vector2u ImageCount(11,4);
    sf::Texture animation_texture;
    animation_texture.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing2_.png");
    Animation animation(&animation_texture,ImageCount,0.1);
    animation.Update(2,0.09);
    ASSERT_EQ(animation.getCurrentimage().y,2);
    ASSERT_EQ(animation.getCurrentimage().x,0);
}

