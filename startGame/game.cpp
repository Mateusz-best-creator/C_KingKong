#include "../functions_definitions.h"
#include "../Interface/interface.h"
#include "../Mario/mario.h"
#include <iostream>

static int levels_completed = 0;
static char name[21] = { "Unknown" };


bool game(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, bool initial_state, bool reset_levels)
{
	if (reset_levels)
		levels_completed = 0;

	// Initialize all the colors
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);

	int x = 1, y = 1, option = 1;
	initial_interface(surfaces, SDL_elements, colors, x, y, name);

	BoardElements board;
	Mario mario_info;
	mario_info.all_points = 0;

	bool mario_won = false;

	// Player choose to quit
	if (x == 1 && y == 1)
		return false;
	// Choosing to play 
	else if (x == 2)
	{
		board = initialize_board(y);
		mario_info = { board.initial_mario_x, board.initial_mario_y, false, false, 0, false, Mario::RIGHT, false, false, 0, 0, 0, 1, false };

		if (std::strcmp(name, "Unknown") != 0)
		{
			std::strcpy(mario_info.name, name);
			levels_completed = 0;
		}
		else
			std::strcpy(mario_info.name, "Unknown");
		mario_won = start_game(mario_info, surfaces, SDL_elements, board, false, 0, false, initial_state);
		while (mario_won)
		{
			levels_completed++;
			std::cout << "MARIO WON!" << std::endl;
			mario_info.all_points = mario_info.level_1_best_score + mario_info.level_2_best_score + mario_info.level_3_best_score;
			if (levels_completed >= 3)
			{
				levels_completed = 0;
				congratulations_interface(surfaces, SDL_elements);
				return true;
			}
			y++;
			if (y > 3)
				y = 1;
			releaseMemory(board);
			board = initialize_board(y);
			mario_won = start_game(mario_info, surfaces, SDL_elements, board, false, 0, false, false);
		}
	}
	// Loading game from file option
	else if (x == 1 && y == 3)
	{
		std::strcpy(mario_info.name, "Unknown");
		start_game(mario_info, surfaces, SDL_elements, board, false, 0, true, true); // Always load as initial state
	}
	// Authentication section
	else if (x == 3 && y == 1)
	{
		std::cout << "authentication!!!" << std::endl;
		std::strcpy(name, authentication_interface(mario_info, surfaces, SDL_elements));
		return true;
	}
	else if (x != 2)
		return false;

	return true;
}