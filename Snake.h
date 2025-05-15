#pragma once
#include <SDL3/SDL.h>

class Snake
{
public:
	Snake();
	~Snake();

	void init();
	void drawSnake(SDL_Renderer* renderer);
	void move();
	void setDirection(int horiz, int vert);
	SDL_Point* getDirection();

private:
	SDL_FRect snek;
	SDL_Point direction;
	int velocity;
};