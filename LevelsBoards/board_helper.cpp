#include "boards.h"

void init_trophies(BoardElements& board, int grab_x, int grab_y, int put_x, int put_y)
{
	// Initialize trophies coordinates
	board.get_trophy_x = grab_x;
	board.get_trophy_y = grab_y;
	board.put_trophy_x = put_x;
	board.put_trophy_y = put_y;
}

void initialize_values(int level, BoardElements& board, const int coins_amount, const int platforms_amount,
					   const int amount_of_ladders, const int mario_x, const int mario_y, const int king_kong_x,
					   const int king_kong_y, const int winning_x1, const int winning_x2, const int winning_y,
					   const int barells_amount)
{
	board.coins_x = new int[coins_amount];
	board.coins_y = new int[coins_amount];
	board.grabbed_coins = new bool[coins_amount];

	board.platforms_amount = platforms_amount;
	board.platforms_x_coordinate = new int[platforms_amount];
	board.platforms_ending_x_coordinate = new int[platforms_amount];
	board.platforms_y_coordinate = new int[platforms_amount];
	board.platforms_widths = new int[platforms_amount];
	board.platforms_rows = new int[platforms_amount];

	// Initialize all other data
	board.amount_of_ladders = amount_of_ladders;
	board.ladders_x_coordinates = new int[amount_of_ladders];
	board.ladders_y_coordinates = new int[amount_of_ladders];
	board.ladders_rows = new int[amount_of_ladders];
	board.ladder_width = 20;
	board.platform_height = 60;
	board.display_get_trophy = true;
	board.display_put_trophy = false;

	// Initial coordinates
	board.initial_mario_x = mario_x;
	board.initial_mario_y = mario_y;
	board.king_kong_x = king_kong_x;
	board.king_kong_y = king_kong_y;

	// Initialize winning coordinates
	board.winning_x1_coordinate = winning_x1;
	board.winning_x2_coordinate = winning_x2;
	board.winning_y_coordinate = winning_y;

	// Initialize barells
	board.barells_amount = barells_amount;
	board.barells_y_coordinate = new int[barells_amount];
	board.barells_left_border = new int[barells_amount];
	board.barells_right_border = new int[barells_amount];
	board.barells_rows = new int[barells_amount];
	board.barells_direction = new int[barells_amount];
}