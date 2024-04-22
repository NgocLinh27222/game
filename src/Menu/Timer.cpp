#include "Timer.h"

Timer::~Timer() {
	Free();
}

void Timer::Setup() {
	font = TTF_OpenFont("res/font/EvilEmpire-4BBVK.ttf", 35);
	time_text.SetColor(GameText::WHITE_TEXT);
}

void Timer::Render() {
	TextureManager::SetPos(dst_timer, {340, 550}, {150, 50});
	time_text.CreateGameText(font, dst_timer);
}

void Timer::Update() {
	std::string strTime = "Timer: ";
	time_val = 60 - (SDL_GetTicks() -  Game::time_0) / 1000; // SDL_GetTicks tra ve thoi gian mili s
	//60 seconds countdown
	val_str_time = std::to_string(time_val);
	strTime += val_str_time;
	time_text.SetText(strTime);
}

Uint32 Timer::getTimeVal() {
	return time_val;
}

void Timer::Free() {
	time_text.Free();
}
