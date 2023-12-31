#include "../functions_definitions.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"
#include "../Barells/barells.h"
#include "../read_write_to_file/read_write_to_file.h"
#include "../Interface/interface.h"

#include <string.h>
#include <cstdlib>
#include <iostream>

int start_game(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, BoardElements& board, bool load_game_from_file)
{
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
        mario_info.x_coordinate = board.initial_mario_x;
        mario_info.y_coordinate = board.initial_mario_y;
    }
    // Initialize the barells, based on board
    init_barells(board, barells);

    // Initialize one falling barell
    FallingBarell flying_barell;
    flying_barell.falling_down = false;
    flying_barell.x_coordinate = INITIAL_FALLING_BARELL_X;
    flying_barell.y_coordinate = INITIAL_FALLING_BARELL_Y;
    flying_barell.delta = 0;

    int mario_won = 0;

    while (!times.quit)
    {
        if (check_if_mario_win(board, mario_info))
        {
            std::cout << "MARIO WINNING, SAVING TO FILE" << std::endl;
            update_mario_metrics(mario_info, times, board.level);
            save_all_games(mario_info);
            save_game("./player_metrics.txt", mario_info);
            mario_won = 1;
            break;
        }

        calculateTime(times.delta, times.tick1, times.tick2, times.worldTime);

        // Fill the entire screen with the given color
        SDL_FillRect(screen, NULL, colors.czarny);

        // Draw all coins
        draw_coins(board, surfaces);

        // Draw all ladders
        DrawLadders(screen, board, colors.brazowy);

        // Draw all platforms
        DrawPlatforms(screen, board, colors.brazowy);

        // Draw trophies
        draw_trophies(mario_info, board, surfaces, colors);

        // Make mario jumping if possible, draw mario
        draw_mario(surfaces, mario_info);

        // Draw king_kong surface
        DrawSurface(screen, *(surfaces.king_kong), board.king_kong_x, board.king_kong_y);

        // Moving all barells
        move_barells(barells, board, surfaces);

        // Draw falling barell
        falling_barell(times, flying_barell, surfaces);
        jumped_over_barell(mario_info, board, barells, screen, *(surfaces.charset));

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

        // Draw message if mario grabbed something
        if (mario_info.just_grabbed_coin)
            grab_coin_message(mario_info, screen, *(surfaces.charset));
        if (mario_info.just_jumped_over_barell)
            jump_over_barell_message(mario_info, screen, *(surfaces.charset));
        if (mario_info.just_grabbed_trophy)
            grab_trophy_message(mario_info, screen, *(surfaces.charset));
        if (mario_info.just_putted_trophy)
            put_trophy_message(mario_info, screen, *(surfaces.charset));

        times.fpsTimer += times.delta;
        if (times.fpsTimer > SECONDS_BETWEEN_REFRESH) {
            times.fps = times.frames * REFRESH_RATE;
            times.frames = 0;
            times.fpsTimer -= SECONDS_BETWEEN_REFRESH;
        }

        int barell_collision_result = -1;
        // Check collisions
        barell_collision_result = collision_with_barell(mario_info, barells, flying_barell, board, surfaces, SDL_elements, times);
        if (barell_collision_result == 0) // lifes == 0
        {
            return 0;
        }
        else if (barell_collision_result == 1) // 1 means that we reset the game, beacuse player touched a barell
        {
            // Reset the board and set initial mario coordinates
            board = initialize_board(board.level);
            init_barells(board, barells);
            mario_info.x_coordinate = board.initial_mario_x;
            mario_info.y_coordinate = board.initial_mario_y;
            continue;
        }

        char text[128];
        drawInfoRectangle(board, mario_info, surfaces, *(surfaces.charset), screen, SDL_elements.scrtex, SDL_elements.renderer, text, times, colors);

        // Handle user events (space, upper arrow...)
        times.quit = handleEvents(event, mario_info, surfaces, SDL_elements, board);
        if (times.quit == 2)
        {
            strcpy(mario_info.name, "Unknown");
            return 0;
        }
        else if (times.quit == 3 || times.quit == 4 || times.quit == 5)
        {
            return times.quit;
        }
        times.frames++;
    }
    delete[] barells;
    return mario_won;
}
