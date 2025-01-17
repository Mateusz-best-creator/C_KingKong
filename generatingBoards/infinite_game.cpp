#include "../Mario/mario.h"
#include "../LevelsBoards/boards.h"
#include "../functions_definitions.h"
#include "infinite_game.h"

#include <string.h>

bool generate_board_interface(SDL_Event& event);

void infinite_game(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
	BoardElements board = generating_board();

	while (start_infinite_game(mario_info, surfaces, SDL_elements, board))
		board = generating_board();
	
	SDL_Event event;
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);
	SDL_FillRect(*(surfaces.screen), NULL, colors.czarny);

	char text[60];
	bool checking = true;

	while (checking)
	{
		DrawRectangle(*(surfaces.screen), 4, 200, SCREEN_WIDTH - 8, 75, colors.szary, colors.szary);
		sprintf_s(text, 60, "All points: %d", mario_info.all_points);
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 222, text, *(surfaces.charset));
		sprintf_s(text, 60, "Thanks for your time");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 243, text, *(surfaces.charset));
		SDL_UpdateTexture(SDL_elements.scrtex, NULL, (*(surfaces.screen))->pixels, (*(surfaces.screen))->pitch);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		// Fill the entire screen with given color
		SDL_FillRect((*(surfaces.screen)), NULL, colors.czarny);
		checking = generate_board_interface(event);
	}
	releaseMemory(board);
}

bool generate_board_interface(SDL_Event & event)
{
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) {
		case SDL_KEYDOWN:
			return false;
		case SDL_QUIT:
			return false;
		}
	}
	return true;
}