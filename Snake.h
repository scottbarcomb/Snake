#pragma once
#include <SDL3/SDL.h>

class Snake
{
public:
	Snake();
	~Snake();

	void init();
	void move();
	void setVelocity(int vel);
	void setDirection(int horiz, int vert);
	SDL_Point* getDirection();
	SDL_FRect* getPosition();
	int getNumSubgridMoves();
	int getLength();

private:
	SDL_FRect snek;
	SDL_Point direction;
	int velocity;
	int numSubgridMoves;
	int length;
};