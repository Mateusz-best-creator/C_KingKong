#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "functions_definitions.h"
#include <iostream>


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {

	SDL_Event event;
	SDL_Surface* screen = nullptr, *charset = nullptr, *mario = nullptr, *king_kong = nullptr;
	SDL_Texture* scrtex = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	bool SDL_Error;
	SDL_Error = fullscreen(&window, &renderer);
	if (SDL_Error)
		return 1;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy��czenie widoczno�ci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// Loading all .bmp images
	SDL_Error = load_bmp_images(&mario, &king_kong, &charset, screen, scrtex, window, renderer);
	if (SDL_Error)
		return 1;

	// Initialize all the colors
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	// Adding some colors
	int brazowy = SDL_MapRGB(screen->format, 0xA5, 0x12A, 0x2A);

	// Initialize all helper variables for measuring the time, frames, fps...
	int tick1, tick2, quit = 0, frames = 0;
	double delta, worldTime = 0.0, fpsTimer = 0.0, fps = 0.0, distance = 0.0, etiSpeed = 0.0;
	tick1 = SDL_GetTicks();

	// Initial mario coordinates
	int mario_x_coordinate = 50, mario_y_coordinate = 387;

	// Boolean that indicates whether or not Mario is jumping
	bool jumping = false;
	int jumping_pixels = 0;
	bool going_down = false;

	bool going_through_the_ladder = false;

	while (!quit) {

		calculateTime(delta, tick1, tick2, worldTime);

		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, czarny);

		// Draw all ladders
		DrawLadders(screen, brazowy);

		// Draw all platforms
		DrawPlatforms(screen, brazowy);

		jump(screen, mario, mario_x_coordinate, mario_y_coordinate, jumping, jumping_pixels, going_down);
		// Draw king_kong surface
		DrawSurface(screen, king_kong, SCREEN_WIDTH / 2, 80);

		fpsTimer += delta;
		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		};

		char text[128];
		//drawInfoRectangle(charset, screen, scrtex, renderer, text, worldTime, fps, czerwony, niebieski);
		// tekst informacyjny / info text
		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
		//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		//	      "Esc - exit, \030 - faster, \031 - slower"
		sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		quit = handleEvents(event, mario_x_coordinate, mario_y_coordinate, 
			jumping, going_down, jumping_pixels, going_through_the_ladder);
		frames++;
	};
	// Clear all the settings
	clearSDL(charset, screen, scrtex, renderer, window);
	return 0;
};

