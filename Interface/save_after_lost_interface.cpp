#include "interface.h"
#include <stdio.h>
#include <iostream>

bool handle_after_lost_interface_events(SDL_Event&, int&);
void save_game(const BoardElements& board, const Mario& mario_info);
void save_data(FILE*, const Mario&, const int*, const int*, const int*, const int, const int, const int, const char*, const char*);

void save_after_lost_interface(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, Mario& mario_info, BoardElements& board)
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
		sprintf(text, "Do you want to save your results to the file\u24B6");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 10, text, *(surfaces.charset));
		sprintf(text, "Y: Yes");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 26, text, *(surfaces.charset));
		sprintf(text, "N: No");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 42, text, *(surfaces.charset));

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
		save_game(board, mario_info);
	}
	game(surfaces, SDL_elements, true);
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

void save_game(const BoardElements& board, const Mario& mario_info)
{
	FILE* file;
	if (fopen_s(&file, "./game_results.txt", "w") != 0) {
		printf("Error opening the file.\n");
		exit(0);
	}

	save_data(file, mario_info, mario_info.level_1_scores, mario_info.level_2_scores, mario_info.level_3_scores,
		mario_info.level_1_best_score, mario_info.level_2_best_score, mario_info.level_3_best_score, "scores", "score");
	save_data(file, mario_info, mario_info.level_1_times, mario_info.level_2_times, mario_info.level_3_times,
		mario_info.level_1_best_time, mario_info.level_2_best_time, mario_info.level_3_best_time, "times", "time");

	fclose(file);
}

void save_data(FILE* file, const Mario& mario_info, const int* level_1_results, const int* level_2_results, 
	const int* level_3_results, const int best_1, const int best_2, const int best_3, const char* s1, const char* s2)
{
	for (int i = 0; i < 3; i++)
	{
		fprintf(file, "Level %d %s: ", i+1, s1);
		for (int j = 0; j < mario_info.index; j++)
			switch (i)
			{
			case 0:
				fprintf(file, "%d ", level_1_results[j]);
				break;
			case 1:
				fprintf(file, "%d ", level_2_results[j]);
				break;
			case 2:
				fprintf(file, "%d ", level_3_results[j]);
				break;
			}
		fprintf(file, "\nLevel %d best %s: ", i+1, s2);
		if (i == 0)
			fprintf(file, "%d\n", best_1);
		else if (i == 1)
			fprintf(file, "%d\n", best_2);
		else
			fprintf(file, "%d\n", best_3);
	}
}