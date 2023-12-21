#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"

#include <iostream>

void calculateTime(double& delta, int& tick1, int& tick2, double& worldTime)
{
	tick2 = SDL_GetTicks();
	// w tym momencie t2-t1 to czas w milisekundach,
	// jaki uplyna� od ostatniego narysowania ekranu
	// delta to ten sam czas w sekundach
	// here t2-t1 is the time in milliseconds since
	// the last screen was drawn
	// delta is the same time in seconds
	delta = (tick2 - tick1) * 0.001;
	tick1 = tick2;
	worldTime += delta;
}

bool fullscreen(SDL_Window** window, SDL_Renderer** renderer)
{
	int rc;
	// tryb pe�noekranowy / fullscreen mode
	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, window, renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return true;
	};
	return false;
}

/*
SDL_Surface** mario_running_right, SDL_Surface** mario_running_left, SDL_Surface** king_kong,
	SDL_Surface** mario_climbing, SDL_Surface** mario_jumping, SDL_Surface** charset
*/
bool load_bmp_images(SDL_Surfaces& surfaces, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) 
{
	bool Error = false;

	// Load charset image
	*(surfaces.charset) = SDL_LoadBMP("./cs8x8.bmp");
	if (surfaces.charset == nullptr) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	else {
		SDL_SetColorKey(*(surfaces.charset), true, 0x000000);
	}
	/*
	const int number_of_images = 6;
	char* image_paths[number_of_images] =
	{
		"./mario_running_right.bmp",
		"./mario_running_left.bmp",
		"./king_kong.bmp",
		"./mario_climbing.bmp",
		"./mario_jumping_right.bmp",
		"./mario_jumping_left.bmp",
	};
	SDL_Surface* images_to_load[number_of_images] =
	{
		*(surfaces.mario_running_right),
		*(surfaces.mario_running_left),
		*(surfaces.king_kong),
		*(surfaces.mario_climbing),
		*(surfaces.mario_jumping_right),
		*(surfaces.mario_jumping_left),
	};
	
	for (size_t i = 0; i < number_of_images; i++)
	{
		images_to_load[i] = SDL_LoadBMP(image_paths[i]);
		if (images_to_load[i] == nullptr) {
			printf("SDL_LoadBMP(%s) error: %s\n", image_paths[i], SDL_GetError());
			// Handle errors and set Error = true
			Error = true;
		}
	}
	*/
	// Load mario running right image
	*(surfaces.mario_running_right) = SDL_LoadBMP("./mario_running_right.bmp");
	if (*(surfaces.mario_running_right) == nullptr) {
		printf("SDL_LoadBMP(mario_running_right.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load mario running left image
	*(surfaces.mario_running_left) = SDL_LoadBMP("./mario_running_left.bmp");
	if (*(surfaces.mario_running_left) == nullptr) {
		printf("SDL_LoadBMP(mario_running_left.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load KingKong image
	*(surfaces.king_kong) = SDL_LoadBMP("./king_kong.bmp");
	if (*(surfaces.king_kong) == nullptr) {
		printf("SDL_LoadBMP(king_kong.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load Mario climbing image
	*(surfaces.mario_climbing) = SDL_LoadBMP("./mario_climbing.bmp");
	if (*(surfaces.king_kong) == nullptr) {
		printf("SDL_LoadBMP(mario_climbing.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load Mario jumping image
	*(surfaces.mario_jumping_right) = SDL_LoadBMP("./mario_jumping_right.bmp");
	if (*(surfaces.mario_jumping_right) == nullptr) {
		printf("SDL_LoadBMP(mario_jumping_right.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load Mario jumping image
	*(surfaces.mario_jumping_left) = SDL_LoadBMP("./mario_jumping_left.bmp");
	if (*(surfaces.mario_jumping_left) == nullptr) {
		printf("SDL_LoadBMP(mario_jumping_right.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Rolling barell
	*(surfaces.rolling_barell) = SDL_LoadBMP("./rolling_barell.bmp");
	if (*(surfaces.mario_jumping_left) == nullptr) {
		printf("SDL_LoadBMP(rolling_barell.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	return Error;
}

void clearSDL(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Window* window)
{
	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void drawInfoRectangle(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex,
	SDL_Renderer* renderer, char* text, TimeVariables& times, Colors& colors)
{
	// tekst informacyjny / info text
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, colors.czerwony, colors.niebieski);
	//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
	sprintf(text, "Czas trwania = %.1lf s  %.0lf klatek / s", times.worldTime, times.fps);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	//	      "Esc - exit, \030 - faster, \031 - slower"
	sprintf(text, "Esc - exit, n - new game, \x5f - jump, \030 - go up, \031 - go down");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void initialize_colors(SDL_Surface* screen, Colors& colors)
{
	// Initialize all the colors
	colors.czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	colors.zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	colors.czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	colors.niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	colors.brazowy = SDL_MapRGB(screen->format, 0xA5, 0x12A, 0x2A);
}

