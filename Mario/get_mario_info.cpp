#include "../functions_definitions.h"
#include "../Mario/mario.h"

void get_mario_info(Mario& mario_info, const BoardElements& board, int& mario_row)
{
	// Based on platforms y coordinates, determine in which row mario is
	if (mario_info.y_coordinate <= 390 && mario_info.y_coordinate > 330)
		mario_row = 1;
	else if (mario_info.y_coordinate <= 330 && mario_info.y_coordinate > 270)
		mario_row = 2;
	else if (mario_info.y_coordinate <= 270 && mario_info.y_coordinate > 210)
		mario_row = 3;
	else if (mario_info.y_coordinate <= 210 && mario_info.y_coordinate > 150)
		mario_row = 4;
	else if (mario_info.y_coordinate <= 150 && mario_info.y_coordinate > 90)
		mario_row = 5;

	bool through_ladder = false;
	bool above_ladder = false;
	for (size_t i = 0; i < board.amount_of_ladders; i++)
	{
		if (mario_info.x_coordinate >= board.ladders_x_coordinates[i] &&
			mario_info.x_coordinate <= board.ladders_x_coordinates[i] + board.ladder_width && mario_row == board.ladders_rows[i])
		{
			through_ladder = true;
		}
		// Check if mario is above the ladder
		if (mario_info.x_coordinate >= board.ladders_x_coordinates[i] &&
			mario_info.x_coordinate <= board.ladders_x_coordinates[i] + board.ladder_width && mario_row - 1 == board.ladders_rows[i])
		{
			above_ladder = true;
		}
	}
	if (through_ladder)
		mario_info.going_through_the_ladder = true;
	else
		mario_info.going_through_the_ladder = false;
	if (above_ladder)
		mario_info.above_ladder = true;
	else
		mario_info.above_ladder = false;
}

