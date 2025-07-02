#pragma once
#include "Snake.h"
#include <SDL3/SDL.h>
#include <vector>

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

	void drawSnake();
	void moveSnake();
	void checkSnakeCollision();

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Snake* snake;
	SDL_Point* snakeDir;
	SDL_FRect* snakePos;
	vector<SDL_FRect*> snakeSegments;

	int LEFTBORDER;
	int RIGHTBORDER;
	int TOPBORDER;
	int BOTTOMBORDER;
};