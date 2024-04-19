#ifndef FRUIT_H
#define FRUIT_H

#include "Game.h"

class Fruit{
	SDL_Rect srcR, dstR;
	SDL_Texture *fruitTexture;
public:
	Fruit() {}
	~Fruit();

    static Vector2D fruit_pos;
    static Vector2D fruit_src;
    static int fruit_score;
	static int size;

	void Setup(const char *filePath);
	void Render();
	void Update();

    static void randTypeFruit();
	static void Respawn();

	void FreeTexture();
};


#endif // FRUIT_H
