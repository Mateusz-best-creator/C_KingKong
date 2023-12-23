#include "../functions_definitions.h"
#include "../Mario/mario.h"

void get_mario_info(Mario& mario_info, const BoardElements& board, int& mario_row)
{
	for (size_t i = 0; i < board.platforms_amount; i++)
	{
		if (mario_info.y_coordinate <= board.platforms_y_coordinates[i] &&
			mario_info.y_coordinate >= board.platforms_y_coordinates[i] - board.platform_height)
		{
			mario_row = i + 1;
			break;
		}
	}

	for (size_t i = 0; i < board.amount_of_ladders; i++)
	{
		if (mario_info.x_coordinate >= board.ladders_x_coordinates[i] &&
			mario_info.x_coordinate <= board.ladders_x_coordinates[i] + board.ladder_width && mario_row == board.ladders_rows[i])
		{
			mario_info.going_through_the_ladder = true;
			break;
		}
		else
			mario_info.going_through_the_ladder = false;

		// Check if mario is above the ladder
		if (mario_info.x_coordinate >= board.ladders_x_coordinates[i] &&
			mario_info.x_coordinate <= board.ladders_x_coordinates[i] + board.ladder_width && mario_row - 1 == board.ladders_rows[i])
		{
			mario_info.above_ladder = true;
			break;
		}
		else
			mario_info.above_ladder = false;
	}
}