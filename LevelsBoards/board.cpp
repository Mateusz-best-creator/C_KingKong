#include "boards.h"
#include "../functions_definitions.h"
#include <stdio.h>

BoardElements initialize_board(int level)
{
	switch (level)
	{
		case 1:
			return initialize_level_1_board();
		case 2:
			return initialize_level_2_board();
		case 3:
			return initialize_level_3_board();
		default:
			break;
	}
}

/*
	Initialize the entire board for level 1
*/
BoardElements initialize_level_1_board()
{
	BoardElements board;
	board.level = 1;

	// Coins coordinates for level 2
	board.coins_x = new int[LEVEL_1_COINS_AMOUNT];
	board.coins_y = new int[LEVEL_1_COINS_AMOUNT];
	board.grabbed_coins = new bool[LEVEL_1_COINS_AMOUNT];
	int coins_x[LEVEL_1_COINS_AMOUNT] = { 476, 308, 200, 344, 170 };
	int coins_y[LEVEL_1_COINS_AMOUNT] = { 387, 327, 267, 207, 147 };
	for (size_t i = 0; i < LEVEL_1_COINS_AMOUNT; i++)
	{
		board.coins_x[i] = coins_x[i];
		board.coins_y[i] = coins_y[i];
		board.grabbed_coins[i] = false;
	}

	board.platforms_amount = LEVEL_1_PLATFORMS_AMOUNT;
	board.platforms_x_coordinate = new int[LEVEL_1_PLATFORMS_AMOUNT];
	board.platforms_ending_x_coordinate = new int[LEVEL_1_PLATFORMS_AMOUNT];
	board.platforms_y_coordinate = new int[LEVEL_1_PLATFORMS_AMOUNT];
	board.platforms_widths = new int[LEVEL_1_PLATFORMS_AMOUNT];
	board.platforms_rows = new int[LEVEL_1_PLATFORMS_AMOUNT];

	// Initialize platforms width and beginning y coordinates
	for (size_t i = 0; i < LEVEL_1_PLATFORMS_AMOUNT; i++)
	{
		board.platforms_y_coordinate[i] = 390 - i * 60;
		board.platforms_widths[i] = SCREEN_WIDTH;
		board.platforms_x_coordinate[i] = 0;
		board.platforms_rows[i] = i + 1;
	}

	// Calculate ending x coordinates for each platform
	for (size_t i = 0; i < LEVEL_1_PLATFORMS_AMOUNT; i++)
		board.platforms_ending_x_coordinate[i] = board.platforms_x_coordinate[i] + board.platforms_widths[i];

	// Initialize all other data
	board.amount_of_ladders = LEVEL_1_AMOUNT_OF_LADDERS;
	board.ladders_x_coordinates = new int[LEVEL_1_AMOUNT_OF_LADDERS];
	board.ladders_y_coordinates = new int[LEVEL_1_AMOUNT_OF_LADDERS];
	board.ladders_rows = new int[LEVEL_1_AMOUNT_OF_LADDERS];
	board.ladder_width = 20;
	board.platform_height = 60;

	for (size_t i = 0; i < board.amount_of_ladders; i++)
	{
		board.ladders_y_coordinates[i] = 351 - board.platform_height * i;
		board.ladders_rows[i] = i + 1;
		// Ladder measurements
		if ((i + 1) % 2)
			board.ladders_x_coordinates[i] = 580;
		else
			board.ladders_x_coordinates[i] = 60;
	}
		
	// Initial coordinates
	board.initial_mario_x = LEVEL_1_MARIO_INITIAL_X;
	board.initial_mario_y = LEVEL_1_MARIO_INITIAL_Y;
	board.king_kong_x = LEVEL1_KING_KONG_X;
	board.king_kong_y = LEVEL1_KING_KONG_Y;

	// Initialize winning coordinates
	board.winning_x1_coordinate = LEVEL_1_WINNING_X1;
	board.winning_x2_coordinate = LEVEL_1_WINNING_X2;
	board.winning_y_coordinate = LEVEL_1_WINNING_Y;

	return board;
}

