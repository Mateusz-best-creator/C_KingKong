#pragma once
#include "../functions_definitions.h"

const double BARELL_SPEED = 0.6;

struct Barell
{
	double x_coordinate, y_coordinate;
	int image_index; // Based on that variable we will print appropriate image, to make it look like the barell is actually rolling
	int direction;
};

void draw_barell(Barell&, SDL_Surfaces&);
void move_barell(Barell& barell);
void move_barell_right(Barell& barell);
void move_barell_left(Barell& barell);