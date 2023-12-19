#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "template.h"
#include <iostream>
void DrawPlatforms();
void DrawLadders(SDL_Surface* screen, int ladder_color);

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *mario;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	int rc;
	// tryb pe³noekranowy / fullscreen mode
	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	                                 &window, &renderer);
	/*rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);*/
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	mario = SDL_LoadBMP("./mario.bmp");
	if(mario == NULL) {
		printf("SDL_LoadBMP(mario.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	// Adding some colors
	int brazowy = SDL_MapRGB(screen->format, 0xA5, 0x12A, 0x2A);

	int tick1, tick2, quit = 0, frames = 0;
	double delta, worldTime = 0.0, fpsTimer = 0.0, fps = 0.0, distance = 0.0, etiSpeed = 0.0;
	tick1 = SDL_GetTicks();

	/*const int MARIO_INITIAL_X = 50;
		const int MARIO_INITIAL_Y = 387;*/
	int mario_x_coordinate = 50, mario_y_coordinate = 387;

	while(!quit) {
		tick2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (tick2 - tick1) * 0.001;
		tick1 = tick2;

		worldTime += delta;

		distance += etiSpeed * delta;

		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, czarny);

		// Draw all ladders
		DrawLadders(screen, brazowy);

		// Draw platforms
		for (size_t i = 0; i < 5; i++)
			DrawRectangle(screen, SCREEN_WIDTH, 400 - i * 60, SCREEN_WIDTH, 10, brazowy, brazowy);

		// Draw all surfaces
		DrawSurface(screen, mario, mario_x_coordinate, mario_y_coordinate);
				 // screen  mario  x coor y coor
		std::cout << "(x, y) = (" << mario_x_coordinate << ", " << mario_y_coordinate << ")\n";

		fpsTimer += delta;
		if(fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
			};

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

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_RIGHT) mario_x_coordinate += 2;
					else if (event.key.keysym.sym == SDLK_LEFT) mario_x_coordinate -= 2;
					else if (event.key.keysym.sym == SDLK_UP) mario_y_coordinate -= 2;
					else if (event.key.keysym.sym == SDLK_DOWN) mario_y_coordinate += 2;
					break;
				//case SDL_KEYUP:
				//	etiSpeed = 1.0;
				//	break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		frames++;
		};

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
};

const int FIRST_ROW_LADDER = 351;
const int FIRST_THIRD_FIFTH_ROW_LADDER_X = 580;
const int SECOND_FOURTH_ROW_LADDER_X = 60;

void DrawLadders(SDL_Surface* screen, int ladder_color)
{
	for (int row = 0; row < 3; row++)
	{
		// Draw ladder for first, third and fifth rows
		DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X, FIRST_ROW_LADDER - row * 120, 5, 50, ladder_color, ladder_color);
		DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X + 20, FIRST_ROW_LADDER - row * 120, 5, 50, ladder_color, ladder_color);
		for (size_t i = 1; i < 5; i++)
			DrawRectangle(screen, FIRST_THIRD_FIFTH_ROW_LADDER_X, FIRST_ROW_LADDER - row * 120 + i * 10, 25, 5, ladder_color, ladder_color);
									// x cor						y cor						    width height
	}

	for (int row = 0; row < 2; row++)
	{
		// Draw ladder for second and fourth rows
		DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X, FIRST_ROW_LADDER - 60 - row * 120, 5, 50, ladder_color, ladder_color);
		DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X + 20, FIRST_ROW_LADDER - 60 - row * 120, 5, 50, ladder_color, ladder_color);
		for (size_t i = 1; i < 5; i++)
			DrawRectangle(screen, SECOND_FOURTH_ROW_LADDER_X, FIRST_ROW_LADDER - 60 - row * 120 + i * 10, 25, 5, ladder_color, ladder_color);
	}
}