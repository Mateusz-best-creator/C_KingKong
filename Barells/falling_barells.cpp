#include "barells.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_n(int min, int max);
void draw_falling_barell(FallingBarell& barell, const SDL_Surfaces& surfaces);
void move_falling_barell(FallingBarell& barell);


void falling_barell(TimeVariables& times, FallingBarell& barell, const SDL_Surfaces& surfaces)
{
	// Throw barell every FALLING_BARELL_TIME seconds
	if (times.worldTime - barell.delta > FALLING_BARELL_TIME && !barell.falling_down)
	{
		barell.delta = times.worldTime;
		// Initialize falling barell
		barell.x_coordinate = random_n(FALLING_BARELL_LEFT_BORDER, FALLING_BARELL_RIGHT_BORDER);
		barell.y_coordinate = INITIAL_FALLING_BARELL_Y;
		barell.falling_down = true;
	}

	if (barell.falling_down)
	{
		draw_falling_barell(barell, surfaces);
		move_falling_barell(barell);
	}

	if (barell.y_coordinate > ENDING_FALLING_BARELL_Y)
	{
		barell.falling_down = false;
		barell.y_coordinate = INITIAL_FALLING_BARELL_Y;
	}
}

void draw_falling_barell(FallingBarell& barell, const SDL_Surfaces& surfaces)
{
	DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_1), barell.x_coordinate, barell.y_coordinate);
}

int random_n(int min, int max) {
	return min + rand() % (max - min + 1);
}

void move_falling_barell(FallingBarell& barell)
{
	barell.y_coordinate += FALLING_BARELL_SPEED;
}