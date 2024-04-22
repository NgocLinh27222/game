#include "Game.h"

#include "TextureManager.h"
#include "Snake.h"
#include "Fruit.h"
#include "Score.h"
#include "Map.h"
#include "Snake2.h"
#include "Menu.h"

#include <string>

SDL_Texture* background = nullptr;

Snake snake;
Snake2 snake2;

Fruit fruit;

std::string Game::filepath = "";
Map map_current;

Menu endBackground;

bool Game::isRunning = false;
bool Game::home;
Uint32 Game::time_0;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::~Game() {
	window = NULL;
	renderer = NULL;
	SDL_DestroyTexture(background);
}

void Game::initWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    	logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Initialize the truetype font API.
	if (TTF_Init() < 0)
		logSDLError(std::cout, "TTF_Init", true);
    isRunning = true;
}

void Game::logSDLError(std::ostream& os, const std::string &msg, bool fatal = false) {
	os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void Game::randTypeMap(){
    short int tmp = rand()%4 + 1;
    filepath = "res/map/map" + std::to_string(tmp) + ".txt";
    //std::cout << filepath << std::endl;
}

void Game::setup() {
	Game::isRunning = true;
	background = TextureManager::LoadTexture("res/gfx/Background/background_play.png");
	randTypeMap();
	map_current.Setup(filepath);
	snake.Setup("res/gfx/Snake/snake.png");

	fruit.Setup("res/gfx/Snake/Fruits/fruits.png");
    Fruit::randTypeFruit();
    do{
        Fruit::Respawn();
    }
    while ( snake.fruitInsideSnake() || snake.fruitInsideBlock() );

    endBackground.Setup();
    home = false;
}

void Game::setupContinue() {
    Game::isRunning = true;
    background = TextureManager::LoadTexture("res/gfx/Background/background_play.png");
    std::ifstream file;
    file.open("res/Continue.txt");
    file >> filepath;
    map_current.Setup(filepath);
    snake.setupContinueSnake(file, "res/gfx/Snake/snake.png");
    fruit.setupContinueFruit(file, "res/gfx/Snake/Fruits/fruits.png");
    file.close();

    endBackground.Setup();
    home = false;
}

void Game::setup2() {
	Game::isRunning = true;
    background = TextureManager::LoadTexture("res/gfx/Background/background_play.png");
    randTypeMap();
    map_current.Setup(filepath);
    snake2.Setup();
    fruit.Setup("res/gfx/Snake/Fruits/fruits.png");
    Fruit::randTypeFruit();
    do{
        Fruit::Respawn();
    }
    while( snake2.player1.fruitInsideSnake() || snake2.player1.fruitInsideSnake(snake2.player2) || snake2.player1.fruitInsideBlock() );

    time_0 = SDL_GetTicks();
    endBackground.Setup();
    home = false;
}

void Game::recordContinueGame() {
	std::ofstream outfile;
	outfile.open("res/Continue.txt", std::ios::out | std::ios::trunc);
	outfile << filepath << std::endl;
	snake.recordContinueSnake(outfile);
	fruit.recordContinueFruit(outfile);
	outfile.close();
}

bool Game::running() {
	return isRunning;
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT :
			if (MessageBoxA(NULL, "Do you wanna quit?", "End game", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                    // hien thi hop thoai cau hoi yes no trong thu vien window.h   // IDYES : YES
                recordContinueGame();
				isRunning = false;
				Quit = 1;
			}
		default:
			break;
	}
}

void Game::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

void Game::update() {
	snake.Update();
	snake.UpdateScore("Score: ");
	snake.UpdateHighestScore();
	fruit.Update();
}

void Game::update2() {
	snake2.Update();
	fruit.Update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	snake.Render();
	map_current.Setup(filepath);
	snake.RenderScore({SCORE_X, SCORE_Y}, {SCORE_W, SCORE_HEIGHT});
	snake.RenderHighestScore({HISCORE_X, HISCORE_Y}, {HISCORE_W, HISCORE_H});
	fruit.Render();
	SDL_RenderPresent(renderer);
}

void Game::render2() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	snake2.Render();
	map_current.Setup(filepath);
	fruit.Render();
	SDL_RenderPresent(renderer);
}

void Game::gameLoopNew() {
	setup();
	gameLoop1_running();
}

void Game::gameLoopContinue() {
    setupContinue();
    gameLoop1_running();
}

void Game::gameLoop1_running() {
    while (running()) {
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();

        // gioi han toc do khung hinh cua tro troi
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        if (Quit == 1)
            isRunning = false;
        else {
            if (!isRunning) {
                std::ofstream outfile;
                outfile.open("res/Continue.txt", std::ios::out | std::ios::trunc);
                outfile << "";
                outfile.close();
                short int chooseOption = endBackground.endMenu("res/gfx/Background/game_over.png", snake.getScore());

                if (chooseOption == PLAY_AGAIN) {
                    SDL_RenderClear(renderer);
                    endBackground.FreeTexture();
                    setup();
                    isRunning = true;
                }
                else if (chooseOption == BACK) {
                    SDL_RenderClear(renderer);
                    endBackground.FreeTexture();
                    home = true;
                }
            }
        }
    }
}

void Game::gameLoop2() {
	setup2();
	while (running()) {
		frameStart = SDL_GetTicks();

		handleEvents();
		update2();
		render2();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

		if (Quit == 1) {
			isRunning = false;
		}
		else {
			if (!isRunning) {
                std::ofstream outfile;
                outfile.open("res/Continue.txt", std::ios::out | std::ios::trunc);
                outfile << "";
                outfile.close();
				if (snake2.isWinner() == 1) {
					short int chooseOption = endBackground.endMenu("res/gfx/Background/P1_win.png");
					if (chooseOption == PLAY_AGAIN) {
						SDL_RenderClear(renderer);
						endBackground.FreeTexture();
						setup2();
						isRunning = true;
					}
					else if (chooseOption == BACK) {
						SDL_RenderClear(renderer);
						endBackground.FreeTexture();
						home = true;
					}
				}
				else if (snake2.isWinner() == 2) {
					short int chooseOption = endBackground.endMenu("res/gfx/Background/P2_win.png");
					if (chooseOption == PLAY_AGAIN) {
						SDL_RenderClear(renderer);
						endBackground.FreeTexture();
						setup2();
						isRunning = true;
					}
					else if (chooseOption == BACK) {
						SDL_RenderClear(renderer);
						endBackground.FreeTexture();
						home = true;
					}
				}
				else {
					int chooseOption = endBackground.endMenu("res/gfx/Background/tie.png");
					if (chooseOption == PLAY_AGAIN) {
						setup2();
						endBackground.FreeTexture();
						isRunning = true;
					}
					else if (chooseOption == BACK) {
						SDL_RenderClear(renderer);
						endBackground.FreeTexture();
						home = true;
					}
				}
			}
		}
	}
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Shutdown and cleanup the truetype font API.
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
