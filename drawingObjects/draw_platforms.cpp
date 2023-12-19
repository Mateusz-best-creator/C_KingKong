#include "../functions_definitions.h"

void DrawPlatforms(SDL_Surface* screen, int platform_color)
{
	for (size_t i = 0; i < 5; i++)
		DrawRectangle(screen, SCREEN_WIDTH, 400 - i * 60, SCREEN_WIDTH, 10, platform_color, platform_color);
	/*for (size_t j = 0; j < 10; j++)
	{
		if (i % 2 == 1)
			DrawRectangle(screen, j * (SCREEN_WIDTH / 10),
				400 - i * 60 + j * 1, SCREEN_WIDTH / 10, 10, platform_color, platform_color);
		else
			DrawRectangle(screen, j * (SCREEN_WIDTH / 10),
				400 - i * 60 - j * 1, SCREEN_WIDTH / 10, 10, platform_color, platform_color);
	}*/
}