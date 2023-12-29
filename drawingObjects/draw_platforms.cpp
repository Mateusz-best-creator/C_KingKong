#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"

void DrawPlatforms(SDL_Surface* screen, const BoardElements& board, int platform_color)
{
	for (size_t i = 0; i < board.platforms_amount; i++)
		DrawRectangle(screen, board.platforms_x_coordinate[i], board.platforms_y_coordinate[i] + PLATFORM_HEIGHT,
			board.platforms_widths[i], PLATFORM_HEIGHT, platform_color, platform_color);
}