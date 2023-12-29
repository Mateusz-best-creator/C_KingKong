#pragma once

#include "../functions_definitions.h"
#include "../Barells/barells.h"
#include <stdio.h>

/*
	In this file we store all the infomation about Mario object
*/

const int MARIO_FLOOR_DISTANCE = 3;
const int MARIO_SPEED = 6;
const int JUMP_HEIGHT = 40;
const double JUMP_SPEED = 0.25;
const int POINTS_FOR_COMPLETING_LEVEL = 5000;
const int POINTS_FOR_GRABBING_COIN = 500;

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
	int lifes;
	long points;
	long all_points;
	int mario_row;
	bool just_grabbed_coin;
	
	/*
		Results from each level
	*/
	int level_1_index;
	int level_2_index;
	int level_3_index;
	char name[21];
	int level_1_scores[20];
	int level_2_scores[20];
	int level_3_scores[20];
	double level_1_times[20];
	double level_2_times[20];
	double level_3_times[20];
	int level_1_best_score;
	int level_2_best_score;
	int level_3_best_score;
	double level_1_best_time;
	double level_2_best_time;
	double level_3_best_time;
	int levels_completed;
};

// Handling user events
int handleEvents(SDL_Event&, Mario&, SDL_Surfaces&, SDL_Elements&, BoardElements&);
void left_arrow_event(Mario& mario_info, const BoardElements& board);
void right_arrow_event(Mario& mario_info, const BoardElements& board);
void upper_arrow_event(Mario& mario_info, const BoardElements& board);
void lower_arrow_event(Mario& mario_info, const BoardElements& board);
void space_event(Mario& mario_info);

// Drawing mario (also animation of the jump)
void draw_mario(SDL_Surfaces&, Mario&);

// Interface while playing
void drawInfoRectangle(const BoardElements&, const Mario&, SDL_Surfaces&, SDL_Surface*, SDL_Surface*, 
	SDL_Texture*, SDL_Renderer*, char*, TimeVariables&, Colors&);

// Grabbing a coin
void grab_coin(Mario& mario_info, const BoardElements& board);
void grab_coin_message(const Mario& mario, SDL_Surface* screen, SDL_Surface* charset);

void get_mario_info(Mario&, const BoardElements&, int&);
bool check_if_mario_win(const BoardElements&, Mario&);
void interface(Mario& mario_info, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex,
	SDL_Renderer* renderer, char* text, Colors& colors);

// Collision with barell
int collision_with_barell(Mario&, Barell*, BoardElements&, SDL_Surfaces&, SDL_Elements&, TimeVariables&);
void update_mario_metrics(Mario&, TimeVariables&, int);

// Starting the game
bool game(Mario&, SDL_Surfaces&, SDL_Elements&, bool);
int start_game(Mario&, SDL_Surfaces&, SDL_Elements&, BoardElements&, bool, long, bool);