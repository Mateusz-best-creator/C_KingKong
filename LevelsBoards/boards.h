#pragma once

// Screen boarders (same for all levels)
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
const int LEVEL_1_WINNING_X1 = 584, LEVEL_1_WINNING_X2 = 596, LEVEL_1_WINNING_Y = 99;
const int LEVEL_2_WINNING_X1 = 320, LEVEL_2_WINNING_X2 = 338, LEVEL_2_WINNING_Y = 105;
const int LEVEL_3_WINNING_X1 = 509, LEVEL_3_WINNING_X2 = 539, LEVEL_3_WINNING_Y = 147;

// Define all platrforms for level 1
struct BoardElements
{
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
};
BoardElements initialize_board(int level);
BoardElements initialize_level_1_board();
BoardElements initialize_level_2_board();
BoardElements initialize_level_3_board();
void releaseMemory(BoardElements&);