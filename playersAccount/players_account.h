#pragma once

#include "../functions_definitions.h"

struct Player
{
	char name[20];
	int level_1_best_score;
	int level_2_best_score;
	int level_3_best_score;
	double level_1_best_time;
	double level_2_best_time;
	double level_3_best_time;
	int total_points;
};

Player* read_players_metrics(int&);
void players_account(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements);