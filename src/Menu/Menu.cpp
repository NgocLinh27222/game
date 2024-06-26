#include "Menu.h"
#include "TextureManager.h"

Menu::~Menu() {
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(infor);
	SDL_DestroyTexture(play);
	SDL_DestroyTexture(exit);
	SDL_DestroyTexture(backButton);
	SDL_DestroyTexture(exitButton);
	SDL_DestroyTexture(playAgain);
}

void Menu::Setup() {
	font = TTF_OpenFont("res/font/SVN-Times New Roman 2 bold.ttf", 35);
	font2 = TTF_OpenFont("res/font/SVN-Times New Roman 2 bold.ttf", 55);

	/*MENU*/ //MENU: 0: play game, 1: exit, 2: info, 3: music;
	//dst
	TextureManager::SetPos(pos_menu[PLAY_GAME], Vector2D(290, 220), Vector2D(250, 75));
	//                                          vi tri dat tren cua so      kich thuoc
	TextureManager::SetPos(pos_menu[EXIT], Vector2D(360, 320), Vector2D(100, 75));
	TextureManager::SetPos(pos_menu[INFOR], Vector2D(570, 190), Vector2D(64, 64));
	TextureManager::SetPos(pos_menu[MUSIC], Vector2D(42, 15), Vector2D(32, 32));
	//texture
	menu = TextureManager::LoadTexture("res/gfx/Background/background.png");
	infor = TextureManager::LoadTexture("res/gfx/Button/information.png");
	play = TextureManager::LoadTexture("res/gfx/Button/play.png");
	exit = TextureManager::LoadTexture("res/gfx/Button/exit.png");
	music = TextureManager::LoadTexture("res/gfx/Button/music.png");
	theme_music.loadMusic("res/audio/music/theme song.mp3");

	/*OPTION*/ //OPTION: 0: player1, 1: player2
	//dst
	for (int i = 0; i < NUM_PLAYER; i++)
		TextureManager::SetPos(pos_opt[i], Vector2D(250, 105 + i * 160), Vector2D(300, 130));
	//texture
	option = TextureManager::LoadTexture("res/gfx/Background/option_background.png");
	mode[PLAYER_1] = TextureManager::LoadTexture("res/gfx/Button/1P.png");
	mode[PLAYER_2] = TextureManager::LoadTexture("res/gfx/Button/2P.png");

	// STATE_PLAY NEW PLAY: 1, CONTINUE: 0
	for (int i = 0; i < STATE_PLAY; i++)
		TextureManager::SetPos(pos_state[i], Vector2D(250, 105 + i * 160), Vector2D(300, 130));
	//texture
    state[NEW_PLAY] = TextureManager::LoadTexture("res/gfx/Button/new_play.png");
	state[CONTINUE] = TextureManager::LoadTexture("res/gfx/Button/continue.png");

	/*END*/ //END: 0: play again, 1: exit, 2: back
	//dst
	TextureManager::SetPos(pos_end[PLAY_AGAIN], Vector2D(130, 310), Vector2D(210, 100));
	TextureManager::SetPos(pos_end[EXIT], Vector2D(500, 310), Vector2D(210, 100));
	TextureManager::SetPos(pos_end[BACK], Vector2D(20, 20), Vector2D(64, 64));
	//texture
	backButton = TextureManager::LoadTexture("res/gfx/Button/backButton.png");
	exitButton = TextureManager::LoadTexture("res/gfx/Button/exitButton.png");
	playAgain = TextureManager::LoadTexture("res/gfx/Button/again.png");
	game_score.Setup(GameText::LIGHT_YELLOW_TEXT);
}

// check chuot
bool Menu::CheckFocusWithRect(const short int& x, const short int& y, const SDL_Rect& rect) {
	return (x >= rect.x && x <= rect.x + rect.w
		   	&& y >= rect.y && y <= rect.y + rect.h);
}

