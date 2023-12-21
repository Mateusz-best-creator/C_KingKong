#pragma once

// Screen boarders (same for all levels)
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_LEFT_X_BORDER = 14;
const int SCREEN_RIGHT_X_BORDER = 626;
const int SCREEN_TOP_Y_BORDER = 1000;
const int SCREEN_BOTTOM_Y_BORDER = 387;

// Amount of ladders for each level
const int LEVEL_1_AMOUNT_OF_LADDERS = 5;
const int LEVEL_2_AMOUNT_OF_LADDERS = 5;
const int LEVEL_3_AMOUNT_OF_LADDERS = 5;

// How many platforms for each level
const int LEVEL_1_PLATFORMS_AMOUNT = 5;

// Initial mario coordinates for each level
const int LEVEL_1_MARIO_INITIAL_X = 50, LEVEL_1_MARIO_INITIAL_Y = 387;

// (X, Y) coordinates for KingKong in each level
const int LEVEL1_KING_KONG_X = SCREEN_WIDTH / 2;
const int LEVEL1_KING_KONG_Y = 80;

// Define all platrforms for level 1
struct BoardElements
{
	int platform_height;
	int platforms_y_coordinates[LEVEL_1_PLATFORMS_AMOUNT], platforms_widths[LEVEL_1_PLATFORMS_AMOUNT];
	int initial_mario_x, initial_mario_y;
	int king_kong_x, king_kong_y;
	int amount_of_ladders;
	int ladders_x_coordinates[LEVEL_1_AMOUNT_OF_LADDERS], ladders_y_coordinates[LEVEL_1_AMOUNT_OF_LADDERS];
	int ladder_width;
};
BoardElements initialize_board(int level);
BoardElements initialize_level_1_board();
