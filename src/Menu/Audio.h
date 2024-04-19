#ifndef AUDIO_H
#define AUDIO_H

#include "Game.h"

class Audio {
	Mix_Chunk* chunk = NULL; // hieu ung am thanh ngan
	Mix_Music* music = NULL; // hieu ung am thanh dai
	int volume;

public:
	Audio();
	~Audio();

	void loadSound(const char* path);
	void loadMusic(const char* path);

	void playSound();
	void playSound(const int& v);

	void playMusic();
	void playMusic(const int& v);

	bool isPlaying();
	void pause();
	void resume();
};

#endif // AUDIO_H
