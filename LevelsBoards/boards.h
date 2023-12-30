#pragma once

// Screen boarders (same for all levels)
const int ROWS = 5;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_LEFT_X_BORDER = 14;
const int SCREEN_RIGHT_X_BORDER = 626;
const int SCREEN_TOP_Y_BORDER = 1000;
const int SCREEN_BOTTOM_Y_BORDER = 387;

const int PLATFORM_HEIGHT = 10;

// Amount of ladders for each level
const int LEVEL_1_AMOUNT_OF_LADDERS = 5;
const int LEVEL_2_AMOUNT_OF_LADDERS = 11;
const int LEVEL_3_AMOUNT_OF_LADDERS = 9;

// How many platforms for each level
const int LEVEL_1_PLATFORMS_AMOUNT = 5;
const int LEVEL_2_PLATFORMS_AMOUNT = 9;
const int LEVEL_3_PLATFORMS_AMOUNT = 10;

// Initial mario coordinates for each level
const int LEVEL_1_MARIO_INITIAL_X = 50, LEVEL_1_MARIO_INITIAL_Y = 387;
const int LEVEL_2_MARIO_INITIAL_X = SCREEN_WIDTH / 2, LEVEL_2_MARIO_INITIAL_Y = 387;
const int LEVEL_3_MARIO_INITIAL_X = SCREEN_WIDTH / 2, LEVEL_3_MARIO_INITIAL_Y = 267;

// (X, Y) coordinates for KingKong in each level
const int LEVEL1_KING_KONG_X = 30, LEVEL1_KING_KONG_Y = 130;
const int LEVEL2_KING_KONG_X = 30, LEVEL2_KING_KONG_Y = 130;
const int LEVEL3_KING_KONG_X = 600, LEVEL3_KING_KONG_Y = 130;

// Winning coordinates for each level
const int LEVEL_1_WINNING_X1 = 590, LEVEL_1_WINNING_X2 = 602, LEVEL_1_WINNING_Y = 99;
const int LEVEL_2_WINNING_X1 = 330, LEVEL_2_WINNING_X2 = 348, LEVEL_2_WINNING_Y = 95;
const int LEVEL_3_WINNING_X1 = 504, LEVEL_3_WINNING_X2 = 539, LEVEL_3_WINNING_Y = 147;

// Coins amount for each level
const int LEVEL_1_COINS_AMOUNT = 5, LEVEL_2_COINS_AMOUNT = 7, LEVEL_3_COINS_AMOUNT = 8;

// Barells amount for each level
const int LEVEL_1_BARELLS_AMOUNT = 4, LEVEL_2_BARELLS_AMOUNT = 4, LEVEL_3_BARELLS_AMOUNT = 4;

// Trophies coordinates
const int LEVEL_1_GET_TROPHY_X = 308, LEVEL_1_GET_TROPHY_Y = 387, LEVEL_1_PUT_TROPHY_X = 308, LEVEL_1_PUT_TROPHY_Y = 147;
const int LEVEL_2_GET_TROPHY_X = 356, LEVEL_2_GET_TROPHY_Y = 267, LEVEL_2_PUT_TROPHY_X = 614, LEVEL_2_PUT_TROPHY_Y = 387;
const int LEVEL_3_GET_TROPHY_X = 170, LEVEL_3_GET_TROPHY_Y = 327, LEVEL_3_PUT_TROPHY_X = 362, LEVEL_3_PUT_TROPHY_Y = 387;

// Define board structure
struct BoardElements
{
	int level;
	int platforms_amount;
	int platform_height;
	int *platforms_y_coordinate, *platforms_x_coordinate, *platforms_ending_x_coordinate;
	int *platforms_widths;
	int* platforms_rows;
	int initial_mario_x, initial_mario_y;
	int king_kong_x, king_kong_y;
	int amount_of_ladders;
	int *ladders_x_coordinates, *ladders_y_coordinates;
	int *ladders_rows;
	int ladder_width;
	int winning_x1_coordinate, winning_x2_coordinate, winning_y_coordinate;
	int amount_of_coins;
	int* coins_x, * coins_y;
	bool* grabbed_coins;
	int barells_amount;
	int* barells_left_border, *barells_right_border, *barells_y_coordinate;
	int* barells_rows, *barells_direction;
	int get_trophy_x, get_trophy_y, put_trophy_x, put_trophy_y;
	bool display_get_trophy, display_put_trophy;
};
BoardElements initialize_board(int level);
BoardElements initialize_level_1_board();
BoardElements initialize_level_2_board();
BoardElements initialize_level_3_board();
void releaseMemory(const BoardElements& board);
void initialize_values(int level, BoardElements& board, const int coins_amount, const int platforms_amount,
	const int amount_of_ladders, const int mario_x, const int mario_y, const int king_kong_x,
	const int king_kong_y, const int winning_x1, const int winning_x2, const int winning_y,
	const int barells_amount);
void init_trophies(BoardElements& board, int grab_x, int grab_y, int put_x, int put_y);