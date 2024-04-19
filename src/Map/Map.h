#ifndef MAP_H
#define MAP_H

#include "Game.h"
#include "TextureManager.h"

class Map {
    SDL_Texture* block;

public:

    static int map_[MAP_ROW][MAP_COL];

	Map() {}
	~Map();

	void Setup(std::string filepath);
	void FreeBorderTexture();

	int getValueOfMap (int row, int col){ return map_[row][col];}
};


#endif // MAP_H