/*
	Initialize the entire board for level 2
*/
BoardElements initialize_level_2_board()
{

	BoardElements board;
	board.level = 2;

	// Coins coordinates for level 2
	board.coins_x = new int[LEVEL_2_COINS_AMOUNT];
	board.coins_y = new int[LEVEL_2_COINS_AMOUNT];
	board.grabbed_coins = new bool[LEVEL_2_COINS_AMOUNT];
	int coins_x[LEVEL_2_COINS_AMOUNT] = { 254, 476, 464, 446, 140, 200, 26 };
	int coins_y[LEVEL_2_COINS_AMOUNT] = { 387, 387, 267, 207, 387, 267, 207 };
	for (size_t i = 0; i < LEVEL_2_COINS_AMOUNT; i++)
	{
		board.coins_x[i] = coins_x[i];
		board.coins_y[i] = coins_y[i];
		board.grabbed_coins[i] = false;
	}
	
	board.platforms_amount = LEVEL_2_PLATFORMS_AMOUNT;
	board.platforms_x_coordinate = new int[LEVEL_2_PLATFORMS_AMOUNT];
	board.platforms_ending_x_coordinate = new int[LEVEL_2_PLATFORMS_AMOUNT];
	board.platforms_y_coordinate = new int[LEVEL_2_PLATFORMS_AMOUNT];
	board.platforms_widths = new int[LEVEL_2_PLATFORMS_AMOUNT];
	board.platforms_rows = new int[LEVEL_2_PLATFORMS_AMOUNT];

	for (size_t i = 0; i < 3; i++)
	{
		board.platforms_x_coordinate[i] = 230 * i;
		board.platforms_y_coordinate[i] = 390;
		board.platforms_widths[i] = 180;
		board.platforms_rows[i] = 1;
	}
	board.platforms_x_coordinate[3] = 0;
	board.platforms_y_coordinate[3] = 330;
	board.platforms_widths[3] = SCREEN_WIDTH;
	board.platforms_rows[3] = 2;
	for (size_t i = 4; i < 6; i++)
	{
		i == 4 ? board.platforms_x_coordinate[i] = 0 : board.platforms_x_coordinate[i] = 440;
		i == 4 ? board.platforms_widths[i] = 400 : board.platforms_widths[i] = 200;
		board.platforms_y_coordinate[i] = 270;
		board.platforms_rows[i] = 3;
	}
	for (size_t i = 6; i < 8; i++)
	{
		i == 6 ? board.platforms_x_coordinate[i] = 0 : board.platforms_x_coordinate[i] = 230;
		i == 6 ? board.platforms_widths[i] = 200 : board.platforms_widths[i] = 410;
		board.platforms_y_coordinate[i] = 210;
		board.platforms_rows[i] = 4;
	}
	board.platforms_x_coordinate[8] = 0;
	board.platforms_y_coordinate[8] = 150;
	board.platforms_widths[8] = SCREEN_WIDTH;
	board.platforms_rows[8] = 5;

	// Calculate ending x coordinates for each platform
	for (size_t i = 0; i < LEVEL_2_PLATFORMS_AMOUNT; i++)
		board.platforms_ending_x_coordinate[i] = board.platforms_x_coordinate[i] + board.platforms_widths[i];
	
	
	board.amount_of_ladders = LEVEL_2_AMOUNT_OF_LADDERS;
	board.ladders_x_coordinates = new int[LEVEL_2_AMOUNT_OF_LADDERS];
	board.ladders_y_coordinates = new int[LEVEL_2_AMOUNT_OF_LADDERS];
	board.ladders_rows = new int[LEVEL_2_AMOUNT_OF_LADDERS];
	board.ladder_width = 20;
	board.platform_height = 60;

	// Initialize ladders
	for (size_t i = 0; i < 3; i++)
	{
		board.ladders_y_coordinates[i] = 351;
		board.ladders_rows[i] = 1;
	}
	board.ladders_x_coordinates[0] = 60;
	board.ladders_x_coordinates[1] = SCREEN_WIDTH / 2;
	board.ladders_x_coordinates[2] = 560;
	for (size_t i = 3; i < 5; i++)
	{ 
		board.ladders_y_coordinates[i] = 291;
		board.ladders_rows[i] = 2;
	}
	board.ladders_x_coordinates[3] = 120;
	board.ladders_x_coordinates[4] = 530;
	for (size_t i = 5; i < 8; i++)
	{
		board.ladders_y_coordinates[i] = 231;
		board.ladders_rows[i] = 3;
	}
	board.ladders_x_coordinates[5] = 60;
	board.ladders_x_coordinates[6] = SCREEN_WIDTH / 2 - 20;
	board.ladders_x_coordinates[7] = 560;
	for (size_t i = 8; i < 10; i++)
	{
		board.ladders_y_coordinates[i] = 171;
		board.ladders_rows[i] = 4;
	}
	board.ladders_x_coordinates[8] = 130;
	board.ladders_x_coordinates[9] = 580;
	board.ladders_x_coordinates[10] = SCREEN_WIDTH / 2;
	board.ladders_y_coordinates[10] = 111;
	board.ladders_rows[10] = 5;

	board.initial_mario_x = LEVEL_2_MARIO_INITIAL_X;
	board.initial_mario_y = LEVEL_2_MARIO_INITIAL_Y;
	board.king_kong_x = LEVEL2_KING_KONG_X;
	board.king_kong_y = LEVEL2_KING_KONG_Y;

	board.winning_x1_coordinate = LEVEL_2_WINNING_X1;
	board.winning_x2_coordinate = LEVEL_2_WINNING_X2;
	board.winning_y_coordinate = LEVEL_2_WINNING_Y;


	return board;
}

