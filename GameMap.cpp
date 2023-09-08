//
// Created by HP on 30/07/2023.
//

#include "GameMap.h"



GameMap::~GameMap() {
    for(std::vector<GameTile*> &i : tilemap){
        for(auto &k : i ){
            delete k;
        }
    }
    tilemap.clear();

}

int GameMap::getMapsize() const {
    return mapSize;
}

GameMap::GameMap( int mapSize): mapSize(mapSize) {
    tilemap.resize(mapSize);
    for (int x = 0; x < mapSize; x++) {
        tilemap[x].resize(mapSize);
        for (int y = 0; y < mapSize; y++) {
            tilemap[x][y] = new GameTile(static_cast<float>(x), static_cast<float>(y));
        }
        }
    }


void GameMap::draw(sf::RenderWindow &window) const {
    for (int x = 0; x < mapSize; x++) {
        for (int y = 0; y < mapSize; y++) {
            tilemap[x][y]->draw(window);

        }
    }
}

const std::vector<std::vector<GameTile*>> &GameMap::getTilemap() const {
    return tilemap;
}


std::vector<sf::Vector2f> GameMap::aStar( GameTile* start, GameTile* destination) {

    struct CompareTiles {
        bool operator()(const GameTile *lhs, const GameTile *rhs) const {
            // Compare nodes following this--> f(n) = g(n) + h(n)
            return lhs->f_cost() > rhs->f_cost();
        }
    };
    //init Vars

    std::vector<sf::Vector2f> findPath;

    //Used to store GameTile* for eventually retrace the path
    std::priority_queue<GameTile*,std::vector<GameTile*>,CompareTiles> openSet;

    //Used to store Gametile* already explored
    std::unordered_map<int, GameTile*> closedSet;

    start->setG(0);
    start->setH(start->EuclidianDistance(*destination));

    openSet.push(start);
    while (!openSet.empty()) {

        //Take first object on the queue and assign to current and then remove it
        auto current = openSet.top();
        openSet.pop();
        if (current->getPos() == destination->getPos()) {
            auto tmp = current;

            //While cicle that inserts positions on the dedicated vector
            while (tmp != nullptr) {
                findPath.push_back(tmp->getPos());
                if(tmp==start){
                    break;
                }
                tmp=tmp->getParent();
            }
            std::reverse(findPath.begin(), findPath.end());
            break;
        }

        const float dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        const float dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

        for (int i = 0; i < 8; ++i) {
           sf::Vector2f new_pos(current->getPos().x+dx[i],current->getPos().y+dy[i]);

            if (new_pos.x >= 0 && new_pos.x < mapSize && new_pos.y >= 0 && new_pos.y < mapSize && tilemap[new_pos.x][new_pos.y]->isAccessible()) {
                //Check if diagonal direction is allowed, if it is not skip to the next iterations
               if (i % 2 != 0 && !tilemap[current->getPos().x][new_pos.y]->isAccessible() && !tilemap[new_pos.x][current->getPos().y]->isAccessible()) {
                   continue;
                }
                int new_g = current->getG() + (i % 2 == 0 ? 10 : 14); // Movimento orizzontale/verticale: costo 10, diagonale: costo 14
                int new_h = tilemap[new_pos.x][new_pos.y]->EuclidianDistance(*destination)*10;
                int new_f = new_g + new_h;

                // if the key does not match return iterator to the end , if the new_f is less than the previous GameTile*
                // must be put in the ClosedSet
                if (closedSet.find(new_pos.y * mapSize + new_pos.x) == closedSet.end() || new_f < tilemap[new_pos.x][new_pos.y]->f_cost()) {
                    tilemap[new_pos.x][new_pos.y]->setG(new_g);
                    tilemap[new_pos.x][new_pos.y]->setH(new_h);
                    tilemap[new_pos.x][new_pos.y]->setParent(current);
                    openSet.push((tilemap[new_pos.x][new_pos.y]));
                    closedSet[new_pos.y * mapSize + new_pos.x] = tilemap[new_pos.x][new_pos.y];
                }
            }
        }
    }

    return findPath;

}

void GameMap::reset(bool act) {
    std::vector<GameTile*> pavement;
    for(int i=0;i<mapSize;i++)
        for(int j=0;j<mapSize;j++) {
            tilemap[i][j]->setH(0);
            tilemap[i][j]->setG(0);
            tilemap[i][j]->setParent(nullptr);
            if(act){
                if(tilemap[i][j]->isAccessible())
                    pavement.emplace_back(tilemap[i][j]);
                }
            else{
            tilemap[i][j]->setVisible(false);
            tilemap[i][j]->setAccessible(true);
            tilemap[i][j]->setCenter(false);
            tilemap[i][j]->getTile().setFillColor(sf::Color::Transparent);}
        }
    if(!pavement.empty()) {
        for (const auto &k: pavement) {
            k->setVisible(false);
            k->setAccessible(true);
            k->setCenter(false);
            k->getTile().setFillColor(sf::Color::Transparent);

        }
        pavement.clear();
    }


}

