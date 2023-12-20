#include "../functions_definitions.h"
#include <iostream>

int handleEvents(SDL_Event& event, int& mario_x_coordinate, int& mario_y_coordinate,
	bool& jumping, bool& going_down, int& jumping_pixels, bool& going_through_the_ladder)
{
	// Variable stores information in which row mario currently is
	int mario_row = 0;
	int amount_of_ladders = LEVEL_1_AMOUNT_OF_LADDERS;

	for (size_t i = 0; i < amount_of_ladders; i++)
	{
		if (mario_y_coordinate <= 390 - i * PLATFORM_HEIGHT && mario_y_coordinate >= 330 - i * PLATFORM_HEIGHT)
		{
			mario_row = i + 1;
			break;
		}
	}

	if ((mario_x_coordinate >= FIRST_THIRD_FIFTH_ROW_LADDER_X &&
		mario_x_coordinate <= FIRST_THIRD_FIFTH_ROW_LADDER_X + LADDER_WIDTH &&
		mario_row % 2 == 1) ||
		(mario_x_coordinate >= SECOND_FOURTH_ROW_LADDER_X &&
			mario_x_coordinate <= SECOND_FOURTH_ROW_LADDER_X + LADDER_WIDTH &&
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
				if (mario_x_coordinate >= SCREEN_RIGHT_X_BORDER || going_through_the_ladder)
					continue;
				mario_x_coordinate += MARIO_SPEED;
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				if (mario_x_coordinate <= SCREEN_LEFT_X_BORDER || going_through_the_ladder)
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
					// Jumping, important helper variables
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
					if (mario_y_coordinate < SCREEN_BOTTOM_Y_BORDER && mario_row == 1) // We can't go under the board
						mario_y_coordinate += MARIO_SPEED;
				}
			}
			break;
		case SDL_QUIT:
			return 1;
		};
	};
}
