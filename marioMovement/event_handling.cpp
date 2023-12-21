#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include <iostream>

const int MARIO_FLOOR_DISTANCE = 3;

int handleEvents(SDL_Event& event, Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, const BoardElements& board)
{
	// Variable stores information in which row mario currently is
	int mario_row = 0;

	for (size_t i = 0; i < board.platforms_amount; i++)
	{
		if (mario_info.y_coordinate <= board.platforms_y_coordinates[i] && 
			mario_info.y_coordinate >= board.platforms_y_coordinates[i] - board.platform_height)
		{
			mario_row = i + 1;
			break;
		}
	}

	for (size_t i = 0; i < board.amount_of_ladders; i++)
	{
		if (mario_info.x_coordinate >= board.ladders_x_coordinates[i] &&
			mario_info.x_coordinate <= board.ladders_x_coordinates[i] + board.ladder_width && mario_row == board.ladders_rows[i])
		{
			mario_info.going_through_the_ladder = true;
			break;
		}
		else
			mario_info.going_through_the_ladder = false;

		// Check if mario is above the ladder
		if (mario_info.x_coordinate >= board.ladders_x_coordinates[i] &&
			mario_info.x_coordinate <= board.ladders_x_coordinates[i] + board.ladder_width && mario_row - 1 == board.ladders_rows[i])
		{
			mario_info.above_ladder = true;
			break;
		}
		else
			mario_info.above_ladder = false;
	}

	// handling of events (if there were any)
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) return 1;
			else if (event.key.keysym.sym == SDLK_n)
			{
				start_game(surfaces, SDL_elements, board);
				return 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				if (mario_info.x_coordinate >= SCREEN_RIGHT_X_BORDER)
					continue;
				bool mario_can_go_right_from_ladder = false;
				for (size_t i = 0; i < board.platforms_amount; i++)
				{
					if (mario_info.y_coordinate + MARIO_FLOOR_DISTANCE == board.platforms_y_coordinates[i])
					{
						mario_can_go_right_from_ladder = true;
						break;
					}
				}
				if (mario_info.going_through_the_ladder && !mario_can_go_right_from_ladder)
					continue;
				mario_info.direction = Mario::RIGHT;
				mario_info.x_coordinate += MARIO_SPEED;
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				if (mario_info.x_coordinate <= SCREEN_LEFT_X_BORDER)
					continue;
				bool mario_can_go_left_from_ladder = false;
				for (size_t i = 0; i < board.platforms_amount; i++)
				{
					if (mario_info.y_coordinate + MARIO_FLOOR_DISTANCE == board.platforms_y_coordinates[i])
					{
						mario_can_go_left_from_ladder = true;
						break;
					}
				}
				if (mario_info.going_through_the_ladder && !mario_can_go_left_from_ladder)
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
				if (mario_info.going_through_the_ladder)
				{
					mario_info.can_go_down = true;
					for (size_t k = 0; k < board.platforms_amount; k++)
					{
						if (board.platforms_y_coordinates[k] == mario_info.y_coordinate + MARIO_FLOOR_DISTANCE)
						{
							mario_info.can_go_down = false;
							break;
						}
					}
					if (mario_info.can_go_down)
						mario_info.y_coordinate += MARIO_SPEED;
				}
				else if (mario_info.above_ladder)
				{
					mario_info.y_coordinate += MARIO_SPEED;
					mario_info.going_through_the_ladder = true;
				}
			}
			break;
		case SDL_QUIT:
			return 1;
		};
	};
}
