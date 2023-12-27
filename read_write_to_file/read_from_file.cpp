#include "read_write_to_file.h"
#include "../LevelsBoards/boards.h"
#include "../Mario/mario.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

void load_table_from_file(Mario& mario, BoardElements& board)
{
    FILE* file;

    if (fopen_s(&file, "./read_from_file.txt", "r") != 0) {
        printf("Error opening the file.\n");
        exit(0);
    }

    char name[20];
    int x, y;
    // Read data from the file using fscanf
    while (fscanf(file, "%s %d %d", name, &x, &y) == 3) 
    {
        if (strcmp(name, "Level") == 0)
        {
            board = initialize_board(x);
        }
        else if (strcmp(name, "Mario") == 0)
        {
            mario.x_coordinate = x;
            mario.y_coordinate = y;
        }
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

        printf("Name: %s\n", name);
        printf("X: %d\n", x);
        printf("Y: %d\n", y);
    }

    // Close the file
    fclose(file);
}