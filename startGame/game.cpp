#include "../functions_definitions.h"
#include "../Interface/interface.h"

void game(SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, bool initial_state)
{
	// Initialize all the colors
	Colors colors;
	initialize_colors(*(surfaces.screen), colors);

	int x = 1, y = 1, option = 1;
	initial_interface(surfaces, SDL_elements, colors, x, y);

	BoardElements board;

	// Initialize the board for the appropriate level
	// Player choose to quit
	if (x == 1 && y == 1)
		exit(0);
	// Choosing to play 
	else if (x == 2)
	{
		board = initialize_board(y);
		start_game(surfaces, SDL_elements, board, false, 0, false, initial_state);
	}
	// Loading game from file option
	else if (x == 1 && y == 3)
	{
		start_game(surfaces, SDL_elements, board, false, 0, true, true); // Always load as initial state
	}
	else if (x != 2)
		exit(0);

	releaseMemory(board);
}