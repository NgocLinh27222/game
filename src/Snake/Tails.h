#ifndef TAILS_H
#define TAILS_H

#include "Game.h"
#include <vector>

class Tails {
	SDL_Texture* tailTexture;
	SDL_Texture* lastTailTexture;
	SDL_Texture* curveTexture;
	SDL_Texture* curveTailTexture;

	SDL_Rect t_srcCurve;
	SDL_Rect srcR, dstR;

	Vector2D curve;

public:
	Tails(){}
	~Tails();

    short int size = TAILS_SIZE;

	std::vector<Vector2D> tail;

	short int total_tail;
    std::vector<int> t_angle;

	void Setup(const std::string& body, const std::string& tail_, const std::string& curve_, const std::string& curve_tail, short int totalTail = 3);
	void Update();
	void Render();
	//short int getTotalTail();

	void FreeTexture();
};


#endif // TAILS_H
