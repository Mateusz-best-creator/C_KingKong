#include "mario.h"
#include "../functions_definitions.h"
#include "../Barells/barells.h"
#include "../LevelsBoards/boards.h"
#include "../Interface/interface.h"
#include "../read_write_to_file/read_write_to_file.h"

#include <iostream>

int return_max(const int[], int);
double return_min(const double[], int);
void update_mario_after_collision(Mario& mario_info, BoardElements& board, TimeVariables& times);

enum CollisionResults { STOP_THE_GAME = 0, CONTINUE_GAME = 1 };

int collision_with_barell(Mario& mario_info, Barell* barells, FallingBarell& flying_barell,
	BoardElements& board, SDL_Surfaces& surfaces, SDL_Elements& elements, TimeVariables& times)
{
	bool touched_flying_barell = false;
	if (((mario_info.x_coordinate >= flying_barell.x_coordinate
		&& mario_info.x_coordinate <= flying_barell.x_coordinate + FLYING_BARELL_WIDTH) 
		|| mario_info.x_coordinate + MARIO_WIDTH > flying_barell.x_coordinate && mario_info.x_coordinate <= flying_barell.x_coordinate)
		&& mario_info.y_coordinate - MARIO_HEIGHT - MARIO_Y_OFFSET <= flying_barell.y_coordinate - FLYING_BARELL_HEIGHT 
		&& mario_info.y_coordinate >= flying_barell.y_coordinate
		&& flying_barell.falling_down)
	{
		touched_flying_barell = true;
	}

	for (size_t i = 0; i < board.barells_amount; i++)
	{
		if ((mario_info.mario_row != barells[i].row || mario_info.going_through_the_ladder) && !touched_flying_barell)
			continue;
		if ((((mario_info.x_coordinate <= barells[i].x_coordinate + BARELL_WIDTH &&
			mario_info.x_coordinate >= barells[i].x_coordinate) ||
			(mario_info.x_coordinate - MARIO_X_OFFSET + MARIO_WIDTH >= barells[i].x_coordinate &&
				mario_info.x_coordinate - MARIO_X_OFFSET + MARIO_WIDTH <= barells[i].x_coordinate + BARELL_WIDTH)) && 
			!mario_info.jumping) || touched_flying_barell)
		{
			update_mario_after_collision(mario_info, board, times);
			times.worldTime = 0;
			flying_barell.delta = 0;
			flying_barell.falling_down = false;
			flying_barell.y_coordinate = INITIAL_FALLING_BARELL_Y;

			bool safe = false;
			// Update lifes
			mario_info.lifes--;
			if (mario_info.lifes <= 0)
			{
				safe = save_after_lost_interface(surfaces, elements, mario_info, board);
				if (safe)
				{
					mario_info.all_points = mario_info.level_1_best_score + mario_info.level_2_best_score + mario_info.level_3_best_score;
					save_game("player_metrics.txt", mario_info);
					save_all_games(mario_info);
				}
				return STOP_THE_GAME;
			}
			bool play_again = continue_interface(surfaces, elements, mario_info, board);
			if (!play_again)
			{
				return STOP_THE_GAME;
			}
			else
			{
				return CONTINUE_GAME;
			}
		}
	}
}

void update_mario_metrics(Mario& mario_info, TimeVariables& times, int level)
{
	int level_1_index = mario_info.level_1_index;
	int level_2_index = mario_info.level_2_index;
	int level_3_index = mario_info.level_3_index;
	// Update all mario game results variables
	switch (level)
	{
	case 1:
		mario_info.level_1_scores[level_1_index] = mario_info.points;
		mario_info.level_1_best_score = return_max(mario_info.level_1_scores, level_1_index);
		mario_info.level_1_times[level_1_index] = times.worldTime;
		mario_info.level_1_best_time = return_min(mario_info.level_1_times, level_1_index);
		mario_info.level_1_index++;
		break;
	case 2:
		mario_info.level_2_scores[level_2_index] = mario_info.points;
		mario_info.level_2_best_score = return_max(mario_info.level_2_scores, level_2_index);
		mario_info.level_2_times[level_2_index] = times.worldTime;
		mario_info.level_2_best_time = return_min(mario_info.level_2_times, level_2_index);
		mario_info.level_2_index++;
		break;
	case 3:
		mario_info.level_3_scores[level_3_index] = mario_info.points;
		mario_info.level_3_best_score = return_max(mario_info.level_3_scores, level_3_index);
		mario_info.level_3_times[level_3_index] = times.worldTime;
		mario_info.level_3_best_time = return_min(mario_info.level_3_times, level_3_index);
		mario_info.level_3_index++;
		break;
	}
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

void update_mario_after_collision(Mario& mario_info, BoardElements& board, TimeVariables& times)
{
	update_mario_metrics(mario_info, times, board.level);
	mario_info.all_points -= mario_info.points;
	mario_info.points = 0;
	for (size_t i = 0; i < board.amount_of_coins; i++)
		board.grabbed_coins[i] = false;
}