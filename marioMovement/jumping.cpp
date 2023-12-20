#include "../functions_definitions.h"

void jump(SDL_Surface* screen, SDL_Surface* mario_running_right, SDL_Surface* mario_running_left, SDL_Surface* mario_climbing, 
	SDL_Surface* mario_jumping, Mario& mario_info)
{
	// Print mario x, y coordinates to the console
	//std::cout << "(x, y) = (" << mario_x_coordinate << ", " << mario_y_coordinate << ")\n";
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
		DrawSurface(screen, mario_jumping, mario_info.x_coordinate, mario_info.y_coordinate - mario_info.jumping_pixels);
		if (!mario_info.jumping_pixels && mario_info.going_down)
			mario_info.jumping = false;
	}
	else if (mario_info.going_through_the_ladder)
	{
		// Draw mario-climbing surface
		DrawSurface(screen, mario_climbing, mario_info.x_coordinate, mario_info.y_coordinate);
	}
	else
	{
		// Draw mario surface
		if (mario_info.direction == Mario::RIGHT)
		{
			DrawSurface(screen, mario_running_right, mario_info.x_coordinate, mario_info.y_coordinate);
		}
		else
		{
			DrawSurface(screen, mario_running_left, mario_info.x_coordinate, mario_info.y_coordinate);
		}
	}
}
