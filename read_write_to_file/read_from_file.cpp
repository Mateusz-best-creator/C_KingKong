#include "read_write_to_file.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

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
    
    if (fopen_s(&file, "./read_from_file_level_3.txt", "r") != 0) {
        printf("Error opening read_from_file_level_3 file.\n");
        exit(0);
    }
    

    char name[20];
    int x, y;
    // Read data from the file using fscanf
    while (fscanf(file, "%s %d %d", name, &x, &y) == 3) 
    {
        // Loading Mario informations from file
        load_mario_informations(board, mario, name, x, y);
        load_board_informations(board, mario, name, x, y);

        printf("Name: %s\n", name);
        printf("X: %d\n", x);
        printf("Y: %d\n", y);
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

}