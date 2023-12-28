#include "mario.h"
#include <stdio.h>

void save_game( const Mario& mario_info)
{
	FILE* file;
	if (fopen_s(&file, "./game_results.txt", "w") != 0) {
		printf("Error opening the file.\n");
		exit(0);
	}
	fprintf(file, "Player name: %s\n", mario_info.name);
	save_data(file, mario_info, mario_info.level_1_scores, mario_info.level_2_scores, mario_info.level_3_scores,
		mario_info.level_1_best_score, mario_info.level_2_best_score, mario_info.level_3_best_score, "scores", "score");
	fprintf(file, "\n================================\n\n");
	save_data(file, mario_info, mario_info.level_1_times, mario_info.level_2_times, mario_info.level_3_times,
		mario_info.level_1_best_time, mario_info.level_2_best_time, mario_info.level_3_best_time, "times", "time");
	fprintf(file, "\n================================\n\n");

	fclose(file);
}

void save_data(FILE* file, const Mario& mario_info, const int* level_1_results, const int* level_2_results,
	const int* level_3_results, const int best_1, const int best_2, const int best_3, const char* s1, const char* s2)
{
	for (int i = 0; i < 3; i++)
	{
		fprintf(file, "Level %d %s: ", i + 1, s1);

		int j;
		if (i == 0)
			for (j = 0; j < mario_info.level_1_index; j++)
				fprintf(file, "%d ", level_1_results[j]);
		else if (i == 1)
			for (j = 0; j < mario_info.level_2_index; j++)
				fprintf(file, "%d ", level_2_results[j]);
		else
			for (j = 0; j < mario_info.level_3_index; j++)
				fprintf(file, "%d ", level_3_results[j]);

		fprintf(file, "\nLevel %d best %s: ", i + 1, s2);
		if (i == 0)
			fprintf(file, "%d\n", best_1);
		else if (i == 1)
			fprintf(file, "%d\n", best_2);
		else
			fprintf(file, "%d\n", best_3);
	}
}

void save_data(FILE* file, const Mario& mario_info, const double* level_1_results, const double* level_2_results,
	const double* level_3_results, const double best_1, const double best_2, const double best_3, const char* s1, const char* s2)
{
	for (int i = 0; i < 3; i++)
	{
		fprintf(file, "Level %d %s: ", i + 1, s1);

		int j;
		if (i == 0)
			for (j = 0; j < mario_info.level_1_index; j++)
				fprintf(file, "%g ", level_1_results[j]);
		else if (i == 1)
			for (j = 0; j < mario_info.level_2_index; j++)
				fprintf(file, "%g ", level_2_results[j]);
		else
			for (j = 0; j < mario_info.level_3_index; j++)
				fprintf(file, "%g ", level_3_results[j]);

		fprintf(file, "\nLevel %d best %s: ", i + 1, s2);
		if (i == 0)
			fprintf(file, "%g\n", best_1);
		else if (i == 1)
			fprintf(file, "%g\n", best_2);
		else
			fprintf(file, "%g\n", best_3);
	}
}