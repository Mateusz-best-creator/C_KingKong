#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"

const int TROPHY_X_OFFSET = 20;
const int TROPHY_Y_OFFSET = 13;
const int GOLD_PLATFORM_WIDTH = 40;
const int GOLD_PLATFORM_HEIGHT = 10;

void draw_trophies(Mario& mario_info, BoardElements& board, const SDL_Surfaces& surfaces, const Colors& colors)
{
	if (board.display_get_trophy)
	{
		if (abs_value(mario_info.x_coordinate - board.get_trophy_x) <= MARIO_SPEED && 
			(mario_info.y_coordinate == board.get_trophy_y || mario_info.y_coordinate + MARIO_FLOOR_DISTANCE == board.get_trophy_y))
		{
			mario_info.just_grabbed_trophy = true;
			mario_info.has_trophy = true;
			board.display_get_trophy = false;
		}
		else
			DrawSurface(*(surfaces.screen), *(surfaces.trophy_icon), board.get_trophy_x, board.get_trophy_y);
	}
	else
		DrawRectangle(*(surfaces.screen), board.put_trophy_x - TROPHY_X_OFFSET, board.put_trophy_y + TROPHY_Y_OFFSET,
			GOLD_PLATFORM_WIDTH, GOLD_PLATFORM_HEIGHT, colors.zloty, colors.zloty);

	if (board.display_put_trophy && !mario_info.has_trophy)
		DrawSurface(*(surfaces.screen), *(surfaces.trophy_icon), board.put_trophy_x, board.put_trophy_y);

	if (mario_info.has_trophy)
	{
		if (mario_info.x_coordinate >= board.put_trophy_x - TROPHY_X_OFFSET && mario_info.x_coordinate <= board.put_trophy_x + TROPHY_X_OFFSET
			&& mario_info.y_coordinate == board.put_trophy_y)
		{
			mario_info.has_trophy = false;
			board.display_put_trophy = true;
			mario_info.points += POINTS_FOR_PUTTING_TROPHY;
			mario_info.all_points += POINTS_FOR_PUTTING_TROPHY;
			mario_info.just_putted_trophy = true;
		}
	}
}

void grab_trophy_message(const Mario& mario, SDL_Surface* screen, SDL_Surface* charset)
{
	char text[30];
	sprintf_s(text, 30, "You capture trophy!");
	DrawString(screen, mario.x_coordinate - LONG_MESSAGE_X_OFFSET, mario.y_coordinate - MESSAGE_Y_OFFSET, text, charset);
}

void put_trophy_message(const Mario& mario, SDL_Surface* screen, SDL_Surface* charset)
{
	char text[10];
	sprintf_s(text, 10, "2000");
	DrawString(screen, mario.x_coordinate - MESSAGE_X_OFFSET, mario.y_coordinate - MESSAGE_Y_OFFSET, text, charset);
}