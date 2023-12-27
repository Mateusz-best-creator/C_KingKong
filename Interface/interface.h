#pragma once

#include "../functions_definitions.h"
#include "../Mario/mario.h" 

/*
	Initial interface constants
*/

const int AMOUNT_OF_OPTIONS = 9;

const int RECTANGLE_HEIGHT = 110;
const int RECTANGLE_WIDTH = 150;

const int RECTANGLES_1_X = 45;
const int RECTANGLES_2_X = SCREEN_WIDTH / 2 - 75;
const int RECTANGLES_3_X = 445;
const int RECTANGLE_1_Y = 70;
const int RECTANGLE_2_Y = 190;
const int RECTANGLE_3_Y = 310;

const int Y_OFFSET = 120;
const int INITIAL_SURFACE_Y = 120;
const int INITIAL_STRING_Y = 165;

const int DESC_RECTANGLE_INIT_X_Y = 4;
const int DESC_RECTANGLE_WIDTH = SCREEN_WIDTH - 8;
const int DESC_RECTANGLE_HEIGHT = 60;
const int DESC_LINE_1 = 10;
const int DESC_LINE_2 = 28;
const int DESC_LINE_3 = 45;

// Interfaces
void initial_interface(const SDL_Surfaces&, const SDL_Elements&, const Colors&, int&, int&);
bool continue_interface(SDL_Surfaces&, SDL_Elements&, Mario&, BoardElements&);
void congratulations_interface(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements);