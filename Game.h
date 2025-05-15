#pragma once
#include "Snake.h"
#include <SDL3/SDL.h>

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int width, int height);
	void run();
	void cleanup();

private:
	void handleEvents();
	void update();
	void render();

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Snake* snake;
	SDL_Point* direction;
};