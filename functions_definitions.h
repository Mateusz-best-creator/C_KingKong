#pragma once


// Code from the template
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset);


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);


// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor);
// End of the code form the template



// Ladders constants
const int FIRST_ROW_LADDER = 351;
const int FIRST_THIRD_FIFTH_ROW_LADDER_X = 580;
const int SECOND_FOURTH_ROW_LADDER_X = 60;
const int LADDER_WIDTH = 20;

const int MARIO_SPEED = 6;

const int PLATFORM_HEIGHT = 60;
const int JUMP_HEIGHT = 30;
const int JUMP_SPEED = 1;

// Time constants
const double SECONDS_BETWEEN_REFRESH = 0.5;
const double REFRESH_RATE = 1 / SECONDS_BETWEEN_REFRESH;

// Screen boarders
const int SCREEN_LEFT_X_BORDER = 11;
const int SCREEN_RIGHT_X_BORDER = 629;
const int SCREEN_TOP_Y_BORDER = 1000;
const int SCREEN_BOTTOM_Y_BORDER = 387;

// Amount of ladders for each level
const int LEVEL_1_AMOUNT_OF_LADDERS = 5;
const int LEVEL_2_AMOUNT_OF_LADDERS = 5;
const int LEVEL_3_AMOUNT_OF_LADDERS = 5;

// (X, Y) coordinates for KingKong in each level
const int LEVEL1_KING_KONG_X = SCREEN_WIDTH / 2;
const int LEVEL1_KING_KONG_Y = 80;

// Initial mario coordinates
const int mario_initial_x_coordinate = 50, mario_initial_y_coordinate = 387;

struct Mario
{
	int x_coordinate;
	int y_coordinate;
	bool going_through_the_ladder;
	bool jumping;
	int jumping_pixels;
	bool going_down;
	enum DIRECTION { LEFT, RIGHT } direction;
};

struct SDL_Surfaces
{
	SDL_Surface** screen, **charset, **mario_running_right, **mario_running_left, **king_kong, **mario_climbing, **mario_jumping;
};

struct TimeVariables
{
	int tick1, tick2, quit = 0, frames = 0;
	double delta, worldTime = 0.0, fpsTimer = 0.0, fps = 0.0, distance = 0.0, etiSpeed = 0.0;
};

struct Colors
{
	int czarny, zielony, czerwony, niebieski, brazowy;
};

// Drawing surfaces
void DrawPlatforms(SDL_Surface*, int);
void DrawLadders(SDL_Surface*, int);

// Handling user events
int handleEvents(SDL_Event&, Mario& mario_info);
void jump(SDL_Surface*, SDL_Surface*, SDL_Surface*, SDL_Surface*, SDL_Surface*, Mario& mario_info);

// Helper functions
void calculateTime(double&, int&, int&, double&);
void clearSDL(SDL_Surface*, SDL_Surface*, SDL_Texture*, SDL_Renderer*, SDL_Window*);
void drawInfoRectangle(SDL_Surface*, SDL_Surface*, SDL_Texture*,
	SDL_Renderer*, char*,TimeVariables&, Colors&);
bool fullscreen(SDL_Window**, SDL_Renderer**);
bool load_bmp_images(SDL_Surfaces& surfaces, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer);
void initialize_colors(SDL_Surface*, Colors&);


