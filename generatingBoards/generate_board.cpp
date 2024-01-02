#include "infinite_game.h"
#include "../LevelsBoards/boards.h"
#include "../functions_definitions.h"

#include <iostream>
#include <cstdlib>
#include <ctime>    

int sum(int ar[], int size);

BoardElements generating_board()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	BoardElements board;
	// At the beginning let's initialize what we can
	board.level = 0;
	board.ladder_width = 20;
	board.platform_height = 60;

	int platforms_in_each_row[5];
	for (size_t i = 0; i < ROWS; i++)
	{
		platforms_in_each_row[i] = std::rand() % 4 + 1;
	}
	
	int platforms_sum = sum(platforms_in_each_row, ROWS);
	board.platforms_amount = platforms_sum;

	board.platforms_x_coordinate = new int[platforms_sum];
	board.platforms_y_coordinate = new int[platforms_sum];
	board.platforms_ending_x_coordinate = new int[platforms_sum];
	board.platforms_widths = new int[platforms_sum];
	board.platforms_rows = new int[platforms_sum];

	std::cout << platforms_sum << std::endl;
	for (int i = 0; i < ROWS; i++)
		std::cout << "Platforms for row " << i + 1 << ": " << platforms_in_each_row[i] << std::endl;
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
				board.platforms_widths[counter] = SCREEN_WIDTH / platforms_in_each_row[row] - 20;
				board.platforms_ending_x_coordinate[counter] = board.platforms_x_coordinate[counter] + board.platforms_widths[counter];
				board.platforms_rows[counter] = row + 1;
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
	int initial_row = std::rand() % 3 + 1;
	if (initial_row == 1)
		board.initial_mario_y = 387;
	else if (initial_row == 2)
		board.initial_mario_y = 327;
	else
		board.initial_mario_y = 267;
	board.initial_mario_x = 100;

	// Initialize kingKong coords
	board.king_kong_x = 50;
	board.king_kong_y = 100;

	// Initialize ladders
	int ladders_sum = platforms_sum;
	board.ladder_width = 20;
	board.amount_of_ladders = ladders_sum;
	board.ladders_x_coordinates = new int[ladders_sum];
	board.ladders_y_coordinates = new int[ladders_sum];
	board.ladders_rows = new int[ladders_sum];

	int ladder_place = 1;

	for (size_t i = 0; i < ladders_sum; i++)
	{
		board.ladders_rows[i] = board.platforms_rows[i];
		ladder_place = std::rand() % 3 + 1;
		if (ladder_place == 1)
		{
			board.ladders_x_coordinates[i] = board.platforms_x_coordinate[i] + 20;
		}
		else if (ladder_place == 2)
		{
			board.ladders_x_coordinates[i] = board.platforms_x_coordinate[i] + (board.platforms_widths[i] / 2);
		}
		else
		{
			board.ladders_x_coordinates[i] = board.platforms_ending_x_coordinate[i] - 20 - board.ladder_width;
		}
		board.ladders_y_coordinates[i] = 351 - (board.platform_height * (board.platforms_rows[i] - 1));
	}

	// Set winning coordinates (static for now)
	board.winning_x1_coordinate = 100;
	board.winning_x2_coordinate = 130;
	board.winning_y_coordinate = 210;

	// Set amount of coins (from 4 to 8)
	int coins_sum = std::rand() % 8 + 4;
	board.amount_of_coins = coins_sum;

	board.coins_x = new int[coins_sum];
	board.coins_y = new int[coins_sum];
	board.grabbed_coins = new bool[coins_sum];


	for (size_t i = 0; i < board.amount_of_coins; i++)
	{
		board.grabbed_coins[i] = false;
		board.coins_x[i] = 100;
		board.coins_y[i] = 200;
		/*
		board.coins_x[i] = board.platforms_x_coordinate[i] + 10;
		board.coins_y[i] = 387 - (board.platforms_rows[i] - 1) * 60;
		*/
	}

	// Initialize barells
	int barells_sum = 1;
	board.barells_amount = barells_sum;
	board.barells_left_border = new int[barells_sum];
	board.barells_right_border = new int[barells_sum];
	board.barells_y_coordinate = new int[barells_sum];
	board.barells_rows = new int[barells_sum];
	board.barells_direction = new int[barells_sum];
	
	board.barells_left_border[0] = 10;
	board.barells_right_border[0] = 500;
	board.barells_y_coordinate[0] = 210;
	board.barells_rows[0] = 4;
	board.barells_direction[0] = 1;

	// Trophy
	board.get_trophy_x = 300;
	board.get_trophy_y = 390;
	board.put_trophy_x = 600;
	board.put_trophy_y = 390;
	board.display_get_trophy = true;
	board.display_put_trophy = false;

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
*/
int sum(int ar[], int size)
{
	int s = 0;
	for (size_t i = 0; i < size; i++)
		s += ar[i];
	return s;
}