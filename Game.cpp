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
			direction = snake->getDirection();
			if ((event.key.scancode == SDL_SCANCODE_W || event.key.key == SDLK_UP) && direction->y != 1) {
				snake->setDirection(0, -1);
			}
			if ((event.key.scancode == SDL_SCANCODE_S || event.key.key == SDLK_DOWN) && direction->y != -1) {
				snake->setDirection(0, 1);
			}
			if ((event.key.scancode == SDL_SCANCODE_A || event.key.key == SDLK_LEFT) && direction->x != 1) {
				snake->setDirection(-1, 0);
			}
			if ((event.key.scancode == SDL_SCANCODE_D || event.key.key == SDLK_RIGHT) && direction->x != -1) {
				snake->setDirection(1, 0);
			}
		}
	}
}

void Game::update() {
	// calls to update the snake and food are gonna go here
	snake->move();
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	// snake and food will be drawn here
	snake->drawSnake(renderer);

	SDL_RenderPresent(renderer);
}

void Game::cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}