#pragma once

#include "../functions_definitions.h"

/*
	In this file we store all the infomation about Mario object
*/

const int MARIO_FLOOR_DISTANCE = 3;
const int MARIO_SPEED = 6;
const int JUMP_HEIGHT = 30;
const double JUMP_SPEED = 1;
const int POINTS_FOR_COMPLETING_LEVEL = 2500;

struct Mario
{
	int x_coordinate;
	int y_coordinate;
	bool going_through_the_ladder;
	bool jumping;
	double jumping_pixels;
	bool going_down;
	enum DIRECTION { LEFT, RIGHT } direction;
	bool above_ladder;
	bool can_go_down;
	int lives;
	long points;
	int mario_row;
};

// Handling user events
int handleEvents(SDL_Event&, Mario&, SDL_Surfaces&, SDL_Elements&, const BoardElements&);
void left_arrow_event(Mario& mario_info, const BoardElements& board);
void right_arrow_event(Mario& mario_info, const BoardElements& board);
void upper_arrow_event(Mario& mario_info, const BoardElements& board);
void lower_arrow_event(Mario& mario_info, const BoardElements& board);
void space_event(Mario& mario_info);

// Drawing mario (also animation of the jump)
void draw_mario(SDL_Surfaces&, Mario&);

void get_mario_info(Mario&, const BoardElements&, int&);
bool check_if_mario_win(const BoardElements&, Mario&);
void interface(Mario& mario_info, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex,
	SDL_Renderer* renderer, char* text, Colors& colors);