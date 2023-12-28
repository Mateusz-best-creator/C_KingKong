#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "functions_definitions.h"
#include "./LevelsBoards/boards.h"
#include "./Interface/interface.h"
#include "./read_write_to_file/read_write_to_file.h"
#include <cstdlib>

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) 
{
	// Initialize all SDL elements
	SDL_Surface* screen = nullptr, * charset = nullptr, * mario_running_right = nullptr, * mario_running_left = nullptr, * king_kong = nullptr,
		* mario_climbing = nullptr, * mario_jumping_right = nullptr, * mario_jumping_left = nullptr, * level_1_crown = nullptr,
		* level_2_treasure = nullptr, * level_3_diamond = nullptr, * level_1_winning_icon = nullptr, * level_2_winning_icon = nullptr,
		* level_3_winning_icon = nullptr, * coin_icon, * heart_icon = nullptr, * rolling_barell_1 = nullptr, * quit_icon = nullptr,
		* report_icon = nullptr, * golden_cup_icon = nullptr, * authentication_icon = nullptr, * generate_level_icon = nullptr, * loading_icon = nullptr;

	// Create structure of all surfaces
	SDL_Surfaces surfaces = { &screen, &charset, &mario_running_right, &mario_running_left,
		&king_kong, &mario_climbing, &mario_jumping_right, &mario_jumping_left, &level_1_crown,
		&level_2_treasure, &level_3_diamond, &level_1_winning_icon, &level_2_winning_icon, &level_3_winning_icon,
		&coin_icon, &heart_icon, &rolling_barell_1, & quit_icon, & report_icon, &golden_cup_icon,
		&authentication_icon, & generate_level_icon, &loading_icon };

	// Create structure of other SDL elements
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

	bool play_again = false;
	play_again = game(surfaces, SDL_elements, true);
	while (play_again)
		play_again = game(surfaces, SDL_elements, true);

	// Clear all the settings
	clearSDL(*(surfaces.charset), screen, SDL_elements.scrtex, SDL_elements.renderer, SDL_elements.window);
	return 0;
};

