#include "barells.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomNumber(int min, int max);
void draw_falling_barell(FallingBarell& barell, const SDL_Surfaces& surfaces);
void move_falling_barell(FallingBarell& barell);

static int delta = 0;

void falling_barell(TimeVariables& times, FallingBarell& barell, const SDL_Surfaces& surfaces)
{
	// Throw barell every FALLING_BARELL_TIME seconds
	if (times.worldTime - delta > FALLING_BARELL_TIME && !barell.falling_down)
	{
		delta += FALLING_BARELL_TIME;
		// Initialize falling barell
		barell.x_coordinate = getRandomNumber(40, 600);
		barell.y_coordinate = 70;
		barell.falling_down = true;
	}

	if (barell.falling_down)
	{
		draw_falling_barell(barell, surfaces);
		move_falling_barell(barell);
	}

	if (barell.y_coordinate > 387)
		barell.falling_down = false;
}

void draw_falling_barell(FallingBarell& barell, const SDL_Surfaces& surfaces)
{
	DrawSurface(*(surfaces.screen), *(surfaces.rolling_barell_1), barell.x_coordinate, barell.y_coordinate);
}

int getRandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}

void move_falling_barell(FallingBarell& barell)
{
	barell.y_coordinate += FALLING_BARELL_SPEED;
}