#include "../functions_definitions.h"
#include "../Interface/interface.h"
#include "../Mario/mario.h"
#include "../read_write_to_file/read_write_to_file.h"
#include "../playersAccount/players_account.h"

#include <string.h>
#include <iostream>

bool game(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, int& level_switch)
{
	// Initialize all the colors
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);

	int x = 1, y = 1, option = 1;
	if (level_switch == CANT_SWITCH_LEVEL)
		initial_interface(surfaces, SDL_elements, colors, x, y, mario_info.name);
	else
	{
		x = 2;
		y = level_switch;
		level_switch = CANT_SWITCH_LEVEL;
	}
	BoardElements board;
	
	mario_info.all_points = 0;

	int mario_won = 0;

	// Player choose to quit
	if (x == 1 && y == 1)
		return false;
	// Choosing to play 
	else if (x == 2)
	{
		// Initialize the board and based on that mario initial coordinates
		board = initialize_board(y);
		mario_info.x_coordinate = board.initial_mario_x;
		mario_info.y_coordinate = board.initial_mario_y;

		mario_won = start_game(mario_info, surfaces, SDL_elements, board, false);
		mario_info.has_trophy = false;
		if (mario_won == SWITCH_TO_LEVEL_1 || mario_won == SWITCH_TO_LEVEL_2 || mario_won == SWITCH_TO_LEVEL_3)
		{
			level_switch = mario_won - 2;
			return true;
		}

		while (mario_won == 1)
		{
			mario_info.levels_completed++;
			mario_info.all_points = mario_info.level_1_best_score + mario_info.level_2_best_score + mario_info.level_3_best_score;
			mario_info.points = 0;
			if (mario_info.levels_completed >= 3)
			{
				mario_info.levels_completed = 0;
				congratulations_interface(surfaces, SDL_elements);
				return true;
			}
			y++;
			if (y > 3)
				y = 1;
			releaseMemory(board);
			board = initialize_board(y);
			mario_won = start_game(mario_info, surfaces, SDL_elements, board, false);
		}
	}
	// Loading game from file option
	else if (x == 1 && y == 3)
	{
		strcpy(mario_info.name, "Unknown");
		start_game(mario_info, surfaces, SDL_elements, board, true);
	}
	// Authentication section
	else if (x == 3 && y == 1)
	{
		mario_info.name[0] = '\0';
		strcpy(mario_info.name, authentication_interface(mario_info, surfaces, SDL_elements, colors));
		return true;
	}
	else if (x == 3 && y == 2)
		players_account(surfaces, SDL_elements);
	else if (x == 3 && y == 3)
		hall_of_fame(surfaces, SDL_elements);
	else if (x == 1 && y == 2)
	{
		infinite_game(surfaces, SDL_elements);
		return true;
	}
	return true;
}