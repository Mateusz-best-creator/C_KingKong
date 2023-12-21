#include "../functions_definitions.h"
#include <iostream>

// Measurements
const int VERTICAL_HEIGHT = 50;
const int VERTICAL_WIDTH = 5;

const int HORIZONTAL_HEIGHT = 5;
const int HORIZONTAL_WIDTH = 25;
const int HORIZONTAL_GAP = 10;
const int LEFT_LADDER_LEG_Y = 351;

void DrawLadders(SDL_Surface* screen, const BoardElements& board, int ladder_color)
{
	// Draw all ladders that are inside our board
	for (size_t i = 0; i < board.amount_of_ladders; i++)
	{
		DrawRectangle(screen, board.ladders_x_coordinates[i], board.ladders_y_coordinates[i],
			VERTICAL_WIDTH, VERTICAL_HEIGHT, ladder_color, ladder_color);
		DrawRectangle(screen, board.ladders_x_coordinates[i] + board.ladder_width, board.ladders_y_coordinates[i],
			VERTICAL_WIDTH, VERTICAL_HEIGHT, ladder_color, ladder_color);

		// Print four horizontal lines for each ladder
		for (size_t j = 0; j < 4; j++)
			DrawRectangle(screen, board.ladders_x_coordinates[i], board.ladders_y_coordinates[i] + (j + 1) * HORIZONTAL_GAP,
				HORIZONTAL_WIDTH, HORIZONTAL_HEIGHT, ladder_color, ladder_color);
	}
}

