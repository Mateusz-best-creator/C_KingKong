#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "functions_definitions.h"
#include <iostream>


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) 
{
	SDL_Event event;
	SDL_Surface* screen = nullptr, *charset = nullptr, *mario = nullptr, *king_kong = nullptr, 
		*mario_climbing = nullptr, *mario_jumping = nullptr;
	SDL_Texture* scrtex = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	bool SDL_Error;
	SDL_Error = fullscreen(&window, &renderer);
	if (SDL_Error)
		return 1;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Mateusz Wieczorek s197743 Data Engeineering group 3");

	int depth = 32;
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, depth,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy��czenie widoczno�ci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// Loading all .bmp images
	SDL_Error = load_bmp_images(&mario, &king_kong, &mario_climbing, &mario_jumping, &charset, screen, scrtex, window, renderer);
	if (SDL_Error)
		return 1;

	int czarny, zielony, czerwony, niebieski, brazowy;
	// Initialize all the colors
	initialize_colors(screen, czarny, zielony, czerwony, niebieski, brazowy);

	// Initialize all helper variables for measuring the time, frames, fps...
	int tick1, tick2, quit = 0, frames = 0;
	double delta, worldTime = 0.0, fpsTimer = 0.0, fps = 0.0, distance = 0.0, etiSpeed = 0.0;
	tick1 = SDL_GetTicks();

	// Initial mario coordinates
	int mario_x_coordinate = 50, mario_y_coordinate = 387;

	// Boolean that indicates whether or not Mario is jumping
	bool jumping = false;
	int jumping_pixels = 0;
	bool going_down = false;

	bool going_through_the_ladder = false;

	while (!quit) {

		calculateTime(delta, tick1, tick2, worldTime);

		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, czarny);

		// Draw all ladders
		DrawLadders(screen, brazowy);

		// Draw all platforms
		DrawPlatforms(screen, brazowy);

		// Make mario jumping if possible, draw mario
		jump(screen, mario, mario_climbing, mario_jumping, mario_x_coordinate, mario_y_coordinate, 
			jumping, jumping_pixels, going_down, going_through_the_ladder);

		// Draw king_kong surface
		DrawSurface(screen, king_kong, LEVEL1_KING_KONG_X, LEVEL1_KING_KONG_Y);

		fpsTimer += delta;
		if (fpsTimer > SECONDS_BETWEEN_REFRESH) {
			fps = frames * REFRESH_RATE;
			frames = 0;
			fpsTimer -= SECONDS_BETWEEN_REFRESH;
		};

		char text[128];
		drawInfoRectangle(charset, screen, scrtex, renderer, text, worldTime, fps, czerwony, niebieski);
		
		// Handle user event (space, upper arrow...)
		quit = handleEvents(event, mario_x_coordinate, mario_y_coordinate, 
			jumping, going_down, jumping_pixels, going_through_the_ladder);
		frames++;
	};
	// Clear all the settings
	clearSDL(charset, screen, scrtex, renderer, window);
	return 0;
};

