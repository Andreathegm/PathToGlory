#include <iostream>
#include <sstream>

#include "GameCharacter.h"
#include "Game.h"
int main() {
    //Init game
    float gridSizeF = 100.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
   //create the map
    GameMap map(10);
    std::vector<sf::Vector2f> bestPath;
    GameTile* start;
    GameTile* destination;
    GameTile* BlockBlocks;
    GameTile* misclick[]={nullptr, nullptr};
     int clickcounter[]={0,0,0};
    int currentPathIndex = 0;
    bool isPathComplete = false;
    bool active[]={false , false,false};


   /* bestPath=map.aStar(map.getTilemap()[0][0],map.getTilemap()[10][7]);
     for(auto i : bestPath)
         std::cout<<i.x<<" "<<i.y<<std::endl;*/
    GameCharacter hero("Resources/SpriteSheet.png", 10, 20, 30, sf::Vector2f(10, 10));
   // hero.move_to_position(bestPath);
   //  hero.setPosition(sf::Vector2f(hero.getPosition().x*gridSizeF,hero.getPosition().y*gridSizeF));
    float dt = 0;
    sf::Clock dtClock;
    float delayTime = 0.5f;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;
    sf::Font font;
    font.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/Roboto-Italic.ttf");
    sf::Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10.f, 10.f);
    text.setString("TEST");
    text.setFont(font);
    sf::Texture obs_text;
    obs_text.loadFromFile("C:/Users/HP/CLionProjects/PathToGlory/Resources/Walll.png");



//Init window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PathToGlory");
    window.setFramerateLimit(120);

//init View
    sf::View view;
    view.setSize(1920.f, 1080.f);
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    float viewspeed = 10.f;
    window.setView(view);

