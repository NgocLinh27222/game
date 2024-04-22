#ifndef SCORE_H
#define SCORE_H

#include "Game.h"
#include "GameText.h"
#include "TextureManager.h"

#include <fstream>

class Score : public GameText {
	GameText score_text;
	std::string val_str_score;
	TTF_Font *font = NULL;
	SDL_Rect src, dst;
public:
	Score() {};
	~Score();

	void CreateText();
 	void Setup(const GameText::TextColor &color);
	void Update(const int &score, const std::string &str);
	void Render(const Vector2D &pos, const Vector2D& size);
	void Render2(const Vector2D &pos, const Vector2D& size);

	int getHighestScore();
	int UpdateHighestScore();
    void Record(const int &HighestScore);

	void Free();
};


#endif // SCORE_H
