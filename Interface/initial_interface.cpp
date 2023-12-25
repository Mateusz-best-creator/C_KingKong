#include "../functions_definitions.h"
#include "interface.h"
#include <string.h>
#include <iostream>

bool handle_initial_interface_events(SDL_Event&, int& level);
void level_rectangle(SDL_Surface*, const int, const Colors&);

int initial_interface(const SDL_Surfaces& surfaces, const SDL_Elements& SDL_elements, const Colors& colors)
{
    SDL_Event event;
	SDL_Surface* screen = *(surfaces.screen);
	SDL_Surface* charset = *(surfaces.charset);

	char desc_text[150];

	bool choosing_level = true;
	int option = 1;

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

		choosing_level = handle_initial_interface_events(event, option);
		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, colors.czarny);

		// Draw rectangle pointing to appropriate level
		level_rectangle(screen, option, colors);
		
		SDL_Surface* level_logos[3] = { *(surfaces.level_1_crown) , *(surfaces.level_2_treasure) , *(surfaces.level_3_diamond) };
		char* level_desc[3] = { "Level 1", "Level 2", "Level 3" };
		// Print icons for each level, print levels informations
		for (size_t i = 0; i < AMOUNT_OF_LEVELS; i++)
		{
			sprintf(desc_text, level_desc[i]);
			DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, INITIAL_STRING_Y + i * OFFSET, desc_text, charset);
			DrawSurface(screen, level_logos[i], SCREEN_WIDTH / 2, INITIAL_SURFACE_Y + i * OFFSET);
		}
	}
    return option;
}

bool handle_initial_interface_events(SDL_Event& event, int& level)
{
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN)
                return false;
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if (level < AMOUNT_OF_LEVELS)
					level++;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				// We do not have level 0
				if (level > 1)
					level--;
			}
            break;  

        case SDL_QUIT:
            return false;
        }
    }
    return true;
}

void level_rectangle(SDL_Surface* screen, const int level, const Colors& colors)
{
	switch (level)
	{
	case 1:
		DrawRectangle(screen, RECTANGLES_X, RECTANGLE_1_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
		break;
	case 2:
		DrawRectangle(screen, RECTANGLES_X, RECTANGLE_2_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
		break;
	case 3:
		DrawRectangle(screen, RECTANGLES_X, RECTANGLE_3_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT, colors.jasny_niebieski, colors.czarny);
		break;
	default:
		break;
	}
}