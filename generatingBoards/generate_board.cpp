#include "generating_boards.h"
#include "../LevelsBoards/boards.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

int random_amount(int min, int max);

template <typename T>
T sum(T* ar, int size);

BoardElements generate_board()
{
	BoardElements board;
	int platforms_amount_for_each_level[ROWS];
	for (size_t i = 0; i < 5; i++)
		platforms_amount_for_each_level[i] = random_amount(1, 4);
	board.platforms_amount = sum(platforms_amount_for_each_level, ROWS);
	board.platform_height = 60;

	int counter = 0;

	for (size_t row = 0; row < ROWS; row++)
	{
		/*for (size_t i = 0; i < platforms_amount_for_each_level[row]; i++)
		{
			board.platforms_widths[counter] = SCREEN_WIDTH / platforms_amount_for_each_level[row] - 20;
			board.platforms_rows[counter] = row;
			counter++;
		}*/
	}

	return board;
}

int random_amount(int min, int max) 
{
	return min + rand() % (max - min + 1);
}

template <typename T>
T sum(T* ar, int size)
{
	T s = 0;
	for (size_t i = 0; i < size; i++)
		s += ar[i];
	return s;
}