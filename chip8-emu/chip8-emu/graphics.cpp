#include <iostream>
#include <SDL.h>
#include "graphics.hpp"

void Graphics::init() {
	//setting virtual scaling
	scale = 20;
	//Positioning and resizing the virtual pixels
	for (int i = 0; i < DISPLAY_HEIGHT; i++)
	{
		for (int j = 0; j < DISPLAY_WIDTH; j++)
		{
			pixels[j + (i*DISPLAY_WIDTH)].w = scale;
			pixels[j + (i*DISPLAY_WIDTH)].h = scale;
			pixels[j + (i*DISPLAY_WIDTH)].x = j * scale;
			pixels[j + (i*DISPLAY_WIDTH)].y = i * scale;
		}
	}

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Chip8 emulator - LDD",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		DISPLAY_WIDTH * scale,
		DISPLAY_HEIGHT * scale,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

}

void Graphics::clean() {

}

void Graphics::render(unsigned char* grid) {
	/* Clearing the screen */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	/* Drawing each pixel individually */
	SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
	for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++){
		if (grid[i] == 1) {
			SDL_RenderDrawRect(renderer, &pixels[i]);
			SDL_RenderFillRect(renderer, &pixels[i]);
			SDL_RenderPresent(renderer);
		}
	}
}

void Graphics::clear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}