short int Menu::showMenu() {
	if (!theme_music.isPlaying())
		theme_music.playMusic(30);
	TextureManager::SetPos(src_menu[PLAY_GAME], Vector2D(0, 0), Vector2D(225, 50));
	//                                    vi tri trong anh nguon  kich thuoc anh nguon
	TextureManager::SetPos(src_menu[EXIT], Vector2D(0, 0), Vector2D(78, 50));
	TextureManager::SetPos(src_menu[INFOR], Vector2D(0, 0), Vector2D(64, 64));
	if (!selected[MUSIC])
		TextureManager::SetPos(src_menu[MUSIC], Vector2D(0, 0), Vector2D(32, 32));
	else
		TextureManager::SetPos(src_menu[MUSIC], Vector2D(32, 0), Vector2D(32, 32));


	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, menu, NULL, NULL);
		SDL_RenderCopy(Game::renderer, play, &src_menu[PLAY_GAME], &pos_menu[PLAY_GAME]);
		SDL_RenderCopy(Game::renderer, exit, &src_menu[EXIT], &pos_menu[EXIT]);
		SDL_RenderCopy(Game::renderer, infor, &src_menu[INFOR], &pos_menu[INFOR]);
		SDL_RenderCopy(Game::renderer, music, &src_menu[MUSIC], &pos_menu[MUSIC]);
		SDL_RenderPresent(Game::renderer);
		while (SDL_PollEvent(&m_event)) {
			switch(m_event.type) {
				case SDL_QUIT:
					SDL_DestroyTexture(menu);
					SDL_DestroyTexture(infor);
					SDL_DestroyTexture(play);
					SDL_DestroyTexture(exit);
					SDL_DestroyTexture(music);
					return EXIT; // 1
				case SDL_MOUSEMOTION:
					xm = m_event.motion.x;
					ym = m_event.motion.y;
					if (CheckFocusWithRect(xm, ym, pos_menu[PLAY_GAME])) {
						if (!selected[PLAY_GAME]) {
							selected[PLAY_GAME] = 1;
							TextureManager::SetPos(src_menu[PLAY_GAME], Vector2D(225, 0), Vector2D(225, 50));
						}
					}
					else {
						if (selected[PLAY_GAME]) {
							selected[PLAY_GAME] = 0;
							TextureManager::SetPos(src_menu[PLAY_GAME], Vector2D(0, 0), Vector2D(225, 50));
						}
					}


					if (CheckFocusWithRect(xm, ym, pos_menu[EXIT])) {
						if (!selected[EXIT]) {
							selected[EXIT] = 1;
							TextureManager::SetPos(src_menu[EXIT], Vector2D(78, 0), Vector2D(78, 50));
						}
					}
					else {
						if (selected[EXIT]) {
							selected[EXIT] = 0;
							TextureManager::SetPos(src_menu[EXIT], Vector2D(0, 0), Vector2D(78, 50));
						}
					}


					if (CheckFocusWithRect(xm, ym, pos_menu[INFOR])) {
						if (!selected[INFOR]) {
							selected[INFOR] = 1;
							TextureManager::SetPos(src_menu[INFOR], Vector2D(64, 0), Vector2D(64, 64));
						}
					}
					else {
						if (selected[INFOR]) {
							selected[INFOR] = 0;
							TextureManager::SetPos(src_menu[INFOR], Vector2D(0, 0), Vector2D(64, 64));
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					xm = m_event.button.x;
					ym = m_event.button.y;
					if (CheckFocusWithRect(xm, ym, pos_menu[PLAY_GAME])) {
						return PLAY_GAME; // 0
					}
					if (CheckFocusWithRect(xm, ym, pos_menu[EXIT])) {
						return EXIT; // 1
					}
					if (CheckFocusWithRect(xm, ym, pos_menu[INFOR])) {
						return INFOR; // 2
					}
					if (CheckFocusWithRect(xm, ym, pos_menu[MUSIC])) {
						if (!selected[MUSIC]) {
							selected[MUSIC] = 1;
							TextureManager::SetPos(src_menu[MUSIC], Vector2D(32, 0), Vector2D(32, 32));
							theme_music.pause();
						}
						else if (selected[MUSIC]) {
							selected[MUSIC] = 0;
							TextureManager::SetPos(src_menu[MUSIC], Vector2D(0, 0),Vector2D(32, 32));
							theme_music.resume();
						}
					}
					break;
				case SDL_KEYDOWN:
					if (m_event.key.keysym.sym == SDLK_ESCAPE) {
						return EXIT; // 0
					}
				default:
					break;
			}
		}
	}
	return EXIT;
}

