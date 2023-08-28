//
// Created by HP on 21/08/2023.
//
#include <gtest/gtest.h>
#include "../Game.cpp"
#include <gmock/gmock.h>

//global variable for some Test_cases
    auto map = new GameMap(5);
    Game game;
    GameTile *tile;
    bool walking = false;
    sf::Vector2u grid_pos;
    sf::Vector2f mouse_pos_view;
    sf::Texture wall_texture;
    float zoomfactor = 1.0f;
    sf::View view;

class IRenderWindow : public sf::RenderWindow{
public:
   virtual bool pollEvent(sf::Event& event){
        if(window.pollEvent(event))
            return true;
        else
            return false;
    }

public:
    sf::RenderWindow window;
};



class MockRenderWindow : public IRenderWindow {
public:
    MOCK_METHOD(bool, pollEvent, (sf::Event & ),(override));
};


class GameTest : public ::testing::Test {
public:
    void handleEvent(sf::Event& event){

    game->setEvent(event);
    ON_CALL(*mockRenderWindow, pollEvent(::testing::_))
    .WillByDefault(::testing::DoAll(::testing::SetArgReferee<0>(event), ::testing::Return(true)));
    game->pollEvents(grid_pos, mockBlockblocks, obsTexture, walking, zoomfactor,view);

    }

protected:
    void SetUp() override {
        mockRenderWindow = new MockRenderWindow();
        game = new Game;
        zoomfactor=1.0f;
        mockBlockblocks= nullptr;
        walking=false;
        game->SetWindow(mockRenderWindow);
        game->Linkmap(map);

    }

    void TearDown() override {
        delete game;
        delete mockRenderWindow;

    }

    Game* game;
    MockRenderWindow* mockRenderWindow;
    GameMap* map = new GameMap(5);
    GameTile *mockBlockblocks;
    bool walking;
    sf::Vector2u grid_pos;
    sf::Vector2f mouse_pos_view;
    sf::Texture wall_texture;
    float zoomfactor;
    sf::View view;
    sf::Texture obsTexture;
};

TEST_F(GameTest, PollEvents_closeWindow) {
    sf::Event closeEvent;
    closeEvent.type = sf::Event::Closed;
    handleEvent(closeEvent);
    ASSERT_EQ(game->IsRunning(), false);
}
TEST_F(GameTest, PollEvents_MoveKeyReleased) {
    sf::Event ReleseEvent_W;
    ReleseEvent_W.type = sf::Event::KeyReleased;
    ReleseEvent_W.key.code = sf::Keyboard::W;

    sf::Event ReleseEvent_A;
    ReleseEvent_A.type = sf::Event::KeyReleased;
    ReleseEvent_A.key.code = sf::Keyboard::A;

    sf::Event ReleseEvent_S;
    ReleseEvent_S.type = sf::Event::KeyReleased;
    ReleseEvent_S.key.code = sf::Keyboard::S;

    sf::Event ReleseEvent_D;
    ReleseEvent_D.type = sf::Event::KeyReleased;
    ReleseEvent_D.key.code = sf::Keyboard::D;

    const char key[4]={'W','A','S','D'};
    std::map<const char, sf::Event> Events;
    const sf::Event Event_name[4]={ReleseEvent_W,ReleseEvent_A,ReleseEvent_S,ReleseEvent_D};
    for( int i=0;i<4;i++) {
        Events.insert(std::make_pair(key[i], Event_name[i]));
        handleEvent(Events[key[i]]);
        ASSERT_FALSE(walking);
    }
    Events.clear();

}
TEST_F(GameTest, ZoomIn) {
    sf::Event ZoomIn;
    ZoomIn.type = sf::Event::KeyReleased;
    ZoomIn.key.code=sf::Keyboard::B;
    handleEvent(ZoomIn);
    ASSERT_FLOAT_EQ(zoomfactor,0.8);//0.8 is the maxZoom
    zoomfactor=0.3f;
    handleEvent(ZoomIn);
    ASSERT_FLOAT_EQ(zoomfactor,0.294);
}
TEST_F(GameTest, ZoomOut) {
    sf::Event ZoomOut;
    ZoomOut.type = sf::Event::KeyReleased;
    ZoomOut.key.code=sf::Keyboard::N;
    handleEvent(ZoomOut);
    ASSERT_FLOAT_EQ(zoomfactor,1.11);//1.11 is the minZoom
    handleEvent(ZoomOut);
    ASSERT_FLOAT_EQ(zoomfactor,1.1766);

}

sf::IntRect rect;

void RunWallPlacementTest( sf::Vector2u& grid_pos,  sf::Texture& wall_texture,sf::IntRect& rect,bool center=false) {
    wall_texture.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/NewWall3.png");
    game.Linkmap(map);
    tile=map->getTilemap()[grid_pos.x][grid_pos.y];
    game.handleWallPlacement(grid_pos, tile, wall_texture);

    ASSERT_EQ(tile->isAccessible(), false);
    ASSERT_EQ(tile->isVisible(), true);
    if(center)
        ASSERT_EQ(tile->isCenter(),true);

    ASSERT_EQ(tile->getObsSprite().getTextureRect().left, rect.left);
    ASSERT_EQ(tile->getObsSprite().getTextureRect().top, rect.top);
    ASSERT_EQ(tile->getObsSprite().getTextureRect().width, rect.width);
    ASSERT_EQ(tile->getObsSprite().getTextureRect().height, rect.height);
    map->reset();
}

