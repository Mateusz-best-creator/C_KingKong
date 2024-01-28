#include "interface.h"

#include <string.h>
#include <stdio.h>

bool handle_after_lost_interface_events(SDL_Event&, int&);

bool save_after_lost_interface(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, Mario& mario_info, BoardElements& board)
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
		sprintf_s(text, 100, "Do you want to save your results to the file\u24B6");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - int(strlen(text)) * 8 / 2, 10, text, *(surfaces.charset));
		sprintf_s(text, 100, "Y: Yes");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - int(strlen(text)) * 8 / 2, 26, text, *(surfaces.charset));
		sprintf_s(text, 100, "N: No");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - int(strlen(text)) * 8 / 2, 42, text, *(surfaces.charset));

		SDL_UpdateTexture(SDL_elements.scrtex, NULL, (*(surfaces.screen))->pixels, (*(surfaces.screen))->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		// Fill the entire screen with given color
		SDL_FillRect((*(surfaces.screen)), NULL, colors.czarny);
		choosing_option = handle_after_lost_interface_events(event, option);
	}
	if (option == 1)
	{
		return true;
	}
	return false;
}

bool handle_after_lost_interface_events(SDL_Event& event, int& x)
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_y)
			{
				x = 1;
				return false;
			}
			else if (event.key.keysym.sym == SDLK_n)
			{
				x = 2;
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