short int Menu::getNumPlayer() {
	for (int i = 0; i < NUM_PLAYER; i++) {
		TextureManager::SetPos(src_opt[i], Vector2D(0, 0), Vector2D(300, 130));
	}

	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, option, NULL, NULL);
		for (int i = 0; i < NUM_PLAYER; i++) {
			SDL_RenderCopy(Game::renderer, mode[i], &src_opt[i], &pos_opt[i]);
		}
		SDL_RenderPresent(Game::renderer);
		while (SDL_PollEvent(&m_event)) {
			switch(m_event.type) {
				case SDL_QUIT:
					return 0;
				case SDL_MOUSEMOTION:
					xm = m_event.motion.x;
					ym = m_event.motion.y;
					for (int i = 0; i < NUM_PLAYER; i++) {
						if (CheckFocusWithRect(xm, ym, pos_opt[i])) {
							if (!selected_opt[i]) {
								selected_opt[i] = 1;
								TextureManager::SetPos(src_opt[i], Vector2D(300, 0), Vector2D(300, 130));
							}
						}
						else {
							if (selected_opt[i]) {
								selected_opt[i] = 0;
								TextureManager::SetPos(src_opt[i], Vector2D(0, 0), Vector2D(300, 130));
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					xm = m_event.button.x;
					ym = m_event.button.y;
					for (int i = 0; i < NUM_PLAYER; i++) {
						if (CheckFocusWithRect(xm, ym, pos_opt[i])) {
							return i + 1;
						}
					}
					break;
				case SDL_KEYDOWN:
					if (m_event.key.keysym.sym == SDLK_ESCAPE) {
						return 0;
					}
				default:
					break;
			}
		}
	}
	return 0;
}

short int Menu::getStatePlay(){
	std::ifstream file("res/Continue.txt");
    int mark = 0;

	//file rong
	std::string s = "";
	file >> s;
	if(s == "")
        mark = 1;

    for(int i = 0; i < STATE_PLAY-mark; i++){
		TextureManager::SetPos(src_state[i], Vector2D(0, 0), Vector2D(300, 130));
    }

    	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, option, NULL, NULL);
		for (int i = 0; i < STATE_PLAY-mark; i++) {
			SDL_RenderCopy(Game::renderer, state[i], &src_state[i], &pos_state[i]);
		}
		SDL_RenderPresent(Game::renderer);
		while (SDL_PollEvent(&m_event)) {
			switch(m_event.type) {
				case SDL_QUIT:
					return 0;
				case SDL_MOUSEMOTION:
					xm = m_event.motion.x;
					ym = m_event.motion.y;
					for (int i = 0; i < STATE_PLAY-mark; i++) {
						if (CheckFocusWithRect(xm, ym, pos_state[i])) {
							if (!selected_state[i]) {
								selected_state[i] = 1;
								TextureManager::SetPos(src_state[i], Vector2D(300, 0), Vector2D(300, 130));
							}
						}
						else {
							if (selected_state[i]) {
								selected_state[i] = 0;
								TextureManager::SetPos(src_state[i], Vector2D(0, 0), Vector2D(300, 130));
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					xm = m_event.button.x;
					ym = m_event.button.y;
					for (int i = 0; i < STATE_PLAY-mark; i++) {
						if (CheckFocusWithRect(xm, ym, pos_state[i])) {
							return i + 1;
						}
					}
					break;
				case SDL_KEYDOWN:
					if (m_event.key.keysym.sym == SDLK_ESCAPE) {
						return 0;
					}
				default:
					break;
			}
		}
	}
	return 0;
}


short int Menu::endMenu(const char* path) {
	end = TextureManager::LoadTexture(path);
	TextureManager::SetPos(src_end[PLAY_AGAIN], Vector2D(0, 0), Vector2D(210, 100));
	TextureManager::SetPos(src_end[EXIT], Vector2D(0, 0), Vector2D(210, 100));
	TextureManager::SetPos(src_end[BACK], Vector2D(0, 0), Vector2D(64, 64));

    int mark = -1;
	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, end, NULL, NULL);
		SDL_RenderCopy(Game::renderer, playAgain, &src_end[PLAY_AGAIN], &pos_end[PLAY_AGAIN]);
		SDL_RenderCopy(Game::renderer, exitButton, &src_end[EXIT], &pos_end[EXIT]);
		SDL_RenderCopy(Game::renderer, backButton, &src_end[BACK], &pos_end[BACK]);
		SDL_RenderPresent(Game::renderer);
		mark = eventEndMenu();
		if(mark!=-1)
            return mark;
	}
	return 1;
}