TEST(WallTesting,Stright){
    grid_pos={2,1};
    rect={0,0,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,TurnRight){

    map->getTilemap()[2][1]->setAccessible(false);
    map->getTilemap()[3][2]->setAccessible(false);

    grid_pos={2,2};
    rect={16,0,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,TurnLeft){

    map->getTilemap()[2][1]->setAccessible(false);
    map->getTilemap()[1][2]->setAccessible(false);

    grid_pos={2,2};
    rect={48,0,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,Turn_top_Right){

    map->getTilemap()[3][2]->setAccessible(false);
    map->getTilemap()[2][3]->setAccessible(false);

    grid_pos={2,2};
    rect={64,0,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,Turn_top_Left){

    map->getTilemap()[2][3]->setAccessible(false);
    map->getTilemap()[1][2]->setAccessible(false);

    grid_pos={2,2};
    rect={80,0,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,3_Right){

    map->getTilemap()[2][3]->setAccessible(false);
    map->getTilemap()[3][2]->setAccessible(false);
    map->getTilemap()[2][1]->setAccessible(false);


    grid_pos={2,2};
    rect={0,16,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,3_Left){

    map->getTilemap()[2][3]->setAccessible(false);
    map->getTilemap()[1][2]->setAccessible(false);
    map->getTilemap()[2][1]->setAccessible(false);


    grid_pos={2,2};
    rect={48,16,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,3_Top){

    map->getTilemap()[3][2]->setAccessible(false);
    map->getTilemap()[2][1]->setAccessible(false);
    map->getTilemap()[1][2]->setAccessible(false);


    grid_pos={2,2};
    rect={32,16,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,3_Down){

    map->getTilemap()[3][2]->setAccessible(false);
    map->getTilemap()[2][3]->setAccessible(false);
    map->getTilemap()[1][2]->setAccessible(false);


    grid_pos={2,2};
    rect={16,16,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,4_dir){

    map->getTilemap()[1][2]->setAccessible(false);
    map->getTilemap()[2][1]->setAccessible(false);
    map->getTilemap()[2][3]->setAccessible(false);
    map->getTilemap()[3][2]->setAccessible(false);


    grid_pos={2,2};
    rect={96,0,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(WallTesting,full){

    const int dirx[8]={1, 1, 0, -1, -1, -1, 0, 1};
    const int diry[8]={0, 1, 1, 1, 0, -1, -1, -1};
    for(int i=0 ; i<8;i++){
        map->getTilemap()[2+dirx[i]][2+diry[i]]->setAccessible(false);
    }


    grid_pos={2,2};
    map->getTilemap()[grid_pos.x][grid_pos.y]->setCenter(true);
    rect={64,16,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect, true);
}
TEST(WallTesting,x_dir){

    map->getTilemap()[1][2]->setAccessible(false);
    map->getTilemap()[3][2]->setAccessible(false);

    grid_pos={2,2};
    rect={32,0,16,16};
    RunWallPlacementTest(grid_pos,wall_texture,rect);
}
TEST(TileSelecBoundTest,All){
    mouse_pos_view={0,499};
    ASSERT_EQ(game.TileSelectorBoundaries(mouse_pos_view),true);
    mouse_pos_view={0,600};
    ASSERT_EQ(game.TileSelectorBoundaries(mouse_pos_view),false);
}

TEST_F(GameTest,WallkeyReleased){
    sf::Event Wallkey;
    Wallkey.type=sf::Event::KeyReleased;
    Wallkey.key.code=sf::Keyboard::X;
    grid_pos={2,2};
    map->getTilemap()[1][2]->setAccessible(false);
    map->getTilemap()[2][1]->setAccessible(false);
    map->getTilemap()[3][2]->setAccessible(false);
    mockBlockblocks=map->getTilemap()[grid_pos.x][grid_pos.y];
    handleEvent(Wallkey);
    rect={32,16,16,16};
    bool center=false;
    ASSERT_EQ(mockBlockblocks->isAccessible(), false);
    ASSERT_EQ(mockBlockblocks->isVisible(), true);
    if(center)
        ASSERT_EQ(mockBlockblocks->isCenter(),true);

    ASSERT_EQ(mockBlockblocks->getObsSprite().getTextureRect().left, rect.left);
    ASSERT_EQ(mockBlockblocks->getObsSprite().getTextureRect().top, rect.top);
    ASSERT_EQ(mockBlockblocks->getObsSprite().getTextureRect().width, rect.width);
    ASSERT_EQ(mockBlockblocks->getObsSprite().getTextureRect().height, rect.height);
    map->reset();

}