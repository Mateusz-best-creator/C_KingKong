#include "../functions_definitions.h"
#include <iostream>

int handleEvents(SDL_Event& event, int& mario_x_coordinate, int& mario_y_coordinate,
	bool& jumping, bool& going_down, int& jumping_pixels, bool& going_through_the_ladder)
{
	// Variable stores information in which row mario currently is
	int mario_row = 0;
	for (size_t i = 0; i < 5; i++)
	{
		if (mario_y_coordinate <= 390 - i * 60 && mario_y_coordinate >= 330 - i * 60)
		{
			mario_row = i + 1;
			break;
		}
	}

	if ((mario_x_coordinate >= FIRST_THIRD_FIFTH_ROW_LADDER_X &&
		mario_x_coordinate <= FIRST_THIRD_FIFTH_ROW_LADDER_X + 30 && // 30 -> ladder width
		mario_row % 2 == 1) ||
		(mario_x_coordinate >= SECOND_FOURTH_ROW_LADDER_X &&
			mario_x_coordinate <= SECOND_FOURTH_ROW_LADDER_X + 30 &&
			mario_row % 2 == 0))
	{
		going_through_the_ladder = true;
	}
	else
		going_through_the_ladder = false;

	// handling of events (if there were any)
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) return 1;
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				if (mario_x_coordinate >= 629)
					continue;
				mario_x_coordinate += MARIO_SPEED;
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				if (mario_x_coordinate <= 11)
					continue;
				mario_x_coordinate -= MARIO_SPEED;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				if (going_through_the_ladder)
				{
					mario_y_coordinate -= MARIO_SPEED;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (!jumping && !going_through_the_ladder)
				{
					// Jump important helper variables
					jumping = true;
					going_down = false;
					jumping_pixels = 0;
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				std::cout << "Mario row: " << mario_row << std::endl;
				std::cout << "Mario x coordinate: " << mario_x_coordinate << std::endl;
				std::cout << "Mario y coordinate: " << mario_y_coordinate << std::endl;
				if (going_through_the_ladder)
				{
					if ((mario_y_coordinate < 387 && mario_row == 1) || // We can't go under the board
						(mario_y_coordinate > 1239))
						mario_y_coordinate += MARIO_SPEED;
				}
			}
			break;
		case SDL_QUIT:
			return 1;
		};
	};
}
