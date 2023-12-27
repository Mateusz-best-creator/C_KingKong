#include "../functions_definitions.h"
#include "../Interface/interface.h"
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

	bool mario_won = false;

	// Player choose to quit
	if (x == 1 && y == 1)
		exit(0);
	// Choosing to play 
	else if (x == 2)
	{
		board = initialize_board(y);
		mario_won = start_game(surfaces, SDL_elements, board, false, 0, false, initial_state);
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
			mario_won = start_game(surfaces, SDL_elements, board, false, 0, false, false);
		}
	}
	// Loading game from file option
	else if (x == 1 && y == 3)
		start_game(surfaces, SDL_elements, board, false, 0, true, true); // Always load as initial state
	// Authentication section
	else if (x == 3 && y == 2)
	{

	}
	else if (x != 2)
		exit(0);

	releaseMemory(board);
	return false;
}