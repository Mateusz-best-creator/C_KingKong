#include "../functions_definitions.h"
#include "../Mario/mario.h"

void left_arrow_event(Mario& mario_info, const BoardElements& board)
{
	if (mario_info.x_coordinate <= SCREEN_LEFT_X_BORDER)
		return;
	bool mario_can_go_left_from_ladder = false;
	for (size_t i = 0; i < board.platforms_amount; i++)
	{
		if (mario_info.y_coordinate + MARIO_FLOOR_DISTANCE == board.platforms_y_coordinates[i])
		{
			mario_can_go_left_from_ladder = true;
			break;
		}
	}
	if (mario_info.going_through_the_ladder && !mario_can_go_left_from_ladder)
		return;
	mario_info.direction = Mario::LEFT;
	mario_info.x_coordinate -= MARIO_SPEED;
}

void right_arrow_event(Mario& mario_info, const BoardElements& board)
{
	if (mario_info.jumping)
	{
		mario_info.x_coordinate += int (MARIO_SPEED / 2);
	}
	if (mario_info.x_coordinate >= SCREEN_RIGHT_X_BORDER)
		return;
	bool mario_can_go_right_from_ladder = false;
	for (size_t i = 0; i < board.platforms_amount; i++)
	{
		if (mario_info.y_coordinate + MARIO_FLOOR_DISTANCE == board.platforms_y_coordinates[i])
		{
			mario_can_go_right_from_ladder = true;
			break;
		}
	}
	if (mario_info.going_through_the_ladder && !mario_can_go_right_from_ladder)
		return;
	
	mario_info.direction = Mario::RIGHT;
	mario_info.x_coordinate += MARIO_SPEED;
}

void upper_arrow_event(Mario& mario_info, const BoardElements& board)
{
	if (mario_info.going_through_the_ladder)
	{
		mario_info.y_coordinate -= MARIO_SPEED;
	}
}

void lower_arrow_event(Mario& mario_info, const BoardElements& board)
{
	if (mario_info.going_through_the_ladder)
	{
		mario_info.can_go_down = true;
		for (size_t k = 0; k < board.platforms_amount; k++)
		{
			if (board.platforms_y_coordinates[k] == mario_info.y_coordinate + MARIO_FLOOR_DISTANCE)
			{
				mario_info.can_go_down = false;
				break;
			}
		}
		if (mario_info.can_go_down)
			mario_info.y_coordinate += MARIO_SPEED;
	}
	else if (mario_info.above_ladder)
	{
		mario_info.y_coordinate += MARIO_SPEED;
		mario_info.going_through_the_ladder = true;
	}
}

void space_event(Mario& mario_info)
{
	if (!mario_info.jumping && !mario_info.going_through_the_ladder)
	{
		// Jumping, important helper variables
		mario_info.jumping = true;
		mario_info.going_down = false;
		mario_info.jumping_pixels = 0;
	}
}