short int Menu::endMenu(const char* path, const int& score) {
	end = TextureManager::LoadTexture(path);
	game_score.Update(score, "Your score: ");
	game_score.CreateText();
	TextureManager::SetPos(src_end[PLAY_AGAIN], Vector2D(0, 0), Vector2D(210, 100));
	TextureManager::SetPos(src_end[EXIT], Vector2D(0, 0), Vector2D(210, 100));
	TextureManager::SetPos(src_end[BACK], Vector2D(0, 0), Vector2D(64, 64));

    int mark = -1;
	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, end, NULL, NULL);
		SDL_RenderCopy(Game::renderer, playAgain, &src_end[PLAY_AGAIN], &pos_end[PLAY_AGAIN]);
		SDL_RenderCopy(Game::renderer, exitButton, &src_end[EXIT], &pos_end[EXIT]);
		SDL_RenderCopy(Game::renderer, backButton, &src_end[BACK], &pos_end[BACK]);
		game_score.Render2(Vector2D(240, 170), Vector2D(340, 100));
		SDL_RenderPresent(Game::renderer);
		mark = eventEndMenu();
		if(mark!=-1)
            return mark;
	}
	return 1;
}

short int Menu::eventEndMenu(){
    while (SDL_PollEvent(&m_event)) {
        switch(m_event.type) {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for (int i = 0; i <= 1; i++) {
                    if (CheckFocusWithRect(xm, ym, pos_end[i])) {
                        if (!selected_end[i]) {
                            selected_end[i] = 1;
                            TextureManager::SetPos(src_end[i], Vector2D(210, 0), Vector2D(210, 100));
                        }
                    }
                    else {
                        if (selected_end[i]) {
                            selected_end[i] = 0;
                            TextureManager::SetPos(src_end[i], Vector2D(0, 0), Vector2D(210, 100));
                        }
                    }
                }
                if (CheckFocusWithRect(xm, ym, pos_end[BACK])) {
                    if (!selected_end[BACK]) {
                        selected_end[BACK] = 1;
                        TextureManager::SetPos(src_end[BACK], Vector2D(64, 0), Vector2D(64, 64));
                    }
                }
                else {
                    if (selected_end[BACK]) {
                        selected_end[BACK] = 0;
                        TextureManager::SetPos(src_end[BACK], Vector2D(0, 0), Vector2D(64, 64));
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = m_event.button.x;
                ym = m_event.button.y;

                for (int i = 0; i <= 1; i++) {
                    if (CheckFocusWithRect(xm, ym, pos_end[i])) {
                        return i;
                    }
                }
                if (CheckFocusWithRect(xm, ym, pos_end[BACK])) {
                        return 2;
                }
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }
                break;
            default:
                break;
        }
    }
    return -1;
}


void Menu::FreeTexture() {
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(infor);
	SDL_DestroyTexture(play);
	SDL_DestroyTexture(exit);
	SDL_DestroyTexture(backButton);
	SDL_DestroyTexture(exitButton);
	SDL_DestroyTexture(playAgain);
}
