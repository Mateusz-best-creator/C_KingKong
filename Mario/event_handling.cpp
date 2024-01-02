#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"
#include "../read_write_to_file/read_write_to_file.h"

#include <cstdlib>
#include <iostream>

int handleEvents(SDL_Event& event, Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, 
	BoardElements& board, Barell* barells, FallingBarell& flying_barell, TimeVariables& times)
{
	// Variable stores information in which row mario currently is
	int mario_row = 1;
	get_mario_info(mario_info, board, mario_row);
	mario_info.mario_row = mario_row;

	if (mario_info.jumping)
	{
		return CANT_MOVE;
	}
	// handling of events (if there were any)
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
			else if (event.key.keysym.sym == SDLK_s)
			{
				save_game_state(mario_info, board, barells, flying_barell, times);
				exit(0);
			}
			else if (event.key.keysym.sym == SDLK_1)
			{
				return SWITCH_TO_LEVEL_1;
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				return SWITCH_TO_LEVEL_2;
			}
			else if (event.key.keysym.sym == SDLK_3)
			{
				return SWITCH_TO_LEVEL_3;
			}
			else if (event.key.keysym.sym == SDLK_n)
			{
				return NEW_GAME;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				right_arrow_event(mario_info, board);
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				left_arrow_event(mario_info, board);
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				upper_arrow_event(mario_info, board);
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				space_event(mario_info);

			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{	
				lower_arrow_event(mario_info, board);
			}
			break;
		case SDL_QUIT:
			return QUIT;
		};
	};
}
