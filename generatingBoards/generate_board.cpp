#include "infinite_game.h"
#include "../LevelsBoards/boards.h"
#include "../functions_definitions.h"

#include <cstdlib>
#include <ctime>    

int sum(int ar[], int size);
/*
	Generate x beginning, x end, y coordinate and width for each platform.
	Also chooses random amount of platforms for each row in the game.
*/
int generate_platforms(BoardElements&, int*);
/*
	Generates initial coordinates for Mario and KingKong.
*/
void initialize_mario_monkey(BoardElements& board);
/*
	Generate ladders x, y coordinates.
*/
void generate_ladders(BoardElements&, const int, int*);
void generate_coins(BoardElements&);
void generate_barells(BoardElements&);
void generate_treasure(BoardElements&);
void generate_trophy(BoardElements&);
bool is_in(int*, int, int);


BoardElements generating_board()
{
	// Set random seed
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	BoardElements board;
	// At the beginning let's initialize what we can
	board.level = 0;
	board.ladder_width = 20;
	board.platform_height = 60;

	int platforms_in_each_row[5];
	int platforms_sum = generate_platforms(board, platforms_in_each_row);

	initialize_mario_monkey(board);
	generate_ladders(board, platforms_sum, platforms_in_each_row);
	generate_treasure(board);
	generate_coins(board);
	generate_barells(board);
	generate_trophy(board);

	return board;
}

int sum(int ar[], int size)
{
	int s = 0;
	for (size_t i = 0; i < size; i++)
		s += ar[i];
	return s;
}

int generate_platforms(BoardElements& board, int* platforms_in_each_row)
{
	for (size_t i = 0; i < ROWS; i++)
	{
		platforms_in_each_row[i] = std::rand() % 4 + 1;
	}
	// Int the last row we always want 1 platform
	platforms_in_each_row[4] = 1;
	int platforms_sum = sum(platforms_in_each_row, ROWS);
	board.platforms_amount = platforms_sum;

	board.platforms_x_coordinate = new int[platforms_sum];
	board.platforms_y_coordinate = new int[platforms_sum];
	board.platforms_ending_x_coordinate = new int[platforms_sum];
	board.platforms_widths = new int[platforms_sum];
	board.platforms_rows = new int[platforms_sum];

	int counter = 0;

	for (size_t row = 0; row < ROWS; row++)
	{
		for (size_t i = 0; i < platforms_in_each_row[row]; i++)
		{
			board.platforms_x_coordinate[counter] = SCREEN_WIDTH / platforms_in_each_row[row] * i;
			board.platforms_y_coordinate[counter] = 390 - row * 60;
			board.platforms_widths[counter] = SCREEN_WIDTH / platforms_in_each_row[row] - 20;
			board.platforms_ending_x_coordinate[counter] = board.platforms_x_coordinate[counter] + board.platforms_widths[counter];
			board.platforms_rows[counter] = row + 1;
			counter++;
		}
	}

	return platforms_sum;
}

void initialize_mario_monkey(BoardElements& board)
{
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
	board.king_kong_x = SCREEN_WIDTH / 2;
	board.king_kong_y = 70;
}

void generate_ladders(BoardElements& board, const int platforms_sum, int* platforms_in_each_row)
{
	// Initialize ladders
	int ladders_sum = platforms_sum - platforms_in_each_row[4];
	board.ladder_width = 20;
	board.amount_of_ladders = ladders_sum;
	board.ladders_x_coordinates = new int[ladders_sum];
	board.ladders_y_coordinates = new int[ladders_sum];
	board.ladders_rows = new int[ladders_sum];

	int ladder_place = 1;
	int offset = 0;

	for (size_t i = 0; i < ladders_sum; i++)
	{
		offset = std::rand() % 30 + 15;
		board.ladders_rows[i] = board.platforms_rows[i];
		ladder_place = std::rand() % 3 + 1;
		if (ladder_place == 1)
		{
			board.ladders_x_coordinates[i] = board.platforms_x_coordinate[i] + offset;
		}
		else if (ladder_place == 2)
		{
			board.ladders_x_coordinates[i] = board.platforms_x_coordinate[i] + (board.platforms_widths[i] / 2) + offset;
		}
		else
		{
			board.ladders_x_coordinates[i] = board.platforms_ending_x_coordinate[i] - offset - board.ladder_width;
		}
		board.ladders_y_coordinates[i] = 351 - (board.platform_height * (board.platforms_rows[i] - 1));
	}
}

