#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "functions_definitions.h"
#include "./LevelsBoards/boards.h"


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) 
{
	// Initialize all SDL elements
	SDL_Event event;
	SDL_Surface* screen = nullptr, *charset = nullptr, *mario_running_right = nullptr, *mario_running_left = nullptr, *king_kong = nullptr, 
		*mario_climbing = nullptr, *mario_jumping_right = nullptr, *mario_jumping_left = nullptr, *rolling_barell = nullptr;

	// Create structure of all surfaces
	SDL_Surfaces surfaces = { &screen, &charset, &mario_running_right, &mario_running_left, 
		&king_kong, &mario_climbing, &mario_jumping_right, &mario_jumping_left, &rolling_barell };
	// Create structure of other SDL elements (except event)
	SDL_Elements SDL_elements = { nullptr, nullptr, nullptr };

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	bool SDL_Error;
	SDL_Error = fullscreen(&(SDL_elements.window), &(SDL_elements.renderer));
	if (SDL_Error)
		return 1;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(SDL_elements.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(SDL_elements.renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(SDL_elements.window, "Mateusz Wieczorek s197743 Data Engeineering group 3");

	int depth = 32;
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, depth,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL_elements.scrtex = SDL_CreateTexture(SDL_elements.renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy��czenie widoczno�ci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// Loading all .bmp images
	SDL_Error = load_bmp_images(surfaces, SDL_elements.scrtex, SDL_elements.window, SDL_elements.renderer);
	if (SDL_Error)
		return 1;

	// Initialize all the colors
	Colors colors;
	initialize_colors(screen, colors);

	// Initialize the board for the appropriate level
	BoardElements board = initialize_board(1);
	start_game(surfaces, SDL_elements, board);
	return 0;
};

