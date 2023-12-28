#include "mario.h"
#include "../functions_definitions.h"
#include "../Barells/barells.h"
#include "../LevelsBoards/boards.h"
#include "../Interface/interface.h"
#include "../read_write_to_file/read_write_to_file.h"
#include <iostream>

static int level_1_index = 0;
static int level_2_index = 0;
static int level_3_index = 0;

int return_max(const int[], int);
double return_min(const double[], int);

void collision_with_barell(Mario& mario_info, Barell* barells, 
	BoardElements& board, SDL_Surfaces& surfaces, SDL_Elements& elements, TimeVariables& times)
{
	for (size_t i = 0; i < board.barells_amount; i++)
	{
		if (mario_info.mario_row != barells[i].row || mario_info.going_through_the_ladder)
			continue;
		if (((mario_info.x_coordinate <= barells[i].x_coordinate + 20 &&
			mario_info.x_coordinate >= barells[i].x_coordinate) ||
			(mario_info.x_coordinate - 14 + 30 >= barells[i].x_coordinate &&
			mario_info.x_coordinate - 14 + 30 <= barells[i].x_coordinate + 25)) && !mario_info.jumping)
		{
			update_mario_metrics(mario_info, times, board.level);
			mario_info.all_points -= mario_info.points;
			mario_info.points = 0;
			for (size_t i = 0; i < board.amount_of_coins; i++)
				board.grabbed_coins[i] = false;
			
			bool safe = false;
			// Update lifes
			mario_info.lifes--;
			if (mario_info.lifes <= 0)
			{
				safe = save_after_lost_interface(surfaces, elements, mario_info, board);
				if (safe)
				{
					save_game(mario_info);
				}
				game(surfaces, elements, true);
				return;
			}
			bool play_again = continue_interface(surfaces, elements, mario_info, board);
			if (!play_again)
			{
				game(surfaces, elements, true);
				return;
			}
			else
			{
				start_game(mario_info, surfaces, elements, board, true, 0, false, false);
				return;
			}
		}
	}
}

void update_mario_metrics(Mario& mario_info, TimeVariables& times, int level)
{
	// Update all mario game results variables
	switch (level)
	{
	case 1:
		mario_info.level_1_scores[level_1_index] = mario_info.points;
		mario_info.level_1_best_score = return_max(mario_info.level_1_scores, level_1_index);
		mario_info.level_1_times[level_1_index] = times.worldTime;
		mario_info.level_1_best_time = return_min(mario_info.level_1_times, level_1_index);
		level_1_index++;
		break;
	case 2:
		mario_info.level_2_scores[level_2_index] = mario_info.points;
		mario_info.level_2_best_score = return_max(mario_info.level_2_scores, level_2_index);
		mario_info.level_2_times[level_2_index] = times.worldTime;
		mario_info.level_2_best_time = return_min(mario_info.level_2_times, level_2_index);
		level_2_index++;
		break;
	case 3:
		mario_info.level_3_scores[level_3_index] = mario_info.points;
		mario_info.level_3_best_score = return_max(mario_info.level_3_scores, level_3_index);
		mario_info.level_3_times[level_3_index] = times.worldTime;
		mario_info.level_3_best_time = return_min(mario_info.level_3_times, level_3_index);
		level_3_index++;
		break;
	}
	mario_info.level_1_index = level_1_index;
	mario_info.level_2_index = level_2_index;
	mario_info.level_3_index = level_3_index;
}

int return_max(const int array[], int size)
{
	int max = array[0];
	for (size_t i = 1; i <= size; i++)
		if (max < array[i])
			max = array[i];
	return max;
}

double return_min(const double array[], int size)
{
	double min = array[0];
	for (size_t i = 1; i <= size; i++)
		if (min > array[i])
			min = array[i];
	return min;
}