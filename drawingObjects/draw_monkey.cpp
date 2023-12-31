#include "../functions_definitions.h"
#include "../Barells/barells.h"

void DrawMonkey(const SDL_Surfaces& surfaces, const BoardElements& board, const TimeVariables& time)
{
	double dif = 0;
	if (time.worldTime != 0 && (int(time.worldTime + 1) % FALLING_BARELL_TIME == 0) && time.worldTime > 1)
	{
		while (dif < FALLING_BARELL_TIME)
		{
			DrawSurface(*(surfaces.screen), *(surfaces.king_kong_throwing_barell), board.king_kong_x, board.king_kong_y);
			dif += 0.003;
		}
	}
	else
		DrawSurface(*(surfaces.screen), *(surfaces.king_kong), board.king_kong_x, board.king_kong_y);
}