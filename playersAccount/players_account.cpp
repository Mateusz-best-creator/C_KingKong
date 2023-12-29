#include "players_account.h"
#include "../functions_definitions.h"
#include <iostream>

bool handle_players_interface_events(SDL_Event&);

void players_account(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
	int num_players = 0;
	Player* players = read_players_metrics(num_players);
	
	SDL_Event event;
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);
	SDL_FillRect(*(surfaces.screen), NULL, colors.czarny);

	char text[200];
	bool checking = true;

	while (checking)
	{
		if (num_players == 0)
		{
			DrawRectangle(*(surfaces.screen), 4, 200, SCREEN_WIDTH - 8, 75, colors.szary, colors.szary);
			sprintf(text, "Player list is empty");
			DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 230, text, *(surfaces.charset));
		}
		else
		{
			for (size_t i = 0; i < num_players; i++)
			{
				DrawRectangle(*(surfaces.screen), 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, colors.szary, colors.szary);
				sprintf(text, "%s", players[i].name);
				DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 15 + i * 90, text, *(surfaces.charset));
				sprintf(text, "Level 1: best score: %d best time: %g", players[i].level_1_best_score, players[i].level_1_best_time);
				DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 35 + i * 90, text, *(surfaces.charset));
				sprintf(text, "Level 2: best score: %d best time %g", players[i].level_2_best_score, players[i].level_2_best_time);
				DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 50 + i * 90, text, *(surfaces.charset));
				sprintf(text, "Level 3: best score: %d best time: %g Total points: %d",
					players[i].level_3_best_score, players[i].level_3_best_time, players[i].total_points);
				DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 65 + i * 90, text, *(surfaces.charset));
			}
		}

		SDL_UpdateTexture(SDL_elements.scrtex, NULL, (*(surfaces.screen))->pixels, (*(surfaces.screen))->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		// Fill the entire screen with given color
		SDL_FillRect((*(surfaces.screen)), NULL, colors.czarny);
		checking = handle_players_interface_events(event);
	}

	delete[] players;
}

bool handle_players_interface_events(SDL_Event& event)
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