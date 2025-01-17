#include "mario.h"
#include "../functions_definitions.h"

bool jumped_over = false;

void jumped_over_barell(Mario& mario_info, BoardElements& board, Barell* barells, SDL_Surface* screen, SDL_Surface* charset)
{
	for (size_t i = 0; i < board.barells_amount; i++)
	{
		if (mario_info.mario_row != barells[i].row || mario_info.going_through_the_ladder)
			continue;
		if (((mario_info.x_coordinate <= barells[i].x_coordinate + BARELL_WIDTH &&
			mario_info.x_coordinate >= barells[i].x_coordinate) ||
			(mario_info.x_coordinate - MARIO_X_OFFSET + MARIO_WIDTH >= barells[i].x_coordinate &&
				mario_info.x_coordinate - MARIO_X_OFFSET + MARIO_WIDTH <= barells[i].x_coordinate + BARELL_WIDTH)) && mario_info.jumping)
		{
			jumped_over = true;
			break;
		}
	}
	if (!mario_info.jumping && jumped_over)
	{
		jumped_over = false;
		mario_info.points += POINTS_FOR_JUMPING_OVER_BARELL;
		mario_info.all_points += POINTS_FOR_JUMPING_OVER_BARELL;
		mario_info.just_jumped_over_barell = true;
	}
}

void jump_over_barell_message(const Mario& mario, SDL_Surface* screen, SDL_Surface* charset)
{
	char text[20];
	sprintf(text, "100");
	DrawString(screen, mario.x_coordinate - MESSAGE_X_OFFSET, mario.y_coordinate - MESSAGE_Y_OFFSET, text, charset);
}