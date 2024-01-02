#include "read_write_to_file.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>

void load_mario_informations(BoardElements&, Mario&, const char*, int, int);
void load_board_informations(BoardElements&, Mario&, const char*, int, int);

void load_table_from_file(Mario& mario, BoardElements& board)
{
    FILE* file;

    /*
        Depending on what level you want to load,
        you have to uncomment appropriate piece of code
        and comment out the rest "file choosing" options
    */
    /*
    if (fopen_s(&file, "./read_from_file_level_1.txt", "r") != 0) {
        printf("Error opening the file.\n");
        exit(0);
    }
    */
    /*
    if (fopen_s(&file, "./read_from_file_level_2.txt", "r") != 0) {
        printf("Error opening the file.\n");
        exit(0);
    }
    */
    /*
     if (fopen_s(&file, "./read_from_file_level_3.txt", "r") != 0) {
        printf("Error opening saved_game_state file.\n");
        exit(0);
    }
    */

    if (fopen_s(&file, "./saved_game_state.txt", "r") != 0) {
        printf("Error opening saved_game_state file.\n");
        exit(0);
    }


    char name[20];
    char mario_name[20];
    int x, y;
    // First row should always be a name
    if (fscanf(file, "%s", mario_name) == 1)
    {
        mario_name[strlen(mario_name)] = '\0';
        strcpy(mario.name, mario_name);
    }

    // Read data from the file using fscanf
    while (fscanf(file, "%s %d %d", name, &x, &y) == 3)
    {
        // Loading Mario informations from file
        load_mario_informations(board, mario, name, x, y);
        load_board_informations(board, mario, name, x, y);
    }
    // Close the file
    fclose(file);
}

void load_mario_informations(BoardElements& board, Mario& mario, const char* name, int x, int y)
{
    if (strcmp(name, "Mario") == 0)
    {
        mario.x_coordinate = x;
        mario.y_coordinate = y;
    }
    else if (strcmp(name, "Level") == 0)
    {
        board = initialize_board(x);
    }
    else if (strcmp(name, "AllPoints") == 0)
        mario.all_points = x;
    else if (strcmp(name, "Lifes") == 0)
        mario.lifes = x;
    else if (strcmp(name, "ThroughLadder") == 0)
        mario.going_through_the_ladder = bool(x);
    else if (strcmp(name, "Jumping") == 0)
    {
        mario.jumping = bool(x);
        mario.jumping_pixels = y;
    }
    else if (strcmp(name, "Direction") == 0)
    {
        if (x == 0)
            mario.direction = Mario::RIGHT;
        else if (x == 1)
            mario.direction = Mario::LEFT;
    }
    else if (strcmp(name, "GoingDown") == 0)
        mario.going_down = bool(x);
    else if (strcmp(name, "AboveLadder") == 0)
        mario.above_ladder = bool(x);
    else if (strcmp(name, "CanGoDown") == 0)
        mario.can_go_down = bool(x);
    else if (strcmp(name, "Points") == 0)
        mario.points = x;
    else if (strcmp(name, "MarioRow") == 0)
        mario.mario_row = x;
    else if (strcmp(name, "JustGrabbedCoin") == 0)
        mario.just_grabbed_coin = bool(x);
    else if (strcmp(name, "HasTrophy") == 0)
        mario.has_trophy = bool(x);
}

void load_board_informations(BoardElements& board, Mario& mario, const char* name, int x, int y)
{
    if (strcmp(name, "Level") == 0)
        board = initialize_board(x);
    else if (strcmp(name, "Coins") == 0)
    {
        int temp = x;
        for (int i = board.amount_of_coins - 1; i >= 0; i--)
        {
            if (temp % 10 == 2) // 2 means that coins is arleady captured
                board.grabbed_coins[i] = true;
            else // Otherwise coin is still on the board
                board.grabbed_coins[i] = false;
            temp /= 10;
        }
    }
    else if (strcmp(name, "DisplayGrabTrophy") == 0)
        board.display_get_trophy = bool(x);
    else if (strcmp(name, "DisplayPutTrophy") == 0)
        board.display_put_trophy = bool(x);
}

void load_barells_from_file(Barell* barells, FallingBarell& flying_barell)
{
    FILE* file;
    if (fopen_s(&file, "./saved_game_state.txt", "r") != 0) {
        printf("Error opening saved_game_state file.\n");
        exit(0);
    }

    char name[20];
    double x, y;
    int index = 0;
    fscanf(file, "%s", name);
    while (fscanf(file, "%s %lf %lf", name, &x, &y) == 3)
    {
        if (strcmp(name, "Barell") == 0)
        {
            barells[index].x_coordinate = x;
            barells[index].y_coordinate = y;
        }
        else if (strcmp(name, "BarellDir") == 0)
        {
            barells[index].direction = x;
            index++;
        }
        else if (strcmp(name, "FlyingBarellCoor") == 0)
        {
            flying_barell.x_coordinate = x;
            flying_barell.y_coordinate = y;
        }
    }
}