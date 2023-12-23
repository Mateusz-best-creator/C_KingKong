#include "../Mario/mario.h"

bool check_if_mario_win(const BoardElements& board, Mario& mario)
{
	if (mario.x_coordinate >= board.winning_x1_coordinate && mario.x_coordinate <= board.winning_x2_coordinate
		&& mario.y_coordinate == board.winning_y_coordinate)
	{
		mario.points += POINTS_FOR_COMPLETING_LEVEL;
		return true;
	}
	return false;
}