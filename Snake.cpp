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
	numSubgridMoves = snek.h / velocity;

	length = 1;
}

void Snake::move() {
	snek.x += direction.x * velocity;
	snek.y += direction.y * velocity;
}

void Snake::setVelocity(int vel) {
	velocity = 0;
}

void Snake::setDirection(int horiz, int vert) {
	direction.x = horiz;
	direction.y = vert;
}

SDL_Point* Snake::getDirection() {
	return &direction;
}

SDL_FRect* Snake::getPosition() {
	return &snek;
}

int Snake::getNumSubgridMoves() {
	return numSubgridMoves;
}

int Snake::getLength() {
	return length;
}