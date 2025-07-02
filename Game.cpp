#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), snake(nullptr) {}

Game::~Game() {}

bool Game::init(const char* title, int width, int height) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}

	if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return false;
	}

	snake = new Snake();
	snake->init();
	

	LEFTBORDER = 0;
	RIGHTBORDER = width - snake->getPosition()->w;
	TOPBORDER = 0;
	BOTTOMBORDER = height - snake->getPosition()->h;

	isRunning = true;
	return true;
}

void Game::run() {
	while (isRunning) {
		handleEvents(); // handle any events triggered between frames
		update(); // update the game state (snake, apples, points, etc.)
		render(); // render the next frame
		SDL_Delay(20); // basic frame control (50 FPS)
	}
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			isRunning = false;
		}
		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_ESCAPE) {
				isRunning = false;
			}
			// snake direction controls
			snakeDir = snake->getDirection();
			if ((event.key.scancode == SDL_SCANCODE_W || event.key.key == SDLK_UP) && snakeDir->y != 1) {
				snake->setDirection(0, -1);
			}
			if ((event.key.scancode == SDL_SCANCODE_S || event.key.key == SDLK_DOWN) && snakeDir->y != -1) {
				snake->setDirection(0, 1);
			}
			if ((event.key.scancode == SDL_SCANCODE_A || event.key.key == SDLK_LEFT) && snakeDir->x != 1) {
				snake->setDirection(-1, 0);
			}
			if ((event.key.scancode == SDL_SCANCODE_D || event.key.key == SDLK_RIGHT) && snakeDir->x != -1) {
				snake->setDirection(1, 0);
			}
		}
	}
}

void Game::update() {
	// Wall collision check
	checkSnakeCollision();

	// Move the snake
	moveSnake();

}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	// snake and food will be drawn here
	drawSnake();

	SDL_RenderPresent(renderer);
}

void Game::drawSnake() {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int i = 0; i < snake->getLength(); i++) {
		SDL_RenderFillRect(renderer, snake->getPosition());
	}
}

void Game::moveSnake() {
	// Move the snake and re-render by number of Subgrid moves
	// Say the grid size is 20px, and the snake's velocity is 4,
	// then the snake will move for 5 frames before any other
	// game updates occur.
	for (int i = 1; i < snake->getNumSubgridMoves(); i++) {
		snake->move();
		render();
		SDL_Delay(20);
	}
	snake->move();
}

void Game::checkSnakeCollision() {
	snakePos = snake->getPosition();
	snakeDir = snake->getDirection();

	// Check wall collisions
	if (snakePos->x == LEFTBORDER && snakeDir->x == -1) {
		snake->setVelocity(0);
	}
	else if (snakePos->x == RIGHTBORDER && snakeDir->x == 1) {
		snake->setVelocity(0);
	}
	else if (snakePos->y == TOPBORDER && snakeDir->y == -1) {
		snake->setVelocity(0);
	}
	else if (snakePos->y == BOTTOMBORDER && snakeDir->y == 1) {
		snake->setVelocity(0);
	}
}

void Game::cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}