void generate_coins(BoardElements& board)
{
	// Set amount of coins (from 4 to 8)
	int coins_sum = std::rand() % 8 + 4;
	board.amount_of_coins = coins_sum;

	board.coins_x = new int[coins_sum];
	board.coins_y = new int[coins_sum];
	board.grabbed_coins = new bool[coins_sum];

	int option = 1;
	int offset;
	for (size_t i = 0; i < board.amount_of_coins; i++)
	{
		offset = std::rand() % 60 + 1;
		option = std::rand() % 2 + 1;
		board.grabbed_coins[i] = false;
		if (option == 1)
			board.coins_x[i] = board.platforms_x_coordinate[i] + offset + 20;
		else if (option == 2)
			board.coins_x[i] = board.platforms_ending_x_coordinate[i] - offset - 20;
		board.coins_y[i] = 387 - (board.platforms_rows[i] - 1) * 60;
	}
}

void generate_barells(BoardElements& board)
{
	// Initialize barells
	int barells_sum = 4;
	board.barells_amount = barells_sum;
	board.barells_left_border = new int[barells_sum];
	board.barells_right_border = new int[barells_sum];
	board.barells_y_coordinate = new int[barells_sum];
	board.barells_rows = new int[barells_sum];
	board.barells_direction = new int[barells_sum];

	int barell_platform_indexes[4] = { -1, -1, -1, -1 };
	int platform_index;
	for (size_t i = 0; i < barells_sum; i++)
	{
		platform_index = std::rand() % board.platforms_amount;
		while (is_in(barell_platform_indexes, 4, platform_index))
			platform_index = std::rand() % board.platforms_amount + 1;
		barell_platform_indexes[i] = platform_index;
		board.barells_left_border[i] = board.platforms_x_coordinate[platform_index] + 10;
		board.barells_right_border[i] = board.platforms_ending_x_coordinate[platform_index] - 10;
		board.barells_y_coordinate[i] = board.platforms_y_coordinate[platform_index];
		board.barells_rows[i] = board.platforms_rows[platform_index];
		i % 2 == 0 ? board.barells_direction[i] = 1 : board.barells_direction[i] = 0;
	}
}

void generate_treasure(BoardElements& board)
{
	int platform_index = std::rand() % board.platforms_amount + 1;
	int option = std::rand() % 2 + 1;
	// Set winning coordinates (static for now)
	if (option == 1)
		board.winning_x1_coordinate = board.platforms_x_coordinate[platform_index] + 30;
	else if (option == 2)
		board.winning_x1_coordinate = board.platforms_ending_x_coordinate[platform_index] - 100;
	board.winning_x2_coordinate = board.winning_x1_coordinate + 20;
	board.winning_y_coordinate = board.platforms_y_coordinate[platform_index];
}

void generate_trophy(BoardElements& board)
{
	int platform_index = std::rand() % board.platforms_amount;
	int option = std::rand() % 2 + 1;
	// Set winning coordinates (static for now)
	if (option == 1)
	{
		board.get_trophy_x = board.platforms_x_coordinate[platform_index] + 30;
		board.get_trophy_y = board.platforms_y_coordinate[platform_index];
	}
	else if (option == 2)
	{
		board.get_trophy_x = board.platforms_ending_x_coordinate[platform_index] - 100;
		board.get_trophy_y = board.platforms_y_coordinate[platform_index];
	}

	board.get_trophy_y = board.platforms_y_coordinate[platform_index];

	int platform_index2 = std::rand() % board.platforms_amount;
	if (platform_index2 == platform_index && platform_index > 0)
		platform_index2--;
	else if (platform_index2 == platform_index && platform_index == 0)
		platform_index2++;
	board.put_trophy_x = board.platforms_x_coordinate[platform_index2] + 30;
	board.put_trophy_y = board.platforms_y_coordinate[platform_index2] - MARIO_FLOOR_DISTANCE;

	board.display_get_trophy = true;
	board.display_put_trophy = false;
}

bool is_in(int* ar, int size, int number)
{
	for (size_t i = 0; i < size; i++)
	{
		if (ar[i] == number)
			return true;
	}
	return false;
}