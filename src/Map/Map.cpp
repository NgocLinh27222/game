#include "Map.h"

#include <fstream>

int Map::map_[MAP_ROW][MAP_COL] = {0};

Map::~Map() {
	FreeBorderTexture();
}

void Map::Setup(std::string filepath){
    block = TextureManager::LoadTexture("res/map/block.png");

    //std::string filepath = "res/map/map2.txt";
    std::ifstream file(filepath);
    int tmp;

    for(int i=0; i<MAP_ROW; i++) {

        for(int j=0; j<MAP_COL; j++) {
            file >> tmp;
            map_[i][j] = tmp;
            if(tmp == 1){
                TextureManager::Draw(block, {j*BLOCK_SIZE, i*BLOCK_SIZE}, {BLOCK_SIZE, BLOCK_SIZE});
            }
        }
    }
    file.close();
}

void Map::FreeBorderTexture() {
	SDL_DestroyTexture(block);
}
