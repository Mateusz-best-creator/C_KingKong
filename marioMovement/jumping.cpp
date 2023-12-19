#include "../functions_definitions.h"

void jump(SDL_Surface* screen, SDL_Surface* mario, int mario_x_coordinate,
	int mario_y_coordinate, bool& jumping, int& jumping_pixels, bool& going_down)
{
	// Print mario x, y coordinates to the console
	//std::cout << "(x, y) = (" << mario_x_coordinate << ", " << mario_y_coordinate << ")\n";
	if (jumping)
	{
		if (jumping_pixels > 30 || going_down)
		{
			going_down = true;
			jumping_pixels -= 1;
		}
		else
		{
			jumping_pixels += 1;
		}
		DrawSurface(screen, mario, mario_x_coordinate, mario_y_coordinate - jumping_pixels);
		if (jumping_pixels == 0 && going_down)
			jumping = false;
	}
	else
	{
		// Draw mario surface
		DrawSurface(screen, mario, mario_x_coordinate, mario_y_coordinate);
	}
}
