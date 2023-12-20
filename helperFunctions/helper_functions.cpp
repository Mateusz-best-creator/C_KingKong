#include "../functions_definitions.h"

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

bool load_bmp_images(SDL_Surface** mario, SDL_Surface** king_kong, SDL_Surface** charset,
	SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) {
	bool Error = false;

	// Load charset image
	*charset = SDL_LoadBMP("./cs8x8.bmp");
	if (*charset == nullptr) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	else {
		SDL_SetColorKey(*charset, true, 0x000000);
	}

	// Load mario image
	*mario = SDL_LoadBMP("./mario2.bmp");
	if (*mario == nullptr) {
		printf("SDL_LoadBMP(mario2.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load KingKong image
	*king_kong = SDL_LoadBMP("./king_kong.bmp");
	if (*king_kong == nullptr) {
		printf("SDL_LoadBMP(king_kong.bmp) error: %s\n", SDL_GetError());
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
	SDL_Renderer* renderer, char* text, double& worldTime, double& fps, int firstcolor, int secondcolor)
{
	// tekst informacyjny / info text
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, firstcolor, secondcolor);
	//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
	sprintf(text, "Czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	//	      "Esc - exit, \030 - faster, \031 - slower"
	sprintf(text, "Esc - exit, n - new game, \x5f - jump, \030 - go up, \031 - go down");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void initialize_colors(SDL_Surface* screen, int& czarny, int& zielony, int& czerwony, int& niebieski, int& brazowy)
{
	// Initialize all the colors
	czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	brazowy = SDL_MapRGB(screen->format, 0xA5, 0x12A, 0x2A);
}

