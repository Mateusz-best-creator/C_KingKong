#include "../functions_definitions.h"

void DrawLadders(SDL_Surface* screen, int ladder_color)
{
	// Draw ladders for first, third and fifth rows
	for (int row = 0; row < 3; row++)
	{
		DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X, FIRST_ROW_LADDER - row * 120, 5, 50, ladder_color, ladder_color);
		DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X + 20, FIRST_ROW_LADDER - row * 120, 5, 50, ladder_color, ladder_color);
		for (size_t i = 1; i < 5; i++)
			DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X, FIRST_ROW_LADDER - row * 120 + i * 10, 25, 5, ladder_color, ladder_color);
		// x cor						y cor						    width height
	}
	// Draw ladders for second and fourth rows
	for (int row = 0; row < 2; row++)
	{
		DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X, FIRST_ROW_LADDER - 60 - row * 120, 5, 50, ladder_color, ladder_color);
		DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X + 20, FIRST_ROW_LADDER - 60 - row * 120, 5, 50, ladder_color, ladder_color);
		for (size_t i = 1; i < 5; i++)
			DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X, FIRST_ROW_LADDER - 60 - row * 120 + i * 10, 25, 5, ladder_color, ladder_color);
	}
}