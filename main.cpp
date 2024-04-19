#include "Game.h"
#include "Menu.h"

Game* game = nullptr;
Menu* GameMenu = nullptr;

void Home();

int main(int argc, char* argv[]) {

	srand(time(0));

	game = new Game();
	game->initWindow();

	GameMenu = new Menu();
	GameMenu->Setup();

    Home();
    std::cout << "toi dang o day\n";
    delete game;
	delete GameMenu;
	std::cout << "chuong trinh da hoan thanh\n";

 	return 0;
}


void Home(){
    int i = GameMenu->showMenu();

    if (i == EXIT) //exit
        Game::isRunning = false;

    else if (i == INFOR) {
        //game instruction
        SDL_Texture* infor_text;
        infor_text = TextureManager::LoadTexture("res/gfx/Background/infor_text.png");
        while (true) {
            SDL_RenderCopy(Game::renderer, infor_text, NULL, NULL);
            SDL_RenderPresent(Game::renderer);
            while (SDL_PollEvent(&Game::event)) {
                switch(Game::event.type) {
                    case SDL_QUIT:
                        exit(0);
                    case SDL_KEYDOWN:
                        switch(Game::event.key.keysym.sym) {
                            case SDLK_ESCAPE: break;
                            case SDLK_h:
                                SDL_DestroyTexture(infor_text);
                                Home();
                                return;
                        }
                }
            }
        }
    }

    else {
        //play game
        int numberOfPlayer = GameMenu->getNumPlayer();
        if (numberOfPlayer == 1) {
            game->gameLoop();
            if (Game::home == true){
                Home();
                return;
            }
        }

        else if (numberOfPlayer == 2) {
            game->gameLoop2();
            if (Game::home == true){
                Home();
                return;
            }
        }
    }
}
