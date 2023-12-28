#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"
#include <iostream>
#include <cstdlib>


int handleEvents(SDL_Event& event, Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, BoardElements& board)
{
	// Variable stores information in which row mario currently is
	int mario_row = 1;
	get_mario_info(mario_info, board, mario_row);
	mario_info.mario_row = mario_row;

	if (mario_info.jumping)
	{
		return 0;
	}
	// handling of events (if there were any)
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
			else if (event.key.keysym.sym == SDLK_n)
			{
				return 2;
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
				std::cout << mario_info.x_coordinate << " " << mario_info.y_coordinate << std::endl;
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
			return 1;
		};
	};
}
