#include "barells.h"
#include "../functions_definitions.h"

void draw_barell(Barell& barell, SDL_Surfaces& surfaces)
{
	DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_1), barell.x_coordinate, barell.y_coordinate);
	/*if (barell.image_index > 6)
		barell.image_index = 1;
	switch (barell.image_index)
	{
	case 1:
		DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_6), barell.x_coordinate, barell.y_coordinate);
		break;
	case 2:
		DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_5), barell.x_coordinate, barell.y_coordinate);
		break;
	case 3:
		DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_4), barell.x_coordinate, barell.y_coordinate);
		break;
	case 4:
		DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_3), barell.x_coordinate, barell.y_coordinate);
		break;
	case 5:
		DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_2), barell.x_coordinate, barell.y_coordinate);
		break;
	case 6:
		DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_1), barell.x_coordinate, barell.y_coordinate);
		break;
	}
	barell.image_index++;*/
}

void move_barell(Barell& barell)
{
	if (barell.direction == 1)
		move_barell_right(barell);
	else if (barell.direction == 0)
		move_barell_left(barell);
}

void move_barell_right(Barell& barell)
{
	if (barell.x_coordinate >= SCREEN_WIDTH - 20)
		barell.x_coordinate = 50;
	barell.x_coordinate += BARELL_SPEED;
}

void move_barell_left(Barell& barell)
{
	if (barell.x_coordinate <= 50)
		barell.x_coordinate = SCREEN_WIDTH - 20;
	barell.x_coordinate -= BARELL_SPEED;
}