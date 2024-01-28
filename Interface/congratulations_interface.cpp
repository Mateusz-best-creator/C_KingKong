#include "interface.h"

#include <string.h>

bool handle_congratulations_interface_events(SDL_Event&);

void congratulations_interface(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
	SDL_Event event;
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);
	SDL_FillRect(*(surfaces.screen), NULL, colors.czarny);

	char text[100];
	bool choosing_option = true;

	while (choosing_option)
	{
		DrawRectangle(*(surfaces.screen), 4, 4, SCREEN_WIDTH - 8, 54, colors.szary, colors.szary);
		sprintf_s(text, 128, "Congratulations, you have completed all 3 levels!");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 10, text, *(surfaces.charset));
		sprintf_s(text, 128, "Type anything to go to the initial_interface");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 26, text, *(surfaces.charset));

		SDL_UpdateTexture(SDL_elements.scrtex, NULL, (*(surfaces.screen))->pixels, (*(surfaces.screen))->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		// Fill the entire screen with given color
		SDL_FillRect((*(surfaces.screen)), NULL, colors.czarny);
		choosing_option = handle_congratulations_interface_events(event);
	}
}

bool handle_congratulations_interface_events(SDL_Event& event)
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			return false;
		case SDL_QUIT:
			return false;
		}
	}
	return true;
}