#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

#include "General.h"
#include "Vector2D.h"

const std::string WINDOW_TITLE = "Snake Game";

class Game {
	int frameTime;
	int Quit = 0;

	const int FPS = 15;
	const int frameDelay = 1000 / FPS;

    SDL_Window* window;
    Uint32 frameStart;

public:
	Game() {};
	~Game();

    static std::string filepath;
    static SDL_Renderer* renderer;
	static SDL_Event event;
	static Uint32 time_0;
	static bool isRunning;
	static bool home;


	void initWindow();
	void logSDLError(std::ostream &os, const std::string &msg, bool fatal);
	void waitUntilKeyPressed();

	//setup
	void randTypeMap();
	void setup();
	void setup2();
	void randMap();

	bool running();
	void handleEvents();

	//update
	void update();
	void update2();

	//render
	void render();
	void render2();

	//engine
	void gameLoop();
	void gameLoop2();

	void clean();
};


#endif // GAME_H
