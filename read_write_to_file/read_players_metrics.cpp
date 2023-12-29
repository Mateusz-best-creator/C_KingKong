#include "read_write_to_file.h"
#include "../playersAccount/players_account.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

const int MAX_PLAYERS = 5;

Player* read_players_metrics(int& num_players)
{
    Player* players = new Player[MAX_PLAYERS];

	FILE* file;
	// Open antoher file, which we will be use for ordering the players
	if (fopen_s(&file, "./players_metrics.txt", "r") != 0) {
		printf("Error opening players_metrics file.\n");
		exit(0);
	}

    int index = 0; // Variable to store the number of players read from the file
    char name[25];
    int level1_points, level2_points, level3_points, total;
    double level1_time, level2_time, level3_time;
    bool skip = false;
    char id[10];

    // Read data from the file using fscanf
    while (fscanf(file, "%s %s %d %d %d %lf %lf %lf %d", id, name, &level1_points, &level2_points, &level3_points,
        &level1_time, &level2_time, &level3_time, &total) == 9)
    {
        std::cout << "Name: " << name << std::endl;
        if (strcmp(id, "Player") == 0)
        {
            // Check if we arleady have that player in our database
            for (size_t i = 0; i < num_players; i++)
            {
                if (strcmp(players[i].name, name) == 0)
                {
                    skip = true;
                    if (players[i].level_1_best_score < level1_points)
                        players[i].level_1_best_score = level1_points;
                    else if (players[i].level_2_best_score < level2_points)
                        players[i].level_2_best_score = level2_points;
                    else if (players[i].level_3_best_score < level3_points)
                        players[i].level_3_best_score = level3_points;
                    else if (players[i].level_1_best_time < level1_time)
                        players[i].level_1_best_time = level1_time;
                    else if (players[i].level_2_best_time < level2_time)
                        players[i].level_2_best_time = level2_time;
                    else if (players[i].level_3_best_time < level3_time)
                        players[i].level_3_best_time = level3_time;
                    else if (players[i].total_points < total)
                        players[i].total_points = total;
                    break;
                }
            }
            if (skip)
            {
                skip = false;
                continue;
            }
            // Add player to the database
            strcpy(players[index].name, name);
            players[index].level_1_best_score = level1_points;
            players[index].level_2_best_score = level2_points;
            players[index].level_3_best_score = level3_points;
            players[index].level_1_best_time = level1_time;
            players[index].level_2_best_time = level2_time;
            players[index].level_3_best_time = level3_time;
            players[index].total_points = total;
            index++;
            num_players++;

            // Check if the maximum number of players has been reached
            if (index >= MAX_PLAYERS) {
                printf("Maximum number of players reached.\n");
                break;
            }
        }
    }
    return players;
}