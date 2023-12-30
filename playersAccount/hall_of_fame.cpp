#include "players_account.h"
#include "../functions_definitions.h"

#include <string.h>
#include <stdio.h>
#include <iostream>

bool hall_of_fame_interface_events(SDL_Event&);
int partition(Player arr[], int low, int high);
void quickSort(Player arr[], int low, int high);

void hall_of_fame(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
	int num_players = 0;
	std::cout << "calling read players metrics..." << std::endl;
	Player* players = read_players_metrics(num_players);
	quickSort(players, 0, num_players - 1);

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
		{
			for (size_t i = 0; i < num_players; i++)
			{
				if (i == 0)
				{
					sprintf(text, "Champion: %s", players[i].name);
					DrawRectangle(*(surfaces.screen), 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, colors.szary, colors.zloty);
				}
				else if (i == 1)
					DrawRectangle(*(surfaces.screen), 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, colors.szary, colors.srebrny);
				else if (i == 2)
					DrawRectangle(*(surfaces.screen), 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, colors.szary, colors.miedziany);
				else
					DrawRectangle(*(surfaces.screen), 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, colors.szary, colors.szary);
				if (i != 0) sprintf(text, "%s", players[i].name);
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
		checking = hall_of_fame_interface_events(event);
	}

	delete[] players;
}

bool hall_of_fame_interface_events(SDL_Event& event)
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

void swap(Player& a, Player& b) {
	Player temp = a;
	a = b;
	b = temp;
}

int partition(Player arr[], int low, int high)
{
	Player pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; ++j) {
		if (arr[j].total_points >= pivot.total_points) {
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(Player arr[], int low, int high)
{
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}