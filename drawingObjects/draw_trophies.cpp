#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"

void draw_trophies(Mario& mario_info, BoardElements& board, const SDL_Surfaces& surfaces, const Colors& colors)
{
	if (board.display_get_trophy)
	{
		if (mario_info.x_coordinate == board.get_trophy_x && mario_info.y_coordinate == board.get_trophy_y)
		{
			mario_info.just_grabbed_trophy = true;
			mario_info.has_trophy = true;
			board.display_get_trophy = false;
		}
		else
			DrawSurface(*(surfaces.screen), *(surfaces.trophy_icon), board.get_trophy_x, board.get_trophy_y);
	}
	else
		DrawRectangle(*(surfaces.screen), board.put_trophy_x - 20, board.put_trophy_y + 13, 40, 10, colors.zloty, colors.zloty);

	if (board.display_put_trophy && !mario_info.has_trophy)
		DrawSurface(*(surfaces.screen), *(surfaces.trophy_icon), board.put_trophy_x, board.put_trophy_y);

	if (mario_info.has_trophy)
	{
		if (mario_info.x_coordinate >= board.put_trophy_x - 20 && mario_info.x_coordinate <= board.put_trophy_x + 20
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
	sprintf(text, "You capture trophy!");
	DrawString(screen, mario.x_coordinate - 60, mario.y_coordinate - 40, text, charset);
}

void put_trophy_message(const Mario& mario, SDL_Surface* screen, SDL_Surface* charset)
{
	char text[20];
	sprintf(text, "2000");
	DrawString(screen, mario.x_coordinate - 10, mario.y_coordinate - 40, text, charset);
}