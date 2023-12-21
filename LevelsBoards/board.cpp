#include "boards.h"
#include "../functions_definitions.h"

BoardElements initialize_board(int level)
{
	switch (level)
	{
		case 1:
			return initialize_level_1_board();
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}

BoardElements initialize_level_1_board()
{
	BoardElements board;
	// Initialize the entire board for level 1

	board.platforms_amount = LEVEL_1_PLATFORMS_AMOUNT;
	// Initialize platforms width and beginning y coordinates
	for (size_t i = 0; i < LEVEL_1_PLATFORMS_AMOUNT; i++)
	{
		board.platforms_y_coordinates[i] = 390 - i * 60;
		board.platforms_widths[i] = SCREEN_WIDTH;
	}

	// Initialize all other data
	board.amount_of_ladders = LEVEL_1_AMOUNT_OF_LADDERS;
	board.ladder_width = 20;
	board.platform_height = 60;
		
	// Initial coordinates
	board.initial_mario_x = LEVEL_1_MARIO_INITIAL_X;
	board.initial_mario_y = LEVEL_1_MARIO_INITIAL_Y;
	board.king_kong_x = LEVEL1_KING_KONG_X;
	board.king_kong_y = LEVEL1_KING_KONG_Y;

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

	return board;
}