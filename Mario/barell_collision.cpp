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
			mario_info.lifes--;
			if (mario_info.lifes <= 0)
			{
				game(surfaces, elements, true);
				break;
			}
			bool play_again = continue_interface(surfaces, elements);
			if (!play_again)
				game(surfaces, elements, true);
			else
				start_game(surfaces, elements, board, true, mario_info.points, false, false);
			return;
		}
	}
}