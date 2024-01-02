#include "infinite_game.h"
#include "../read_write_to_file/read_write_to_file.h"

#include <string.h>

int start_infinite_game(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, BoardElements& board)
{
    SDL_Event event;
    SDL_Surface* screen = *(surfaces.screen);

    // Initialize all the colors
    Colors colors;
    initialize_colors(screen, colors);

    // Initialize all helper variables for measuring the time, frames, fps...
    TimeVariables times = { SDL_GetTicks(), 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    Barell* barells = new Barell[board.barells_amount];
    FallingBarell flying_barell;

    mario_info.x_coordinate = board.initial_mario_x;
    mario_info.y_coordinate = board.initial_mario_y;
    // Initialize one falling barell
    flying_barell.x_coordinate = INITIAL_FALLING_BARELL_X;
    flying_barell.y_coordinate = INITIAL_FALLING_BARELL_Y;
    // Initialize the barells, based on board
    init_barells(board, barells);
    flying_barell.delta = 0;
    flying_barell.falling_down = false;

    int mario_won = 0;

    while (!times.quit)
    {
        if (check_if_mario_win(board, mario_info))
        {
            mario_info.all_points += mario_info.points;
            mario_info.points = 0;
            update_mario_metrics(mario_info, times, board.level);
            save_all_games(mario_info);
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
        DrawMonkey(surfaces, board, times);

        // Moving all barells
        move_barells(barells, board, surfaces);

        // Draw falling barell
        falling_barell(times, flying_barell, surfaces);
        jumped_over_barell(mario_info, board, barells, screen, *(surfaces.charset));
        
        // Draw treasure
        DrawSurface(screen, *(surfaces.level_1_winning_icon), board.winning_x1_coordinate, board.winning_y_coordinate);

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
            return 0; // Player lost all his lifes
        }
        else if (barell_collision_result == 1) // 1 means that we reset the game, beacuse player touched a barell
        {
            // Reset the board and set initial mario coordinates
            //board = initialize_board(board.level);
            init_barells(board, barells);
            mario_info.x_coordinate = board.initial_mario_x;
            mario_info.y_coordinate = board.initial_mario_y;
            continue;
        }
        
        char text[128];
        drawInfoRectangle(board, mario_info, surfaces, *(surfaces.charset), screen, SDL_elements.scrtex, SDL_elements.renderer, text, times, colors);

        // Handle user events (space, upper arrow...)
        times.quit = handleEvents(event, mario_info, surfaces, SDL_elements, board, barells, flying_barell, times);
        times.frames++;
    }
    delete[] barells;
    return mario_won;
}