#pragma once

#include "../Mario/mario.h"
#include "../LevelsBoards/boards.h"

void load_table_from_file(Mario&, BoardElements&);
void save_game(const Mario& mario_info);
void save_all_games(const Mario& mario_info);
void save_data(FILE* file, const Mario& mario_info, const int* level_1_results, const int* level_2_results,
	const int* level_3_results, const int best_1, const int best_2, const int best_3, const char* s1, const char* s2);
void save_data(FILE* file, const Mario& mario_info, const double* level_1_results, const double* level_2_results,
	const double* level_3_results, const double best_1, const double best_2, const double best_3, const char* s1, const char* s2);