#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"
#include "../Barells/barells.h"
#include "../read_write_to_file/read_write_to_file.h"
#include "../Interface/interface.h"
#include <iostream>
#include <cstdlib>

static int lifes = 3;
static long local_points = 0;
static int times_mario_won = 0;

bool start_game(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, BoardElements& board, 
	bool lost_life, long gained_points, bool load_game_from_file, bool initial_state)
{
	if (lost_life)
	{
		lifes--;
	    
    }
    local_points += gained_points;
    if (initial_state)
    {
        times_mario_won = 0;
        local_points = 0;
        lifes = 3;
    }

	SDL_Event event;
	SDL_Surface* screen = *(surfaces.screen);

	// Initialize all the colors
	Colors colors;
	initialize_colors(screen, colors);

	// Initialize all helper variables for measuring the time, frames, fps...
	TimeVariables times = { SDL_GetTicks(), 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if (load_game_from_file)
	{
		load_table_from_file(mario_info, board);
	}
    Barell* barells = new Barell[board.barells_amount];
    if (!load_game_from_file)
    {
        mario_info.points = local_points;
        mario_info.lifes = lifes;
        mario_info.x_coordinate = board.initial_mario_x;
        mario_info.y_coordinate = board.initial_mario_y;
        /* Do not reset the coins if mario loses a life
        for (size_t i = 0; i < board.amount_of_coins; i++)
            board.grabbed_coins[i] = false;
        */
    }
    // Initialize the barells, based on board
    init_barells(board, barells);

    bool mario_won = false;

    while (!times.quit)
    {
        if (check_if_mario_win(board, mario_info))
        {
            update_mario_metrics(mario_info, times, board.level);
            save_game(mario_info);
            mario_won = true;
            break;
        }

        calculateTime(times.delta, times.tick1, times.tick2, times.worldTime);

        // Fill the entire screen with the given color
        SDL_FillRect(screen, NULL, colors.czarny);

        draw_coins(board, surfaces);

        // Draw all ladders
        DrawLadders(screen, board, colors.brazowy);

        // Draw all platforms
        DrawPlatforms(screen, board, colors.brazowy);

        // Make mario jumping if possible, draw mario
        draw_mario(surfaces, mario_info);

        // Draw king_kong surface
        DrawSurface(screen, *(surfaces.king_kong), board.king_kong_x, board.king_kong_y);

        // Moving all barells
        move_barells(barells, board, surfaces);

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

        // Draw message if mario grabbed a coin
        if (mario_info.just_grabbed_coin)
            grab_coin_message(mario_info, screen, *(surfaces.charset));

        times.fpsTimer += times.delta;
        if (times.fpsTimer > SECONDS_BETWEEN_REFRESH) {
            times.fps = times.frames * REFRESH_RATE;
            times.frames = 0;
            times.fpsTimer -= SECONDS_BETWEEN_REFRESH;
        }

        // Check collisions
        collision_with_barell(mario_info, barells, board, surfaces, SDL_elements, times);

        char text[128];
        drawInfoRectangle(board, mario_info, surfaces, *(surfaces.charset), screen, SDL_elements.scrtex, SDL_elements.renderer, text, times, colors);

        // Handle user events (space, upper arrow...)
        times.quit = handleEvents(event, mario_info, surfaces, SDL_elements, board);
        if (times.quit == 2)
            return false;
        times.frames++;
    }
    delete[] barells;
    return mario_won;
}