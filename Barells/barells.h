#pragma once
#include "../functions_definitions.h"

const double BARELL_SPEED = 0.4;
const double FALLING_BARELL_SPEED = 0.3;
const int FALLING_BARELL_TIME = 5;
const int INITIAL_FALLING_BARELL_X = 300;
const int INITIAL_FALLING_BARELL_Y = 70;
const int ENDING_FALLING_BARELL_Y = 420;
const int FALLING_BARELL_LEFT_BORDER = 40;
const int FALLING_BARELL_RIGHT_BORDER = 600;
const int BARELL_WIDTH = 20;
const int FLYING_BARELL_WIDTH = 25, FLYING_BARELL_HEIGHT = 25;

struct Barell
{
	double x_coordinate, y_coordinate;
	int image_index; // Based on that variable we will print appropriate image, to make it look like the barell is actually rolling
	int direction; // 0 for left and 1 for right
	int left_border, right_border, row;
};

struct FallingBarell
{
	double x_coordinate, y_coordinate, delta;
	bool falling_down;
};

void falling_barell(TimeVariables& times, FallingBarell& barell, const SDL_Surfaces& surfaces);

void init_barells(const BoardElements& board, Barell* barells);
void draw_barell(Barell&, const SDL_Surfaces&);
void move_barells(Barell*, const BoardElements&, const SDL_Surfaces&);
void move_barell(Barell& barell, int);
void move_barell_right(Barell& barell);
void move_barell_left(Barell& barell);