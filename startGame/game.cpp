#include "../functions_definitions.h"
#include "../Interface/interface.h"
#include "../Mario/mario.h"
#include <iostream>

static int levels_completed = 0;
static int points = 0;
static char name[21] = { "Unknown" };

bool game(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, bool initial_state)
{
	// Initialize all the colors
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);

	int x = 1, y = 1, option = 1;
	initial_interface(surfaces, SDL_elements, colors, x, y, name);

	BoardElements board;
	Mario mario_info;
	mario_info.all_points = 0 + points;

	bool mario_won = false;

	// Player choose to quit
	if (x == 1 && y == 1)
		exit(0);
	// Choosing to play 
	else if (x == 2)
	{
		board = initialize_board(y);
		mario_info = { board.initial_mario_x, board.initial_mario_y, false, false, 0, false, Mario::RIGHT, false, false, 0, 0, 0, 1, false };
		
		if (std::strcmp(name, "Unknown") != 0)
			std::strcpy(mario_info.name, name);
		else
			std::strcpy(mario_info.name, "Unknown");
		mario_won = start_game(mario_info, surfaces, SDL_elements, board, false, 0, false, initial_state);
		while (mario_won)
		{
			points += POINTS_FOR_COMPLETING_LEVEL;
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
		std::strcpy(mario_info.name, "Unknown");
		start_game(mario_info, surfaces, SDL_elements, board, false, 0, true, true); // Always load as initial state
	}
	// Authentication section
	else if (x == 3 && y == 1)
	{
		std::strcpy(name, authentication_interface(mario_info, surfaces, SDL_elements));
		return true;
	}
	else if (x != 2)
		exit(0);

	releaseMemory(board);
	return false;
}