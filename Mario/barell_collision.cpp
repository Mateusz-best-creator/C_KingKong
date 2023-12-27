#include "mario.h"
#include "../functions_definitions.h"
#include "../Barells/barells.h"
#include "../LevelsBoards/boards.h"
#include "../Interface/interface.h"

void collision_with_barell(Mario& mario_info, Barell* barells, 
	BoardElements& board, SDL_Surfaces& surfaces, SDL_Elements& elements)
{
	for (size_t i = 0; i < board.barells_amount; i++)
	{
		if (mario_info.mario_row != barells[i].row || mario_info.going_through_the_ladder)
			continue;
		if (((mario_info.x_coordinate <= barells[i].x_coordinate + 20 &&
			mario_info.x_coordinate >= barells[i].x_coordinate) ||
			(mario_info.x_coordinate - 14 + 30 >= barells[i].x_coordinate &&
			mario_info.x_coordinate - 14 + 30 <= barells[i].x_coordinate + 25)) && !mario_info.jumping)
		{
			// Update lifes
			mario_info.lifes--;
			if (mario_info.lifes <= 0)
			{
				save_after_lost_interface(surfaces, elements, mario_info, board);
				return;
			}
			bool play_again = continue_interface(surfaces, elements, mario_info, board);
			if (!play_again)
				game(surfaces, elements, true);
			else
				start_game(surfaces, elements, board, true, 0, false, false);
			return;
		}
	}
}