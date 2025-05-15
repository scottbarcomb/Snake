#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false) {}

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

	isRunning = true;
	return true;
}

void Game::run() {
	while (isRunning) {
		handleEvents(); // handle any events triggered between frames
		update(); // update the game state (snake, apples, points, etc.)
		render(); // render the next frame
		SDL_Delay(100); // basic frame control (10 FPS)
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
			// snake direction controls are gonna go here
		}
	}
}

void Game::update() {
	// calls to update the snake and food are gonna go here
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	// snake and food will be drawn here

	SDL_RenderPresent(renderer);
}

void Game::cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}