#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"

void DrawPlatforms(SDL_Surface* screen, const BoardElements& board, int platform_color)
{
	for (size_t i = 0; i < 5; i++)
		DrawRectangle(screen, SCREEN_WIDTH, 400 - i * 60, SCREEN_WIDTH, 10, platform_color, platform_color);
}