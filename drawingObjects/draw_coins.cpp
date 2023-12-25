#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"

void draw_coins(const BoardElements& board, const SDL_Surfaces& surfaces)
{
	int amount = 0;
	switch (board.level)
	{
	case 1:
		amount = LEVEL_1_COINS_AMOUNT;
		break;
	case 2:
		amount = LEVEL_2_COINS_AMOUNT;
		break;
	case 3:
		amount = LEVEL_3_COINS_AMOUNT;
		break;
	default:
		break;
	}

	for (size_t i = 0; i < amount; i++)
	DrawSurface(*(surfaces.screen), *(surfaces.coin_icon), board.coins_x[i], board.coins_y[i]);
}