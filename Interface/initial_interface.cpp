#include "../functions_definitions.h"
#include "interface.h"
#include <string.h>
#include <cstdlib>
#include <iostream>

bool handle_initial_interface_events(SDL_Event&, int& x, int& y);
void level_rectangle(SDL_Surface*, const int, const int, const Colors&);

void initial_interface(const SDL_Surfaces& surfaces, const SDL_Elements& SDL_elements, const Colors& colors, int& x, int& y)
{
    SDL_Event event;
	SDL_Surface* screen = *(surfaces.screen);
	SDL_Surface* charset = *(surfaces.charset);

	char desc_text[150];

	bool choosing_level = true;

	while (choosing_level)
	{
		// tekst informacyjny / info text
		DrawRectangle(screen, DESC_RECTANGLE_INIT_X_Y, DESC_RECTANGLE_INIT_X_Y, 
			DESC_RECTANGLE_WIDTH, DESC_RECTANGLE_HEIGHT, colors.czerwony, colors.niebieski);
		const char* desc[3] =
		{
			"Embark on a  thrilling retro adventure  with my C++-crafted DonkeyKong",
			"game. You'll dodge barrels, climb ladders, and find amazing treasures!",
			"Enter - pick a level, \030 - choose lower level, \031 - choose higher level"
		};
		const int lines_Y[3] = {DESC_LINE_1, DESC_LINE_2, DESC_LINE_3};
		for (size_t i = 0; i < 3; i++)
		{
			sprintf(desc_text, desc[i]);
			DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, lines_Y[i], desc_text, charset);
		}

		SDL_UpdateTexture(SDL_elements.scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		choosing_level = handle_initial_interface_events(event, x, y);
		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, colors.czarny);

		// Draw rectangle pointing to appropriate level
		level_rectangle(screen, x, y, colors);
		
		SDL_Surface* level_logos[9] =
		{
			*(surfaces.quit_icon), *(surfaces.level_1_crown), *(surfaces.authentication_icon),
			*(surfaces.saving_icon) , *(surfaces.level_2_treasure), *(surfaces.report_icon),
			* (surfaces.loading_icon) , *(surfaces.level_3_diamond), *(surfaces.golden_cup_icon)
		};
		char* options_desc[9] =
		{
			"Quit", "Level 1", "Authentication",
			"Save to file", "Level 2", "Results account",
			"Read from file", "Level 3", "Hall of fame"
		};
		char* level_desc[3] = { "Level 1", "Level 2", "Level 3" };
		// Print icons for each level, print levels informations
		int counter = 0;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				// Printing text
				sprintf(desc_text, options_desc[counter]);
				if (j == 0)
					DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2 - 200, INITIAL_STRING_Y + i * Y_OFFSET, desc_text, charset);
				else
					DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2 - 200 + j * 200, INITIAL_STRING_Y + i * Y_OFFSET, desc_text, charset);
				// Printing icons
				DrawSurface(screen, level_logos[counter], 120 + j * 200, INITIAL_SURFACE_Y + i * Y_OFFSET);
				counter++;
			}
		}
	}
}

bool handle_initial_interface_events(SDL_Event& event, int& x, int& y)
{
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
			else if (event.key.keysym.sym == SDLK_RETURN)
				return false;
			else if (event.key.keysym.sym == SDLK_DOWN && y < 3)
				y++;
			else if (event.key.keysym.sym == SDLK_UP && y > 1)
				y--;
			else if (event.key.keysym.sym == SDLK_LEFT && x > 1)
				x--;
			else if (event.key.keysym.sym == SDLK_RIGHT && x < 3)
				x++;
            break;  
        case SDL_QUIT:
            return false;
        }
    }
    return true;
}

/*
	Drawing blue rectangle on the appropriate place based on x and y values.
*/
void level_rectangle(SDL_Surface* screen, const int x, const int y, const Colors& colors)
{
	if (x == 1 && y == 1)
		DrawRectangle(screen, RECTANGLES_1_X, RECTANGLE_1_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 1 && y == 2)
		DrawRectangle(screen, RECTANGLES_1_X, RECTANGLE_2_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 1 && y == 3)
		DrawRectangle(screen, RECTANGLES_1_X, RECTANGLE_3_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 2 && y == 1)
		DrawRectangle(screen, RECTANGLES_2_X, RECTANGLE_1_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 2 && y == 2)
		DrawRectangle(screen, RECTANGLES_2_X, RECTANGLE_2_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 2 && y == 3)
		DrawRectangle(screen, RECTANGLES_2_X, RECTANGLE_3_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 3 && y == 1)
		DrawRectangle(screen, RECTANGLES_3_X, RECTANGLE_1_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 3 && y == 2)
		DrawRectangle(screen, RECTANGLES_3_X, RECTANGLE_2_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
	else if (x == 3 && y == 3)
		DrawRectangle(screen, RECTANGLES_3_X, RECTANGLE_3_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
}