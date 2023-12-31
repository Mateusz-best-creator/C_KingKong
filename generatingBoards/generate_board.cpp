/*
#include "infinite_game.h"
#include "../LevelsBoards/boards.h"
#include "../functions_definitions.h"

#include <iostream>

int random_n(int min, int max);
int sum(int ar[], int size);

BoardElements generating_board()
{
	BoardElements board;
	// At the beginning let's initialize what we can
	board.level = 0;
	board.ladder_width = 20;
	board.platform_height = 60;
	board.display_get_trophy = true;
	board.display_put_trophy = false;

	int platforms_in_each_row[5];
	for (size_t i = 0; i < ROWS; i++)
	{
		platforms_in_each_row[i] = random_n(1, 4);
	}
	
	int platforms_sum = sum(platforms_in_each_row, ROWS);
	board.platforms_amount = platforms_sum;

	board.platforms_x_coordinate = new int[platforms_sum];
	board.platforms_y_coordinate = new int[platforms_sum];
	board.platforms_ending_x_coordinate = new int[platforms_sum];
	board.platforms_widths = new int[platforms_sum];
	board.platforms_rows = new int[platforms_sum];

	std::cout << platforms_sum << std::endl;
	int counter = 0;

	for (size_t row = 0; row < ROWS; row++)
	{
		for (size_t i = 0; i < platforms_in_each_row[row]; i++)
		{
			try
			{
				if (counter >= platforms_sum)
					throw counter;
				board.platforms_x_coordinate[counter] = SCREEN_WIDTH / platforms_in_each_row[row] * i;
				board.platforms_y_coordinate[counter] = 390 - row * 60;
				board.platforms_ending_x_coordinate[counter] = SCREEN_WIDTH / platforms_in_each_row[row] * i + SCREEN_WIDTH / platforms_in_each_row[row] - 20;
				board.platforms_widths[counter] = SCREEN_WIDTH / platforms_in_each_row[row] - 20;
				counter++;
			}
			catch (const int& er)
			{
				std::cout << "Counter is greater than amount of platforms: " << er << std::endl;
				exit(0);
			}
		}
	}

	// Let's now generate mario initial coordinates
	int initial_row = random_n(1, 3);
	if (initial_row == 1)
		board.initial_mario_y = 387;
	else if (initial_row == 2)
		board.initial_mario_y = 327;
	else
		board.initial_mario_y = 267;
	board.initial_mario_x = 10;

	// Initialize kingKong coords
	board.king_kong_x = 10;
	board.king_kong_y = 70;

	// Initialize ladders
	int ladders_sum = platforms_sum;
	board.amount_of_ladders = ladders_sum;
	board.ladders_x_coordinates = new int[ladders_sum];
	board.ladders_y_coordinates = new int[ladders_sum];
	board.ladders_rows = new int[ladders_sum];

	

	return board;
}
/*
struct BoardElements
{
	int level;
	int platforms_amount;
	int platform_height;
	int* platforms_y_coordinate, * platforms_x_coordinate, * platforms_ending_x_coordinate;
	int* platforms_widths;
	int* platforms_rows;
	int initial_mario_x, initial_mario_y;
	int king_kong_x, king_kong_y;
	int amount_of_ladders;
	int* ladders_x_coordinates, * ladders_y_coordinates;
	int* ladders_rows;
	int ladder_width;
	int winning_x1_coordinate, winning_x2_coordinate, winning_y_coordinate;
	int amount_of_coins;
	int* coins_x, * coins_y;
	bool* grabbed_coins;
	int barells_amount;
	int* barells_left_border, * barells_right_border, * barells_y_coordinate;
	int* barells_rows, * barells_direction;
	int get_trophy_x, get_trophy_y, put_trophy_x, put_trophy_y;
	bool display_get_trophy, display_put_trophy;
};

int sum(int ar[], int size)
{
	int s = 0;
	for (size_t i = 0; i < size; i++)
		s += ar[i];
	return s;
}

int random_n(int min, int max)
{
	return min + rand() % (max - min + 1);
}
*/