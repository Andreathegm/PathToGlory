//
// Created by HP on 21/08/2023.
//
#include <gtest/gtest.h>
#include "../Animation.h"
#include "../collision.h"
class AnimationTest : public ::testing::Test{
protected:
    void SetUp() override {
        Collision::CreateTextureAndBitmask(animation_texture,"C:/Users/HP/CLionProjects/PathToGlory/Resources/prisonerEditing2_.png");
        width_per_frame=animation_texture.getSize().x/ImageCount.x;
        width_per_frame=animation_texture.getSize().x/ImageCount.x;
        animation.setImagecount(ImageCount);
        animation.setTotaltime(0);
        animation.setSwitchTime(0.1);
        animation.uvRect.width=animation_texture.getSize().x/static_cast<float>(ImageCount.x);
        animation.uvRect.height=animation_texture.getSize().y/static_cast<float>(ImageCount.y);

    }
    void TearDown() override {
    }
    sf::Vector2u ImageCount{11,4};
    sf::Texture animation_texture;
    unsigned width_per_frame;
    unsigned height_per_frame;
    Animation animation;
};

TEST_F(AnimationTest,switchImage){
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
TEST_F(AnimationTest,Not_switching){
    animation.Update(2,0.09);
    ASSERT_EQ(animation.getCurrentimage().y,2);
    ASSERT_EQ(animation.getCurrentimage().x,0);
}

