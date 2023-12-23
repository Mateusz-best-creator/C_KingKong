#include "../functions_definitions.h"

void draw_mario(SDL_Surfaces& surfaces, Mario& mario_info)
{
	if (mario_info.jumping)
	{
		if (mario_info.jumping_pixels > JUMP_HEIGHT || mario_info.going_down)
		{
			mario_info.going_down = true;
			mario_info.jumping_pixels -= JUMP_SPEED;
		}
		else
		{
			mario_info.jumping_pixels += JUMP_SPEED;
		}
		// Draw appropirate mario image while jumping
		if (mario_info.direction == Mario::RIGHT)
		{
			DrawSurface(*(surfaces.screen), *(surfaces.mario_jumping_right), 
				mario_info.x_coordinate, mario_info.y_coordinate - mario_info.jumping_pixels);
		}
		else
		{
			DrawSurface(*(surfaces.screen), *(surfaces.mario_jumping_left),
				mario_info.x_coordinate, mario_info.y_coordinate - mario_info.jumping_pixels);
		}
		if (!mario_info.jumping_pixels && mario_info.going_down)
			mario_info.jumping = false;
	}
	else if (mario_info.going_through_the_ladder)
	{
		// Draw mario_climbing surface
		DrawSurface(*(surfaces.screen), *(surfaces.mario_climbing), mario_info.x_coordinate, mario_info.y_coordinate);
	}
	else
	{
		// Draw mario surface
		if (mario_info.direction == Mario::RIGHT)
		{
			DrawSurface(*(surfaces.screen), *(surfaces.mario_running_right), mario_info.x_coordinate, mario_info.y_coordinate);
		}
		else
		{
			DrawSurface(*(surfaces.screen), *(surfaces.mario_running_left), mario_info.x_coordinate, mario_info.y_coordinate);
		}
	}
}
