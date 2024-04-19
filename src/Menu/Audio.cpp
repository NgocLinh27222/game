#include "Audio.h"

Audio::Audio() {
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		std::cout << "Audio Error" << Mix_GetError();
}

Audio::~Audio() {
	Mix_FreeChunk(chunk);
	Mix_FreeMusic(music);
}

void Audio::loadSound(const char *path) {
	chunk = Mix_LoadWAV(path);
	if (chunk == NULL) {
		std::cout << "Audio Error " << Mix_GetError();
		exit(0);
	}
}

void Audio::loadMusic(const char* path) {
	music = Mix_LoadMUS(path);
	if (music == NULL) {
		std::cout << "Audio Error" << Mix_GetError();
		exit(0);
	}
}

void Audio::playSound() {
	Mix_PlayChannel(-1, chunk, 0);
}

void Audio::playSound(const int& v) {
    volume = (MIX_MAX_VOLUME * v) / 100;// phan tram am luong phat ra
	Mix_Volume(-1, volume); // dieu chinh am luong
	Mix_PlayChannel(-1, chunk, 0); // 0 : phat mot lan
}

void Audio::playMusic() {
	Mix_PlayMusic(music, -1); // -1 phat ban nhac lap vo han cho den khi lenh dung
}

void Audio::playMusic(const int& v) {
	volume = (MIX_MAX_VOLUME * v) / 100;
	Mix_VolumeMusic(volume);
	Mix_PlayMusic(music, -1);
}

bool Audio::isPlaying() {
	return Mix_PlayingMusic();
}

void Audio::pause() {
	Mix_PauseMusic();
}

void Audio::resume() {
	Mix_ResumeMusic();
}