BoardElements initialize_level_3_board()
{
	BoardElements board;
	board.level = 3;

	// Coins coordinates for level 2
	board.coins_x = new int[LEVEL_3_COINS_AMOUNT];
	board.coins_y = new int[LEVEL_3_COINS_AMOUNT];
	board.grabbed_coins = new bool[LEVEL_3_COINS_AMOUNT];
	int coins_x[LEVEL_3_COINS_AMOUNT] = { 116, 188, 20, 20, 446, 530, 446, 494 };
	int coins_y[LEVEL_3_COINS_AMOUNT] = { 387, 387, 207, 147, 207, 387, 387, 267 };
	for (size_t i = 0; i < LEVEL_3_COINS_AMOUNT; i++)
	{
		board.coins_x[i] = coins_x[i];
		board.coins_y[i] = coins_y[i];
		board.grabbed_coins[i] = false;
	}
	
	board.platforms_amount = LEVEL_3_PLATFORMS_AMOUNT;
	board.platforms_x_coordinate = new int[LEVEL_3_PLATFORMS_AMOUNT];
	board.platforms_ending_x_coordinate = new int[LEVEL_3_PLATFORMS_AMOUNT];
	board.platforms_y_coordinate = new int[LEVEL_3_PLATFORMS_AMOUNT];
	board.platforms_widths = new int[LEVEL_3_PLATFORMS_AMOUNT];
	board.platforms_rows = new int[LEVEL_3_PLATFORMS_AMOUNT];

	// Initialize platforms
	int first_platforms_X_cors[4] = {0, 167, 334, 501};
	for (size_t i = 0; i < 4; i++)
	{
		board.platforms_x_coordinate[i] = first_platforms_X_cors[i];
		board.platforms_y_coordinate[i] = 390;
		board.platforms_widths[i] = 137;
		board.platforms_rows[i] = 1;
	}
	for (size_t i = 4; i < 6; i++)
	{
		i == 4 ? board.platforms_x_coordinate[i] = 0 : board.platforms_x_coordinate[i] = 340;
		board.platforms_y_coordinate[i] = 330;
		board.platforms_widths[i] = 300;
		board.platforms_rows[i] = 2;
	}
	board.platforms_x_coordinate[6] = 0;
	board.platforms_y_coordinate[6] = 270;
	board.platforms_widths[6] = SCREEN_WIDTH;
	board.platforms_rows[6] = 3;
	for (size_t i = 7; i < 9; i++)
	{
		i == 7 ? board.platforms_x_coordinate[i] = 0 : board.platforms_x_coordinate[i] = 390;
		board.platforms_y_coordinate[i] = 210;
		i == 7 ? board.platforms_widths[i] = 120 : board.platforms_widths[i] = 250;
		board.platforms_rows[i] = 4;
	}
	board.platforms_x_coordinate[9] = 0;
	board.platforms_y_coordinate[9] = 150;
	board.platforms_widths[9] = SCREEN_WIDTH;
	board.platforms_rows[9] = 5;

	// Calculate ending x coordinates for each platform
	for (size_t i = 0; i < LEVEL_3_PLATFORMS_AMOUNT; i++)
		board.platforms_ending_x_coordinate[i] = board.platforms_x_coordinate[i] + board.platforms_widths[i];

	board.amount_of_ladders = LEVEL_3_AMOUNT_OF_LADDERS;
	board.ladders_x_coordinates = new int[LEVEL_3_AMOUNT_OF_LADDERS];
	board.ladders_y_coordinates = new int[LEVEL_3_AMOUNT_OF_LADDERS];
	board.ladders_rows = new int[LEVEL_3_AMOUNT_OF_LADDERS];
	board.ladder_width = 20;
	board.platform_height = 60;

	// Initialize ladders
	int first_ladders_X_cors[4] = { 10, 257, 394, 581 };
	for (size_t i = 0; i < 4; i++)
	{
		board.ladders_x_coordinates[i] = first_ladders_X_cors[i];
		board.ladders_y_coordinates[i] = 351;
		board.ladders_rows[i] = 1;
	}
	for (size_t i = 4; i < 6; i++)
	{
		i == 4 ? board.ladders_x_coordinates[i] = 100 : board.ladders_x_coordinates[i] = 550;
		board.ladders_y_coordinates[i] = 291;
		board.ladders_rows[i] = 2;
	}
	for (size_t i = 6; i < 8; i++)
	{
		i == 6 ? board.ladders_x_coordinates[i] = 40 : board.ladders_x_coordinates[i] = 580;
		board.ladders_y_coordinates[i] = 231;
		board.ladders_rows[i] = 3;
	}
	board.ladders_x_coordinates[8] = 80;
	board.ladders_y_coordinates[8] = 171;
	board.ladders_rows[8] = 4;


	board.initial_mario_x = LEVEL_3_MARIO_INITIAL_X;
	board.initial_mario_y = LEVEL_3_MARIO_INITIAL_Y;
	board.king_kong_x = LEVEL3_KING_KONG_X;
	board.king_kong_y = LEVEL3_KING_KONG_Y;

	board.winning_x1_coordinate = LEVEL_3_WINNING_X1;
	board.winning_x2_coordinate = LEVEL_3_WINNING_X2;
	board.winning_y_coordinate = LEVEL_3_WINNING_Y;

	return board;
}

void releaseMemory(BoardElements& board)
{
	delete[] board.platforms_x_coordinate;
	delete[] board.platforms_ending_x_coordinate;
	delete[] board.platforms_y_coordinate;
	delete[] board.platforms_widths;
	delete[] board.ladders_x_coordinates;
	delete[] board.ladders_y_coordinates;
	delete[] board.ladders_rows;
	delete[] board.platforms_rows;
	/*delete[] board.coins_x;
	delete[] board.coins_y;*/
	printf("Memory released");
}