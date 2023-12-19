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

const int FIRST_ROW_LADDER = 351;
const int FIRST_THIRD_FIFTH_ROW_LADDER_X = 580;
const int SECOND_FOURTH_ROW_LADDER_X = 60;

const int MARIO_SPEED = 6;

// My own functions

void DrawPlatforms(SDL_Surface*, int);
void DrawLadders(SDL_Surface*, int);
void calculateTime(double&, int&, int&, double&);
int handleEvents(SDL_Event&, int&, int&, bool&, bool&, int&, bool&);
void clearSDL(SDL_Surface*, SDL_Surface*, SDL_Texture*, SDL_Renderer*, SDL_Window*);
void drawInfoRectangle(SDL_Surface*, SDL_Surface*, SDL_Texture*,
	SDL_Renderer*, char*, double, int, int, int);
void jump(SDL_Surface* screen, SDL_Surface* mario, int mario_x_coordinate, int mario_y_coordinate, bool& jumping, int& jumping_pixels, bool& going_down);
bool fullscreen(SDL_Window** window, SDL_Renderer** renderer);
bool load_bmp_images(SDL_Surface** mario, SDL_Surface** king_kong, SDL_Surface** charset,
	SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer);
void initialize_colors(SDL_Surface*, int&, int&, int&, int&, int&);