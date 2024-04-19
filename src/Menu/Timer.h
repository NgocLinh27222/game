#ifndef TIMER_H
#define TIMER_H

#include "Game.h"
#include "GameText.h"
#include "TextureManager.h"
#include <time.h>

using namespace std;

class Timer: public GameText {
	GameText time_text;
	string val_str_time;
	TTF_Font* font = NULL;
	SDL_Rect dst_timer;
	Uint32 time_val;

public:
	Timer() {};
	~Timer();

	void Setup();
    void Render();
	void Update();
	Uint32 getTimeVal();
	void Free();
};


#endif // TIMER_H
