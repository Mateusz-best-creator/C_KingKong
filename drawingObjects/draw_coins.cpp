#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"

int abs_value(int num)
{
	return (num < 0) ? -num : num;
}

void draw_coins(const BoardElements& board, const SDL_Surfaces& surfaces)
{
	int amount = board.amount_of_coins;

	for (size_t i = 0; i < amount; i++)
		if (!board.grabbed_coins[i])
			DrawSurface(*(surfaces.screen), *(surfaces.coin_icon), board.coins_x[i], board.coins_y[i]);
}

void grab_coin(Mario& mario_info, const BoardElements& board)
{
	int amount = board.amount_of_coins;
	for (size_t i = 0; i < amount; i++)
	{
		if (abs_value(mario_info.x_coordinate - board.coins_x[i]) <= MARIO_SPEED && mario_info.y_coordinate == board.coins_y[i] && !board.grabbed_coins[i])
		{
			mario_info.points += POINTS_FOR_GRABBING_COIN;
			mario_info.all_points += POINTS_FOR_GRABBING_COIN;
			board.grabbed_coins[i] = true;
			mario_info.just_grabbed_coin = true;
			return;
		}
	}
	mario_info.just_grabbed_coin = false;
}

void grab_coin_message(const Mario& mario, SDL_Surface* screen, SDL_Surface* charset)
{
	char text[20];
	sprintf(text, "500");
	DrawString(screen, mario.x_coordinate - MESSAGE_X_OFFSET, mario.y_coordinate - MESSAGE_Y_OFFSET, text, charset);
}