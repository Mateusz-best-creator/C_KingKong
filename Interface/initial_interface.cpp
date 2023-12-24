#include "../functions_definitions.h"
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
	int level = 1;

	while (choosing_level)
	{
		// tekst informacyjny / info text
		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 60, colors.czerwony, colors.niebieski);
		sprintf(desc_text, "Embark on a  thrilling retro adventure  with my C++-crafted DonkeyKong");
		DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, 10, desc_text, charset);
		sprintf(desc_text, "game. You'll dodge barrels, climb ladders, and find amazing treasures!");
		DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, 28, desc_text, charset);
		sprintf(desc_text, "Enter - pick a level, \030 - choose lower level, \031 - choose higher level");
		DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, 45, desc_text, charset);

		SDL_UpdateTexture(SDL_elements.scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		choosing_level = handle_initial_interface_events(event, level);
		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, colors.czarny);

		// Draw rectangle pointing to appropriate level
		level_rectangle(screen, level, colors);

		// Print levels informations
		sprintf(desc_text, "Level 1");
		DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, 165, desc_text, charset);
		sprintf(desc_text, "Level 2");
		DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, 270, desc_text, charset);
		sprintf(desc_text, "Level 3");
		DrawString(screen, screen->w / 2 - strlen(desc_text) * 8 / 2, 400, desc_text, charset);

		// Print icons for each level
		DrawSurface(screen, *(surfaces.level_1_crown),
			SCREEN_WIDTH / 2, 120);
		DrawSurface(screen, *(surfaces.level_2_treasure),
			SCREEN_WIDTH / 2, 230);
		DrawSurface(screen, *(surfaces.level_3_diamond),
			SCREEN_WIDTH / 2, 360);
	}
    return 1;
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
				if (level < 3)
					level++;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
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
		DrawRectangle(screen, SCREEN_WIDTH / 2 - 75, 70, 150, 110, colors.jasny_niebieski, colors.czarny);
		break;
	case 2:
		DrawRectangle(screen, SCREEN_WIDTH / 2 - 75, 190, 150, 110, colors.jasny_niebieski, colors.czarny);
		break;
	case 3:
		DrawRectangle(screen, SCREEN_WIDTH / 2 - 75, 310, 150, 110, colors.jasny_niebieski, colors.czarny);
		break;
	default:
		break;
	}
}