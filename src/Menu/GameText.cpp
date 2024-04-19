 #include "GameText.h"

GameText::~GameText() {
    Free();
}

void GameText::SetText(const std::string &text) {
	str_val = text;
}

void GameText::SetColor(const int &type) {
	if (type == RED_TEXT) {
		SDL_Color color = {255, 0, 0};
		text_color = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Color color = {255, 255, 255};
		text_color = color;
	}
	else if (type == BLACK_TEXT) {
		SDL_Color color = {0, 0, 0};
		text_color = color;
	}
	else if (type == GREEN_TEXT) {
		SDL_Color color = {34, 139, 34};
		text_color = color;
	}
	else if (type == PINK_TEXT) {
		SDL_Color color = {249, 109, 109};
		text_color = color;
	}
	else if (type == LIGHT_YELLOW_TEXT) {
		SDL_Color color = {238, 232, 170};
		text_color = color;
	}
}

void GameText::CreateGameText(TTF_Font *font, const SDL_Rect &dstR) {
	Free(); // giai phong noi dung ma texture dang nam giu
	surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color); // tao surface chua van ban mau text_color;
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_RenderCopy(Game::renderer, texture, nullptr, &dstR); // null la sao chep toan bo texture
	SDL_FreeSurface(surface);
}

void GameText::Init(TTF_Font* font) {
	surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
}

void GameText::Render(const SDL_Rect &dstR) {
	SDL_RenderCopy(Game::renderer, texture, NULL, &dstR);
}

void GameText::Free() {
	SDL_DestroyTexture(texture);
}
