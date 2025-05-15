#include "Snake.h"
#include <iostream>

using namespace std;

Snake::Snake() : snek() {}

Snake::~Snake() {}

void Snake::init() {
	snek.x = 0.0;
	snek.y = 0.0;
	snek.h = 20.0;
	snek.w = 20.0;

	direction.x = 0;
	direction.y = 1; // move down

	velocity = 4;
}

void Snake::drawSnake(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &snek);
}

void Snake::move() {
	snek.x += direction.x * velocity;
	snek.y += direction.y * velocity;
}

void Snake::setDirection(int horiz, int vert) {
	direction.x = horiz;
	direction.y = vert;
}

SDL_Point* Snake::getDirection() {
	return &direction;
}