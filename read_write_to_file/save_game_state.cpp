#include "read_write_to_file.h"
#include "../Mario/mario.h"
#include "../LevelsBoards/boards.h"

#include <stdio.h>

void save_game_state(const Mario& mario_info, const BoardElements& board, Barell* barells, FallingBarell& flying_barell)
{
    FILE* file = fopen("saved_game_state.txt", "w");

    // Check if the file was successfully opened
    if (file == NULL) {
        fprintf(stderr, "Unable to open the file.\n");
        exit(0);
    }

    char* board_coins = new char[board.amount_of_coins + 1];
    for (size_t i = 0; i < board.amount_of_coins; i++)
    {
        if (board.grabbed_coins[i])
            board_coins[i] = '2';
        else
            board_coins[i] = '1';
    }
    board_coins[board.amount_of_coins] = '\0';

    // Write to the file using fprintf
    fprintf(file, "%s\n", mario_info.name);
    fprintf(file, "Level %d 0\n", board.level);
    fprintf(file, "Mario %d %d\n", mario_info.x_coordinate, mario_info.y_coordinate);
    fprintf(file, "AllPoints %d 0\n", mario_info.all_points);
    fprintf(file, "Lifes %d 0\n", mario_info.lifes);
    fprintf(file, "ThroughLadder %d 0\n", mario_info.going_through_the_ladder);
    fprintf(file, "Jumping %d 0\n", mario_info.jumping);
    fprintf(file, "GoingDown %d 0\n", mario_info.going_down);
    fprintf(file, "Direction %d 0\n", mario_info.direction);
    fprintf(file, "AboveLadder %d 0\n", mario_info.above_ladder);
    fprintf(file, "CanGoDown %d 0\n", mario_info.can_go_down);
    fprintf(file, "Points %d 0\n", mario_info.points);
    fprintf(file, "MarioRow %d 0\n", mario_info.mario_row);
    fprintf(file, "JustGrabbedCoin %d 0\n", mario_info.just_grabbed_coin);
    fprintf(file, "Coins %s 0\n", board_coins);
    // Additional features about trophy
    fprintf(file, "HasTrophy %d 0\n", mario_info.has_trophy);
    fprintf(file, "DisplayGrabTrophy %d 0\n", board.display_get_trophy);
    fprintf(file, "DisplayPutTrophy %d 0\n", board.display_put_trophy);

    // Send barells coordinates
    for (size_t i = 0; i < board.barells_amount; i++)
    {
        fprintf(file, "Barell %lf %lf\n", barells[i].x_coordinate, barells[i].y_coordinate);
        fprintf(file, "BarellDir %d 0\n", barells[i].direction);
    }

    // Send flying barell coordinates
    fprintf(file, "FlyingBarellCoor %lf %lf\n", flying_barell.x_coordinate, flying_barell.y_coordinate);

    releaseMemory(board);
    delete[] board_coins;
    fclose(file);
}