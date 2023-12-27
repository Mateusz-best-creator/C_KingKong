#include "interface.h"
#include "../functions_definitions.h"
#include <iostream>

bool continue_interface(SDL_Surfaces& surfaces)
{
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);
	int option = 1;
	char text[100];
	bool choosing_option = true;
	int c = 0;

	while (choosing_option)
	{
		DrawRectangle(*(surfaces.screen), 4, 4, SCREEN_WIDTH - 8, 36, colors.szary, colors.szary);
		sprintf(text, "Continue the game");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 10, text, *(surfaces.charset));
		sprintf(text, "Stop the game");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 26, text, *(surfaces.charset));
		c++;
		if (c == 1000)
			choosing_option = false;
	}

	if (option == 1)
		return true;
	return false;
}
