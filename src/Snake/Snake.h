#ifndef SNAKE_H
#define SNAKE_H

#include "Game.h"
#include "Audio.h"
#include "Tails.h"
#include "Score.h"
#include "Map.h"


class Snake {
public:
	Snake() {}
	~Snake();

	void Setup(const std::string &filePath);
	void Setup2(const std::string &head_color, const std::string &body_color, const std::string &tail_color,
                const std::string &curve_color, const std::string &curveTail_color,
                const Vector2D &startPos, const int &index, const GameText::TextColor &color);

	// Movement
	void Move();
	void Up();
	void Down();
	void Left();
	void Right();

	// Alive
	bool CheckSelfCollide();
    bool CheckCollideBlock();
    bool isAlive() {return alive;}

	//1 player
	void Update();
	void Direction();
	void CheckCollideFood();

    // check fruit
	bool fruitInsideSnake();
    bool fruitInsideSnake(const Snake &other);
    bool fruitInsideBlock();

	//2 player
	void moveSet();
	void Update2(const Snake &other);
	void Direction2();
	void moveSet2();
	void CheckCollideFood2(const Snake &other);

	//render
	void Render();
	void RenderHighestScore(const Vector2D &pos, const Vector2D &size);
	void RenderScore(const Vector2D &pos, const Vector2D &size);

    //score
	int getScore();
	void UpdateScore(std::string msg);
	void UpdateHighestScore();

	//Tails getTails() const;

	void FreeTexture();

private:
    int size = SNAKE_SIZE;
	Vector2D head;
    Tails tails;

	int velocity = SNAKE_SIZE;
	Vector2D step;

	SDL_Texture* snakeTexture;
	SDL_Rect srcR, dstR;

	Audio eating_sound;
	Audio lose_sound;

	int score;
    int HighestScore;
	Score game_score;
	Score game_highestScore;

    int s_angle = 0;
    bool alive = true;
	bool isMove = false;
	SDL_RendererFlip s_flip = SDL_FLIP_NONE;

	bool resume = false;

	enum eDirection {UP, DOWN, LEFT, RIGHT};
	eDirection dir;
};


#endif // SNAKE_H
