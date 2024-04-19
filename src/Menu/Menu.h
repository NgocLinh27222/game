#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include "GameText.h"
#include "Score.h"
#include "Audio.h"

class Menu: public GameText {
	SDL_Rect pos_menu[MENU_ITEM];
	SDL_Rect src_menu[MENU_ITEM];
	bool selected[MENU_ITEM] = {0, 0, 0, 0};

	SDL_Texture* menu;
	SDL_Texture* play;
	SDL_Texture* exit;
	SDL_Texture* infor;
	SDL_Texture* music;
	//MENU: 0: play game, 1: exit, 2: info, 3: music;


	SDL_Rect pos_opt[NUM_PLAYER];
	SDL_Rect src_opt[NUM_PLAYER];
	bool selected_opt[NUM_PLAYER] ={0, 0};
	SDL_Texture* mode[NUM_PLAYER];
	SDL_Texture* option;
	//OPTION: 0: exit, 1: player1, 2: player2;

	SDL_Rect pos_end[MENU_ITEM];
	SDL_Rect src_end[MENU_ITEM];
	bool selected_end[MENU_ITEM] = {0, 0, 0, 0};
	SDL_Texture* end;
	SDL_Texture* exitButton;
	SDL_Texture* playAgain;
	SDL_Texture* backButton;
	//END: 0: play again, 1: exit, 2: back

	Audio theme_music;

	TTF_Font* font = NULL;
	TTF_Font* font2 = NULL;

	Score game_score;
	int xm = 0, ym = 0;
	SDL_Event m_event;

public:
	Menu() {}
	~Menu();

	void Setup();
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
	int showMenu();
	int getNumPlayer();
	int endMenu(const char* path);
	int endMenu(const char* path, const int& score);
	int eventEndMenu();

	void FreeTexture();
};


#endif // MENU_H
