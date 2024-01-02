#pragma once

#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"

void infinite_game(Mario&, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements);
BoardElements generating_board();
int start_infinite_game(Mario&, SDL_Surfaces&, SDL_Elements&, BoardElements&);