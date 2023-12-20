#include "../functions_definitions.h"
#include <iostream>

// This global variable will store the y coordinate when mario enters the ladder
int initial_mario_ladder_y = 0;

int handleEvents(SDL_Event& event, Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
	// Variable stores information in which row mario currently is
	int mario_row = 0;
	int amount_of_ladders = LEVEL_1_AMOUNT_OF_LADDERS;

	for (size_t i = 0; i < amount_of_ladders; i++)
	{
		if (mario_info.y_coordinate <= 390 - i * PLATFORM_HEIGHT && mario_info.y_coordinate >= 330 - i * PLATFORM_HEIGHT)
		{
			mario_row = i + 1;
			break;
		}
	}

	if ((mario_info.x_coordinate >= FIRST_THIRD_FIFTH_ROW_LADDER_X &&
		mario_info.x_coordinate <= FIRST_THIRD_FIFTH_ROW_LADDER_X + LADDER_WIDTH &&
		mario_row % 2 == 1) ||
		(mario_info.x_coordinate >= SECOND_FOURTH_ROW_LADDER_X &&
			mario_info.x_coordinate <= SECOND_FOURTH_ROW_LADDER_X + LADDER_WIDTH &&
			mario_row % 2 == 0))
	{
		if (initial_mario_ladder_y == 0)
			initial_mario_ladder_y = mario_info.y_coordinate;
		mario_info.going_through_the_ladder = true;
	}
	else
		mario_info.going_through_the_ladder = false;

	// handling of events (if there were any)
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) return 1;
			else if (event.key.keysym.sym == SDLK_n)
			{
				start_game(surfaces, SDL_elements);
				return 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				if (mario_info.x_coordinate >= SCREEN_RIGHT_X_BORDER || 
					(mario_info.going_through_the_ladder && initial_mario_ladder_y != mario_info.y_coordinate))
					continue;
				mario_info.direction = Mario::RIGHT;
				mario_info.x_coordinate += MARIO_SPEED;
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				std::cout << initial_mario_ladder_y << " " << mario_info.y_coordinate << std::endl;
				if (mario_info.x_coordinate <= SCREEN_LEFT_X_BORDER ||
					(mario_info.going_through_the_ladder && initial_mario_ladder_y != mario_info.y_coordinate))
					continue;
				mario_info.direction = Mario::LEFT;
				mario_info.x_coordinate -= MARIO_SPEED;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				if (mario_info.going_through_the_ladder)
				{
					mario_info.y_coordinate -= MARIO_SPEED;
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (!mario_info.jumping && !mario_info.going_through_the_ladder)
				{
					// Jumping, important helper variables
					mario_info.jumping = true;
					mario_info.going_down = false;
					mario_info.jumping_pixels = 0;
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				std::cout << "Mario row: " << mario_row << std::endl;
				std::cout << "Mario x coordinate: " << mario_info.x_coordinate << std::endl;
				std::cout << "Mario y coordinate: " << mario_info.y_coordinate << std::endl;
				
				if (mario_info.going_through_the_ladder)
				{
					if (mario_info.y_coordinate < SCREEN_BOTTOM_Y_BORDER && mario_row == 1) // We can't go under the board
						mario_info.y_coordinate += MARIO_SPEED;
				}
			}
			break;
		case SDL_QUIT:
			return 1;
		};
	};
}
