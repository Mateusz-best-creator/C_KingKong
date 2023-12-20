#include "../functions_definitions.h"

void start_game(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
	SDL_Event event;
	SDL_Surface* screen = *(surfaces.screen);

	// Initialize all the colors
	Colors colors;
	initialize_colors(screen, colors);

	// Initialize all helper variables for measuring the time, frames, fps...
	TimeVariables times = { SDL_GetTicks(), 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// Create mario object
	Mario mario_info = { mario_initial_x_coordinate, mario_initial_y_coordinate, false, false, 0, false, Mario::RIGHT };

	while (!times.quit) {

		calculateTime(times.delta, times.tick1, times.tick2, times.worldTime);

		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, colors.czarny);

		// Draw all ladders
		DrawLadders(screen, colors.brazowy);

		// Draw all platforms
		DrawPlatforms(screen, colors.brazowy);

		// Make mario jumping if possible, draw mario
		jump(surfaces, mario_info);

		// Draw king_kong surface
		DrawSurface(screen, *(surfaces.king_kong), LEVEL1_KING_KONG_X, LEVEL1_KING_KONG_Y);

		times.fpsTimer += times.delta;
		if (times.fpsTimer > SECONDS_BETWEEN_REFRESH) {
			times.fps = times.frames * REFRESH_RATE;
			times.frames = 0;
			times.fpsTimer -= SECONDS_BETWEEN_REFRESH;
		};

		char text[128];
		drawInfoRectangle(*(surfaces.charset), screen, SDL_elements.scrtex, SDL_elements.renderer, text, times, colors);

		// Handle user event (space, upper arrow...)
		times.quit = handleEvents(event, mario_info, surfaces, SDL_elements);
		times.frames++;
	};
	// Clear all the settings
	clearSDL(*(surfaces.charset), screen, SDL_elements.scrtex, SDL_elements.renderer, SDL_elements.window);
}