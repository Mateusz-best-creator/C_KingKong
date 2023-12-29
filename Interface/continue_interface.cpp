#include "interface.h"
#include "../functions_definitions.h"
#include "../Mario/mario.h"

#include <string.h>

bool handle_continue_interface_events(SDL_Event&, int&);

bool continue_interface(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, Mario& mario_info, BoardElements& board)
{
	SDL_Event event;
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);
	SDL_FillRect(*(surfaces.screen), NULL, colors.czarny);

	int option = 1;
	char text[100];
	bool choosing_option = true;

	while (choosing_option)
	{
		DrawRectangle(*(surfaces.screen), 4, 4, SCREEN_WIDTH - 8, 54, colors.szary, colors.szary);
		sprintf(text, "Mario points for level %d : %d Mario lifes: %d", board.level, mario_info.points, mario_info.lifes);
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 10, text, *(surfaces.charset));
		sprintf(text, "C: Continue the game");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 26, text, *(surfaces.charset));
		sprintf(text, "B: Stop the game");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 42, text, *(surfaces.charset));
		
		SDL_UpdateTexture(SDL_elements.scrtex, NULL, (*(surfaces.screen))->pixels, (*(surfaces.screen))->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		// Fill the entire screen with given color
		SDL_FillRect((*(surfaces.screen)), NULL, colors.czarny);
		choosing_option = handle_continue_interface_events(event, option);
	}

	if (option == 1)
		return true;
	return false;
}

bool handle_continue_interface_events(SDL_Event& event, int& x)
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_c)
			{
				x = 1;
				return false;
			}
			else if (event.key.keysym.sym == SDLK_b)
			{
				x = 0;
				return false;
			}
			else
				return true;
		case SDL_QUIT:
			return false;
		}
	}
	return true;
}