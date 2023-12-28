#include "../functions_definitions.h"
#include "../Interface/interface.h"
#include "../Mario/mario.h"
#include <iostream>

static int levels_completed = 0;
static int POINTS = 0;

bool game(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, bool initial_state)
{
	// Initialize all the colors
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);

	int x = 1, y = 1, option = 1;
	initial_interface(surfaces, SDL_elements, colors, x, y);

	BoardElements board;
	Mario mario_info;

	bool mario_won = false;

	// Player choose to quit
	if (x == 1 && y == 1)
		exit(0);
	// Choosing to play 
	else if (x == 2)
	{
		board = initialize_board(y);
		mario_info = { board.initial_mario_x, board.initial_mario_y, false, false, 0, false, Mario::RIGHT, false, false, 0, 0, 1, false };
		mario_won = start_game(mario_info, surfaces, SDL_elements, board, false, 0, false, initial_state);
		while (mario_won)
		{
			levels_completed++;
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
	
		start_game(mario_info, surfaces, SDL_elements, board, false, 0, true, true); // Always load as initial state
	}
	// Authentication section
	else if (x == 3 && y == 2)
	{
		save_game(mario_info);
	}
	else if (x != 2)
		exit(0);

	releaseMemory(board);
	return false;
}