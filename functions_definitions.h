#pragma once

#include "LevelsBoards/boards.h"

// Code from the template
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

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

// Time constants
const double SECONDS_BETWEEN_REFRESH = 0.5;
const double REFRESH_RATE = 1 / SECONDS_BETWEEN_REFRESH;

struct SDL_Surfaces
{
	SDL_Surface** screen, ** charset, ** mario_running_right, ** mario_running_left,
		** king_kong, ** mario_climbing, ** mario_jumping_right, ** mario_jumping_left, ** level_1_crown,
		** level_2_treasure, ** level_3_diamond, ** level_1_winning_icon, ** level_2_winning_icon, ** level_3_winning_icon,
		** coin_icon, ** heart_icon, ** rolling_barell_1, ** quit_icon, ** report_icon, ** golden_cup_icon,
		** authentication_icon, ** generate_level_icon, ** loading_icon, ** trophy_icon;
};

struct SDL_Elements
{
	SDL_Texture* scrtex = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};

struct TimeVariables
{
	int tick1, tick2, quit = 0, frames = 0;
	double delta, worldTime = 0.0, fpsTimer = 0.0, fps = 0.0, distance = 0.0, etiSpeed = 0.0;
};

struct Colors
{
	int czarny, zielony, czerwony, niebieski, brazowy, jasny_niebieski, szary, zloty, srebrny, miedziany;
};

// Drawing surfaces
void DrawPlatforms(SDL_Surface*, const BoardElements&, int);
void DrawLadders(SDL_Surface*, const BoardElements&, int);
void draw_coins(const BoardElements&, const SDL_Surfaces&);

// Helper functions
void calculateTime(double&, int&, int&, double&);
void clearSDL(SDL_Surface*, SDL_Surface*, SDL_Texture*, SDL_Renderer*, SDL_Window*);
bool fullscreen(SDL_Window**, SDL_Renderer**);
bool load_bmp_images(SDL_Surfaces& surfaces, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer);
void initialize_colors(SDL_Surface*, Colors&);
void infinite_game(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements);