#include "../functions_definitions.h"

const int LADDER_ROWS = 5;
// Measurements
const int VERTICAL_HEIGHT = 50;
const int VERTICAL_WIDTH = 5;

const int HORIZONTAL_HEIGHT = 5;
const int HORIZONTAL_WIDTH = 25;
const int HORIZONTAL_GAP = 10;

void DrawLadders(SDL_Surface* screen, int ladder_color)
{
	// Draw ladders for first, third and fifth rows
	int right_ladders = 3;
	for (int row = 0; row < right_ladders; row++)
	{
		// Print two vertical lines
		DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X, FIRST_ROW_LADDER - row * PLATFORM_HEIGHT * 2, 
			VERTICAL_WIDTH, VERTICAL_HEIGHT, ladder_color, ladder_color);
		DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X + LADDER_WIDTH, FIRST_ROW_LADDER - row * PLATFORM_HEIGHT * 2,
			VERTICAL_WIDTH, VERTICAL_HEIGHT, ladder_color, ladder_color);

		// Print five horizontal lines
		for (size_t i = 1; i < LADDER_ROWS; i++)
			DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X, FIRST_ROW_LADDER - row * PLATFORM_HEIGHT * 2 + i * HORIZONTAL_GAP,
				HORIZONTAL_WIDTH, HORIZONTAL_HEIGHT, ladder_color, ladder_color);
	}
	// Draw ladders for second and fourth rows
	int left_ladders = 2;
	for (int row = 0; row < left_ladders; row++)
	{
		// Print two vertical lines
		DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X, 
			FIRST_ROW_LADDER - PLATFORM_HEIGHT - row * PLATFORM_HEIGHT * 2, 
			VERTICAL_WIDTH, VERTICAL_HEIGHT, ladder_color, ladder_color);
		DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X + LADDER_WIDTH, 
			FIRST_ROW_LADDER - PLATFORM_HEIGHT - row * PLATFORM_HEIGHT * 2, 
			VERTICAL_WIDTH, VERTICAL_HEIGHT, ladder_color, ladder_color);
		
		// Print five horizontal lines
		for (size_t i = 1; i < LADDER_ROWS; i++)
			DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X, 
				FIRST_ROW_LADDER - PLATFORM_HEIGHT - row * PLATFORM_HEIGHT * 2 + i * HORIZONTAL_GAP, 
				HORIZONTAL_WIDTH, HORIZONTAL_HEIGHT, ladder_color, ladder_color);
	}
}

