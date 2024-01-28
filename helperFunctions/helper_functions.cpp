#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"

#include <string.h>

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
	Load all bmp images needed in our game.
*/
bool load_bmp_images(SDL_Surfaces& surfaces, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) 
{
	bool Error = false;

	// Load charset image
	*(surfaces.charset) = SDL_LoadBMP("./images/cs8x8.bmp");
	if (surfaces.charset == nullptr) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	else {
		SDL_SetColorKey(*(surfaces.charset), true, 0x000000);
	}
	// Load mario running right image
	*(surfaces.mario_running_right) = SDL_LoadBMP("./images/mario_running_right.bmp");
	if (*(surfaces.mario_running_right) == nullptr) {
		printf("SDL_LoadBMP(mario_running_right.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load mario running left image
	*(surfaces.mario_running_left) = SDL_LoadBMP("./images/mario_running_left.bmp");
	if (*(surfaces.mario_running_left) == nullptr) {
		printf("SDL_LoadBMP(mario_running_left.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load KingKong image
	*(surfaces.king_kong) = SDL_LoadBMP("./images/king_kong.bmp");
	if (*(surfaces.king_kong) == nullptr) {
		printf("SDL_LoadBMP(king_kong.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load Mario climbing image
	*(surfaces.mario_climbing) = SDL_LoadBMP("./images/mario_climbing.bmp");
	if (*(surfaces.king_kong) == nullptr) {
		printf("SDL_LoadBMP(mario_climbing.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load Mario jumping image
	*(surfaces.mario_jumping_right) = SDL_LoadBMP("./images/mario_jumping_right.bmp");
	if (*(surfaces.mario_jumping_right) == nullptr) {
		printf("SDL_LoadBMP(mario_jumping_right.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Load Mario jumping image
	*(surfaces.mario_jumping_left) = SDL_LoadBMP("./images/mario_jumping_left.bmp");
	if (*(surfaces.mario_jumping_left) == nullptr) {
		printf("SDL_LoadBMP(mario_jumping_right.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Level 1 logo
	*(surfaces.level_1_crown) = SDL_LoadBMP("./images/crown_logo.bmp");
	if (*(surfaces.level_1_crown) == nullptr) {
		printf("SDL_LoadBMP(images/crown_logo.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Level 2 logo
	*(surfaces.level_2_treasure) = SDL_LoadBMP("./images/treasure_logo.bmp");
	if (*(surfaces.level_2_treasure) == nullptr) {
		printf("SDL_LoadBMP(images/treasure_logo.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}

	// Level 3 logo
	*(surfaces.level_3_diamond) = SDL_LoadBMP("./images/diamond_logo.bmp");
	if (*(surfaces.level_3_diamond) == nullptr) {
		printf("SDL_LoadBMP(images/diamond_logo.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.level_1_winning_icon) = SDL_LoadBMP("./images/crown_logo_winning.bmp");
	if (*(surfaces.level_1_winning_icon) == nullptr) {
		printf("SDL_LoadBMP(crown_logo_winning.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.level_2_winning_icon) = SDL_LoadBMP("./images/treasure_logo_winning.bmp");
	if (*(surfaces.level_1_winning_icon) == nullptr) {
		printf("SDL_LoadBMP(treasure_logo_winning.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.level_3_winning_icon) = SDL_LoadBMP("./images/diamond_logo_winning.bmp");
	if (*(surfaces.level_1_winning_icon) == nullptr) {
		printf("SDL_LoadBMP(diamond_logo_winning.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.coin_icon) = SDL_LoadBMP("./images/coin.bmp");
	if (*(surfaces.king_kong) == nullptr) {
		printf("SDL_LoadBMP(coin.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.heart_icon) = SDL_LoadBMP("./images/heart.bmp");
	if (*(surfaces.heart_icon) == nullptr) {
		printf("SDL_LoadBMP(heart_icon.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	// Rolling barell
	*(surfaces.rolling_barell_1) = SDL_LoadBMP("./images/Barells/rolling_barell_1.bmp");
	if (*(surfaces.rolling_barell_1) == nullptr) {
		printf("SDL_LoadBMP(/Barells/rolling_barell_1.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	// Quitting icon
	*(surfaces.quit_icon) = SDL_LoadBMP("./images/quit.bmp");
	if (*(surfaces.quit_icon) == nullptr) {
		printf("SDL_LoadBMP(/quit.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	// Report icon
	*(surfaces.report_icon) = SDL_LoadBMP("./images/report.bmp");
	if (*(surfaces.report_icon) == nullptr) {
		printf("SDL_LoadBMP(/report.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.golden_cup_icon) = SDL_LoadBMP("./images/golden_cup.bmp");
	if (*(surfaces.golden_cup_icon) == nullptr) {
		printf("SDL_LoadBMP(/golden_cup.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.authentication_icon) = SDL_LoadBMP("./images/authentication.bmp");
	if (*(surfaces.authentication_icon) == nullptr) {
		printf("SDL_LoadBMP(/authentication.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.generate_level_icon) = SDL_LoadBMP("./images/hammer.bmp");
	if (*(surfaces.generate_level_icon) == nullptr) {
		printf("SDL_LoadBMP(/hammer.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.loading_icon) = SDL_LoadBMP("./images/loading.bmp");
	if (*(surfaces.loading_icon) == nullptr) {
		printf("SDL_LoadBMP(/saving.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.trophy_icon) = SDL_LoadBMP("./images/trophy.bmp");
	if (*(surfaces.trophy_icon) == nullptr) {
		printf("SDL_LoadBMP(/trophy.bmp) error: %s\n", SDL_GetError());
		// Handle errors and set Error = true
		Error = true;
	}
	*(surfaces.king_kong_throwing_barell) = SDL_LoadBMP("./images/monkey_throwing_barell.bmp");
	if (*(surfaces.king_kong_throwing_barell) == nullptr) {
		printf("SDL_LoadBMP(monkey_throwing_barell.bmp) error: %s\n", SDL_GetError());
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

void drawInfoRectangle(const BoardElements& board, const Mario& mario_info, SDL_Surfaces& surfaces, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex,
	SDL_Renderer* renderer, char* text, TimeVariables& times, Colors& colors)
{
	// Draw hearts
	for (size_t i = 0; i < mario_info.lifes; i++)
	{
		DrawSurface(screen, *(surfaces.heart_icon), SCREEN_WIDTH - 130 + i * 45, 70);
	}
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, colors.szary, colors.szary);
	sprintf_s(text, 128, "Mario points for level %d : %d   Mario lifes: %d", board.level, mario_info.points, mario_info.lifes);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	sprintf_s(text, 128, "Player name: %s   %s all points: %d", mario_info.name, mario_info.name, mario_info.all_points);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
	// tekst informacyjny / info text
	DrawRectangle(screen, 4, 430, SCREEN_WIDTH - 8, 36, colors.szary, colors.szary);
	//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
	sprintf_s(text, 128, "Czas trwania = %.1lf s  %.0lf klatek / s, Esc - exit, n - new game", times.worldTime, times.fps);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 435, text, charset);
	//	      "Esc - exit, \030 - faster, \031 - slower"
	sprintf_s(text, 128, "s - save game, \x5f - jump, \030 - go up, \031 - go down, \032 - go left, \033 - go right");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 450, text, charset);

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
	colors.jasny_niebieski = SDL_MapRGB(screen->format, 0x42, 0xa0, 0xdd);
	colors.szary = SDL_MapRGB(screen->format, 0x33, 0x33, 0x33);
	colors.zloty = SDL_MapRGB(screen->format, 0xff, 0xc8, 0x37);
	colors.srebrny = SDL_MapRGB(screen->format, 0xc1, 0xc9, 0xc8);
	colors.miedziany = SDL_MapRGB(screen->format, 0xa5, 0x2a, 0x2a);
}

