#include "mario.h"
#include "../functions_definitions.h"
#include "../Barells/barells.h"
#include "../LevelsBoards/boards.h"

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
			start_game(surfaces, elements, board, true, mario_info.points, false);
			return;
		}
	}
}