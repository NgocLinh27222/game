#ifndef SNAKE2_H
#define SNAKE2_H

#include "Snake.h"
#include "Timer.h"
#include "TextureManager.h"

class Snake2 {

public:
	Snake player1;
	Snake player2;
	Timer timer;
	int winner;

public:
	Snake2() {}
	~Snake2();

	void Setup();
	void Render();
	void Update();

	void Logic();
	int isWinner();
	void FreeTexture();
};


#endif // SNAKE2_H