//Init game element


    sf::RectangleShape tileselector(sf::Vector2f(gridSizeF, gridSizeF));
    tileselector.setFillColor(sf::Color::Transparent);
    tileselector.setOutlineThickness(1.5);
    tileselector.setOutlineColor(sf::Color::Green);


    while (window.isOpen()) {
        //Update mouse position
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if (mousePosView.x >= 0)
            mousePosGrid.x = mousePosView.x / gridSizeU;
        if (mousePosView.y >= 0)
            mousePosGrid.y = mousePosView.y / gridSizeU;
        tileselector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
            if (ev.type == sf::Event::KeyReleased) {
                if (ev.key.code == sf::Keyboard::X) {
                    if(mousePosGrid.x>=0 && mousePosGrid.x<map.getMapsize() && mousePosGrid.y>=0 && mousePosGrid.y<map.getMapsize())
                    BlockBlocks = map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
                    else
                        break;
                    //Check if tile has already been assigned
                    if(!BlockBlocks->isAccessible()){
                        BlockBlocks->setAccessible(true);
                        BlockBlocks->setVisible(false);}

                    else
                    {
                        BlockBlocks->setPos(sf::Vector2f(mousePosGrid.x,mousePosGrid.y));
                        BlockBlocks->setVisible(true);
                        BlockBlocks->setAccessible(false);

                        //if all 8 tile -> draw a fire sprite
                        if (mousePosGrid.x+1>=0 && mousePosGrid.y-1>=0 &&
                            mousePosGrid.x-1>=0 && mousePosGrid.y+1>=0
                            &&mousePosGrid.x+1<map.getMapsize() && mousePosGrid.y-1<map.getMapsize() &&
                            mousePosGrid.x-1<map.getMapsize() && mousePosGrid.y+1<map.getMapsize() &&

                            !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible()&&
                            !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y-1]->isAccessible()&&
                            !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y-1]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y+1]->isAccessible()&&
                            !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y+1]->isAccessible() &&
                            !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isAccessible()&&
                            !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isAccessible()){
                            BlockBlocks->setObsSpriteTexture(obs_text,"full");
                            BlockBlocks->setCenter(true);

                            //if both orizontal and vertical not accessible , draw a 4connected wall
                        }else if(mousePosGrid.x+1>=0 && mousePosGrid.y-1>=0
                                 &&mousePosGrid.x-1>=0 && mousePosGrid.y+1>=0
                                 &&mousePosGrid.x+1<map.getMapsize() && mousePosGrid.y-1<map.getMapsize() &&
                                 mousePosGrid.x-1<map.getMapsize() && mousePosGrid.y+1<map.getMapsize() &&
                                 !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible()&&
                                 !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isAccessible()&&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isCenter()){

                            BlockBlocks->setObsSpriteTexture(obs_text,"4_dir");
                            map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                            map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");

                        }
                            //Now drawing 3connected wall if 3 tile are not accesible

                            //1) Top
                        else if(mousePosGrid.x+1>=0 && mousePosGrid.x-1>=0 &&mousePosGrid.y+1>=0
                                &&mousePosGrid.x+1<map.getMapsize() && mousePosGrid.x-1<map.getMapsize() &&
                                mousePosGrid.y+1<map.getMapsize() &&
                                !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible()&&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isCenter() &&
                                !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isCenter() &&
                                !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter()

                                ){
                            if(mousePosGrid.y-1>=0 && mousePosGrid.y-1<map.getMapsize() && map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y-1]->isAccessible() &&
                               map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y-1]->isAccessible()){

                                BlockBlocks->setObsSpriteTexture(obs_text,"3_top");
                                map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                                map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");}
                            else{
                                BlockBlocks->setObsSpriteTexture(obs_text,"3_top");
                            }

                            //Down
                        }else if(mousePosGrid.x+1>=0 && mousePosGrid.x-1>=0 &&mousePosGrid.y-1>=0
                                 &&mousePosGrid.x+1<map.getMapsize() && mousePosGrid.x-1<map.getMapsize() &&
                                 mousePosGrid.y-1<map.getMapsize() && !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible()&&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter() &&
                                 !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isCenter()
                                ){
                            if(mousePosGrid.y+1>=0 && mousePosGrid.y+1<map.getMapsize() && map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y+1]->isAccessible() &&
                               map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y+1]->isAccessible()){

                                BlockBlocks->setObsSpriteTexture(obs_text,"3_down");
                                map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                                map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");}
                            else{
                                BlockBlocks->setObsSpriteTexture(obs_text,"3_down");
                            }
                            //Left
                        }else if(mousePosGrid.x-1>=0 && mousePosGrid.y-1>=0 &&mousePosGrid.y+1>=0
                                 &&mousePosGrid.x-1<map.getMapsize() && mousePosGrid.y-1<map.getMapsize() &&
                                 mousePosGrid.y+1<map.getMapsize() && !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isAccessible()&&
                                 !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                                 !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isCenter()
                                ){
                            BlockBlocks->setObsSpriteTexture(obs_text,"3_left");
                            map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");



                        }
                            //Right
                        else if(mousePosGrid.x+1>=0 && mousePosGrid.y-1>=0 &&mousePosGrid.y+1>=0 &&
                                mousePosGrid.x+1<map.getMapsize() && mousePosGrid.y-1<map.getMapsize() &&
                                mousePosGrid.y+1<map.getMapsize() && !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isAccessible()&&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter()
                                ){
                            BlockBlocks->setObsSpriteTexture(obs_text,"3_right");
                            map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");

                        }
                            //drawing 2connected wall

                            //1) Right
                        else if(mousePosGrid.x+1>=0 && mousePosGrid.y-1>=0 &&
                                mousePosGrid.x+1<map.getMapsize() && mousePosGrid.y-1<map.getMapsize() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isAccessible()&&
                                !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isCenter() &&
                                !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter()
                                ){
                            if( mousePosGrid.y+1>=0 && mousePosGrid.y+1<map.getMapsize() && map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y+1]->isAccessible()
                            && map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y-1]->isAccessible() ){
                                BlockBlocks->setObsSpriteTexture(obs_text,"turn_right");
                                map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                                map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setPos(sf::Vector2f(mousePosGrid.x+1,mousePosGrid.y));

                            }
                            else{
                                BlockBlocks->setObsSpriteTexture(obs_text,"turn_right");

                            }
                        }
                            //2) Left_top
                        else if(mousePosGrid.x-1>=0 && mousePosGrid.y+1>=0
                                &&mousePosGrid.x-1<map.getMapsize() && mousePosGrid.y+1<map.getMapsize() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isAccessible()&&
                                !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isCenter() &&
                                !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isCenter()) {
                            if(mousePosGrid.y-1>=0 && mousePosGrid.y-1<map.getMapsize() &&
                            map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y-1]->isAccessible() &&
                            map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y+1]->isAccessible()){
                                BlockBlocks->setObsSpriteTexture(obs_text,"turn_left_top");
                                map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                                map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->setPos(sf::Vector2f(mousePosGrid.x-1,mousePosGrid.y));
                            }
                            else{
                                BlockBlocks->setObsSpriteTexture(obs_text,"turn_left_top");
                            }

                        }
                            // Left_Bottom
                        else{
                            if(mousePosGrid.x-1>=0 && mousePosGrid.y-1>=0
                               &&mousePosGrid.x-1<map.getMapsize() && mousePosGrid.y-1<map.getMapsize() &&
                               !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isAccessible()&&
                               !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                               !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isCenter() &&
                               !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isCenter()
                                    ){
                                if(mousePosGrid.y+1>=0 && mousePosGrid.y+1<map.getMapsize() && map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y+1]->isAccessible() &&
                                    map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y-1]->isAccessible()){
                                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_left");
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setPos(sf::Vector2f(mousePosGrid.x - 1, mousePosGrid.y));
                                }
                                else {
                                    BlockBlocks->setObsSpriteTexture(obs_text, "turn_left");

                                }
                            }

                                // Right_Top
                            else if(mousePosGrid.x+1>=0 && mousePosGrid.y+1>=0
                                    &&mousePosGrid.x+1<map.getMapsize() && mousePosGrid.y+1<map.getMapsize() &&
                                    !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isAccessible()&&
                                    !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible() &&
                                    !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isCenter() &&
                                    !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter())
                            {
                                if(mousePosGrid.y-1>=0 && mousePosGrid.y-1<map.getMapsize() && map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y-1]->isAccessible()
                                && map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y+1]->isAccessible())
                                   {
                                    BlockBlocks->setObsSpriteTexture(obs_text,"turn_right_top");
                                    map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                                    map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setPos(sf::Vector2f(mousePosGrid.x+1,mousePosGrid.y));}
                                else{
                                    BlockBlocks->setObsSpriteTexture(obs_text,"turn_right_top");

                                }
                            }

                                // X_direction_right
                            else if(mousePosGrid.y+1>=0 &&  mousePosGrid.y+1< map.getMapsize() &&
                                    mousePosGrid.y-1>=0 &&  mousePosGrid.y-1< map.getMapsize() &&
                                    mousePosGrid.x-1>=0 &&mousePosGrid.x-1<map.getMapsize() &&
                                    mousePosGrid.x+1>=0 &&mousePosGrid.x+1<map.getMapsize() &&
                                    !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible() &&
                                    !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isCenter() &&
                                    !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isCenter() &&
                                    !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isCenter() &&
                                    !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter()
                                    )
                            {
                                if(!map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y+1]->isAccessible()
                                   || !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y-1]->isAccessible())
                                    BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");

                                else{
                                    BlockBlocks->setObsSpriteTexture(obs_text, "x_dir");
                                    map.getTilemap()[mousePosGrid.x - 1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");
                                }
                            }
                                //X_direction_left
                            else if ( mousePosGrid.y-1>=0 &&  mousePosGrid.y-1< map.getMapsize() &&
                                      mousePosGrid.y+1>=0 &&  mousePosGrid.y+1< map.getMapsize() &&
                                      mousePosGrid.x+1>=0 &&mousePosGrid.x+1<map.getMapsize() &&
                                      !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible()&&
                                      !map.getTilemap()[mousePosGrid.x][mousePosGrid.y-1]->isCenter() &&
                                      !map.getTilemap()[mousePosGrid.x][mousePosGrid.y+1]->isCenter() &&
                                      !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isCenter()
                                    ){

                                if((!map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y-1]->isAccessible()
                                    || !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y+1]->isAccessible())){
                                    BlockBlocks->setObsSpriteTexture(obs_text,"x_dir");
                                }
                                else{
                                    BlockBlocks->setObsSpriteTexture(obs_text,"x_dir");
                                    map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->setObsSpriteTexture(obs_text,"x_dir");

                                }

                            } //Straight wall between two obstacles
                            else if( mousePosGrid.x-1>=0 &&  mousePosGrid.x-1< map.getMapsize() &&
                                     mousePosGrid.x+1>=0 &&  mousePosGrid.x+1< map.getMapsize() &&
                                     !map.getTilemap()[mousePosGrid.x-1][mousePosGrid.y]->isAccessible()
                                     && !map.getTilemap()[mousePosGrid.x+1][mousePosGrid.y]->isAccessible()){
                                BlockBlocks->setObsSpriteTexture(obs_text,"x_dir");

                            }
                            else if(mousePosGrid.y==0 || mousePosGrid.y==map.getMapsize()-1  ) {
                                if (mousePosGrid.y+1>=0 && mousePosGrid.y+1<map.getMapsize() &&
                                !map.getTilemap()[mousePosGrid.x][mousePosGrid.y + 1]->isAccessible()){
                                    BlockBlocks->setObsSpriteTexture(obs_text);
                                }
                                else{
                                    if(mousePosGrid.y-1>=0 && mousePosGrid.y-1<map.getMapsize() &&
                                       !map.getTilemap()[mousePosGrid.x][mousePosGrid.y - 1]->isAccessible())
                                    BlockBlocks->setObsSpriteTexture(obs_text);
                                    else{
                                        BlockBlocks->setObsSpriteTexture(obs_text,"x_dir");
                                    }
                                }
                            }
                            else{
                                BlockBlocks->setObsSpriteTexture(obs_text);}

                        }

                    }
                }

            }
        }


        //start hero path
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            if(clickcounter[0]==1){
                misclick[0]->getTile().setFillColor(sf::Color::White);
                clickcounter[0]=0;
            }
            start = map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
            if(start->isAccessible()) {
                misclick[0] = start;
                start->getTile().setFillColor(sf::Color::Blue);
                mousePosGrid.x *= gridSizeF;
                mousePosGrid.x += gridSizeF / 4;
                mousePosGrid.y *= gridSizeF;
                hero.setPosition(static_cast<sf::Vector2f>(mousePosGrid));
                active[0] = true;
                clickcounter[0]++;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if(clickcounter[1]==1){
                misclick[1]->getTile().setFillColor(sf::Color::White);
                clickcounter[1]=0;
            }
            destination=map.getTilemap()[mousePosGrid.x][mousePosGrid.y];
            misclick[1]=destination;
            destination->getTile().setFillColor(sf::Color::Red);
            active[1]=true;
            clickcounter[1]++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            map.reset();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            map.reset(true);
        if(active[0] && active[1]) {
            bestPath = map.aStar(start, destination);

            if (!isPathComplete) {
                // Ottieni il tempo trascorso fin dall'ultima chiamata di restart()
                float elapsedTime = dtClock.getElapsedTime().asSeconds();

                // Esegui il corpo del ciclo solo se è passato almeno 0.5 secondi
                if (elapsedTime >= delayTime) {
                    if (currentPathIndex < bestPath.size()) {
                        // Effettua qui le operazioni del ciclo che desideri eseguire con l'intervallo desiderato
                        hero.setPosition(sf::Vector2f(bestPath[currentPathIndex].x * gridSizeF,
                                                      bestPath[currentPathIndex].y * gridSizeF));
                        map.getTilemap()[bestPath[currentPathIndex].x][bestPath[currentPathIndex].y]->getTile().setFillColor(sf::Color::Green);
                        // Incrementa l'indice per passare alla prossima posizione nel vettore path
                        currentPathIndex++;

                        // Resetta il timer per il prossimo intervallo
                        dtClock.restart().asSeconds();
                    } else {
                        // Il percorso è terminato, imposta la variabile di completamento a true
                        isPathComplete = true;
                        currentPathIndex=0;
                        active[2]= true;
                    }
                }
            }
        }
    if(active[2]) {
       // map.reset();
        for(bool & i : active)
            i=false;
        isPathComplete= false;
    }
       //update game elements
        //update UI
        std::stringstream ss;
        ss << "Screen " << mousePosScreen.x << " " << mousePosScreen.y << "\n" <<
           "Window " << mousePosWindow.x << " " << mousePosWindow.y << std::endl <<
           "View " << mousePosView.x << " " << mousePosView.y << std::endl <<
           "Grid " << mousePosGrid.x << " " << mousePosGrid.y << std::endl;

        text.setString(ss.str());
        //events


        //Update GC
        hero.move();
        //Update
        //to move the view num_lock on your keyboard need to be active
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
            view.move(-viewspeed , 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
            view.move(0, -viewspeed );
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
            view.move(0, viewspeed );
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
            view.move(viewspeed , 0);
        }



        //render
        window.clear();


        //render game elements
        window.setView(view);



        map.draw(window);

        hero.draw(window);

        window.draw(tileselector);
        //render Ui
        window.setView(window.getDefaultView());

        window.draw(text);

        //done drawing
        window.display();



    }
}





