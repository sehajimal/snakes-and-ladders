#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--help") == 0) 
    {
        help();
        return 0;
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Let's play Snakes and Ladders!\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    srand(time(0)); 

    char status[100] = "in progress";
    int player1Pos = 1;
    int player2Pos = 1;

    int boardLength = 10;
    int boardHeight = 10;

    char player1[5] = "P1";
    char player2[5] = "P2";

    // Create a board of slots
    struct Slot board[boardLength][boardHeight];

    // Generate the board initially
    generateBoard(player1, player2, &player1Pos, &player2Pos, boardLength, boardHeight, board);

    // Print the initial state of the board
    printBoard(boardLength, boardHeight, board);

    while (strcmp(status, "in progress") == 0) {
        // Player 1's turn
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Player 1, roll the dice.\n");
        letsRoll();  // Assuming this function simulates dice roll output
        if (playerMovement(&player1Pos, boardLength, boardHeight, board)) {
            strcpy(status, "Player 1 has won!");
            printf("%s\n", status);
        }

        // Update and print the board after Player 1's move
        updateBoard(player1, player2, &player1Pos, &player2Pos, boardLength, boardHeight, board);
        printBoard(boardLength, boardHeight, board);

        if (strcmp(status, "in progress") != 0) {
            break;
        }

        // Player 2's turn
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Player 2, roll the dice.\n");
        letsRoll();  // Assuming this function simulates dice roll output
        if (playerMovement(&player2Pos, boardLength, boardHeight, board)) {
            strcpy(status, "Player 2 has won!");
            printf("%s\n", status);
        }

        // Update and print the board after Player 2's move
        updateBoard(player1, player2, &player1Pos, &player2Pos, boardLength, boardHeight, board);
        printBoard(boardLength, boardHeight, board);
    }

    return 0;
}
