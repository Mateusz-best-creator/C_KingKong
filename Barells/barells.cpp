#include "barells.h"
#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"

void init_barells(const BoardElements& board, Barell* barells)
{
	int dir = 0;
	for (size_t i = 0; i < board.barells_amount; i++)
	{
		barells[i].row = board.barells_rows[i];
		dir = board.barells_direction[i];
		barells[i].direction = dir;
		if (dir == 0)
		{
			barells[i].x_coordinate = board.barells_left_border[i];
		}
		else
		{
			barells[i].x_coordinate = board.barells_right_border[i];
		}
		barells[i].right_border = board.barells_right_border[i];
		barells[i].left_border = board.barells_left_border[i];
		barells[i].y_coordinate = board.barells_y_coordinate[i];
	}
}

void move_barells(Barell* barells, const BoardElements& board, const SDL_Surfaces& surfaces)
{
	// Move all barells
	for (size_t i = 0; i < board.barells_amount; i++)
	{
		draw_barell(barells[i], surfaces);
		move_barell(barells[i], board.level);
	}
}

void draw_barell(Barell& barell, const SDL_Surfaces& surfaces)
{
	DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_1), int(barell.x_coordinate), int(barell.y_coordinate));
}

void move_barell(Barell& barell, int level)
{
	// 0 means left, 1 means right
	if (barell.direction == 1 && barell.x_coordinate >= barell.right_border)
		barell.direction = 0;
	else if (barell.direction == 0 && barell.x_coordinate <= barell.left_border)
		barell.direction = 1;

	if (barell.direction == 1)
		move_barell_right(barell);
	else if (barell.direction == 0)
		move_barell_left(barell);
}

void move_barell_right(Barell& barell)
{
	if (barell.x_coordinate >= barell.right_border)
		barell.x_coordinate = barell.left_border;
	barell.x_coordinate += BARELL_SPEED;
}

void move_barell_left(Barell& barell)
{
	if (barell.x_coordinate <= barell.left_border)
		barell.x_coordinate = barell.right_border;
	barell.x_coordinate -= BARELL_SPEED;
}

