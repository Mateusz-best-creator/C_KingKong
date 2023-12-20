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
	// Initialize all SDL elements
	SDL_Event event;
	SDL_Surface* screen = nullptr, *charset = nullptr, *mario_running_right = nullptr, *mario_running_left = nullptr, *king_kong = nullptr, 
		*mario_climbing = nullptr, *mario_jumping = nullptr;
	SDL_Texture* scrtex = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Create structure of all surfaces
	SDL_Surfaces surfaces = { &screen, &charset, &mario_running_right, &mario_running_left, &king_kong, &mario_climbing, &mario_jumping };

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
	SDL_Error = load_bmp_images(surfaces, scrtex, window, renderer);
	if (SDL_Error)
		return 1;

	// Initialize all the colors
	Colors colors;
	initialize_colors(screen, colors);

	// Initialize all helper variables for measuring the time, frames, fps...
	TimeVariables times = { SDL_GetTicks(), 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// Create mario object
	Mario mario_info = { mario_initial_x_coordinate, mario_initial_y_coordinate, false, false, 0, false, Mario::RIGHT };

	while (!times.quit) {

		calculateTime(times.delta, times.tick1, times.tick2, times.worldTime);

		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, colors.czarny);

		// Draw all ladders
		DrawLadders(screen, colors.brazowy);

		// Draw all platforms
		DrawPlatforms(screen, colors.brazowy);

		// Make mario jumping if possible, draw mario
		jump(screen, mario_running_right, mario_running_left, mario_climbing, mario_jumping, mario_info);

		// Draw king_kong surface
		DrawSurface(screen, king_kong, LEVEL1_KING_KONG_X, LEVEL1_KING_KONG_Y);

		times.fpsTimer += times.delta;
		if (times.fpsTimer > SECONDS_BETWEEN_REFRESH) {
			times.fps = times.frames * REFRESH_RATE;
			times.frames = 0;
			times.fpsTimer -= SECONDS_BETWEEN_REFRESH;
		};

		char text[128];
		drawInfoRectangle(charset, screen, scrtex, renderer, text, times, colors);
		
		// Handle user event (space, upper arrow...)
		times.quit = handleEvents(event, mario_info);
		times.frames++;
	};
	// Clear all the settings
	clearSDL(charset, screen, scrtex, renderer, window);
	return 0;
};

