#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"
#include <iostream>

void start_game(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, const BoardElements& board)
{
	SDL_Event event;
	SDL_Surface* screen = *(surfaces.screen);

	// Initialize all the colors
	Colors colors;
	initialize_colors(screen, colors);

	// Initialize all helper variables for measuring the time, frames, fps...
	TimeVariables times = { SDL_GetTicks(), 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// Create mario object
	Mario mario_info = { board.initial_mario_x, board.initial_mario_y, false, false, 0, false, Mario::RIGHT, false, false, 3, 0, 1 };

	while (!times.quit) {

		if (check_if_mario_win(board, mario_info))
		{
			std::cout << "Mario winning!!!" << std::endl;
			break;
		}

		calculateTime(times.delta, times.tick1, times.tick2, times.worldTime);

		// Fill the entire screen with given color
		SDL_FillRect(screen, NULL, colors.czarny);

		// Draw all ladders
		DrawLadders(screen, board, colors.brazowy);

		// Draw all platforms
		DrawPlatforms(screen, board, colors.brazowy);

		// Make mario jumping if possible, draw mario
		draw_mario(surfaces, mario_info);

		// Draw king_kong surface
		DrawSurface(screen, *(surfaces.king_kong), board.king_kong_x, board.king_kong_y);

		// Draw barell
		DrawSurface(screen, *(surfaces.rolling_barell), board.king_kong_x, board.king_kong_y);

		// Draw final treasures
		switch (board.level)
		{
		case 1:
			DrawSurface(screen, *(surfaces.level_1_winning_icon), LEVEL_1_WINNING_X1, LEVEL_1_WINNING_Y);
			break;
		case 2:
			DrawSurface(screen, *(surfaces.level_2_winning_icon), LEVEL_2_WINNING_X1, LEVEL_2_WINNING_Y);
			break;
		case 3:
			DrawSurface(screen, *(surfaces.level_3_winning_icon), LEVEL_3_WINNING_X1, LEVEL_3_WINNING_Y);
			break;
		default:
			break;
		}
		

		times.fpsTimer += times.delta;
		if (times.fpsTimer > SECONDS_BETWEEN_REFRESH) {
			times.fps = times.frames * REFRESH_RATE;
			times.frames = 0;
			times.fpsTimer -= SECONDS_BETWEEN_REFRESH;
		};

		char text[128];
		drawInfoRectangle(*(surfaces.charset), screen, SDL_elements.scrtex, SDL_elements.renderer, text, times, colors);

		// Handle user event (space, upper arrow...)
		times.quit = handleEvents(event, mario_info, surfaces, SDL_elements, board);
		times.frames++;
	};
}