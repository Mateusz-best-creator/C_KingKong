#include "../Mario/mario.h"
#include "../LevelsBoards/boards.h"
#include "../functions_definitions.h"
#include "infinite_game.h"

#include <iostream>

bool generate_board_interface(SDL_Event& event);

void infinite_game(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
	BoardElements board = generating_board();
	for (size_t i = 0; i < board.platforms_amount; i++)
	{
		std::cout << "Platform x: " << board.platforms_x_coordinate[i] << " y: " << board.platforms_y_coordinate[i] << std::endl;
		std::cout << "Platform end: " << board.platforms_ending_x_coordinate[i] << " width: " << board.platforms_widths[i] << " row: " << board.platforms_rows[i] << std::endl;
	}
	std::cout << "Mario: " << board.initial_mario_x << " " << board.initial_mario_y << " " << board.king_kong_x << " " << board.king_kong_y << std::endl;
	std::cout << "Barell: " << board.barells_y_coordinate[0] << std::endl;
	for (size_t i = 0; i < board.amount_of_ladders; i++)
	{
		std::cout << "Ladder " << board.ladders_x_coordinates[i] << " " << board.ladders_y_coordinates[i] << std::endl;
		std::cout << "Ladders2: " << board.ladders_rows[i] << " " << board.ladder_width << std::endl;
	}
	start_infinite_game(mario_info, surfaces, SDL_elements, board);
	
	SDL_Event event;
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);
	SDL_FillRect(*(surfaces.screen), NULL, colors.czarny);

	char text[60];
	bool checking = true;

	while (checking)
	{
		DrawRectangle(*(surfaces.screen), 4, 200, SCREEN_WIDTH - 8, 75, colors.szary, colors.szary);
		sprintf(text, "This option is not implemented yet");
		DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 230, text, *(surfaces.charset));
		SDL_UpdateTexture(SDL_elements.scrtex, NULL, (*(surfaces.screen))->pixels, (*(surfaces.screen))->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL_elements.renderer);

		// Fill the entire screen with given color
		SDL_FillRect((*(surfaces.screen)), NULL, colors.czarny);
		checking = generate_board_interface(event);
	}
	
}

bool generate_board_interface(SDL_Event & event)
{
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) {
		case SDL_KEYDOWN:
			return false;
		case SDL_QUIT:
			return false;
		}
	}
	return true;
}