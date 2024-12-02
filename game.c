#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "slot.h"

void printBoard(int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]);

int rollDice() {
    int roll = rand() % 6 + 1;
    printf("You rolled a %d\n", roll);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    return roll;
}


void generateBoard (char p1[], char p2[], int *pos1, int *pos2, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]){
    int count;

    // iterating over the board (2D array of Slots) in correct order and setting the index and default type symbol 
    for (int i = boardLength - 1; i >= 0; i--) {
        for (int j = 0; j < boardHeight; j++) {

            // calculating index (count)
            if (i % 2 == 0) {
                count = i * boardHeight + (boardHeight - j);
            }
            else {
                count = i * boardHeight + j + 1;   
            }
            // assigning default symbol and types
            board[i][j].index = count;
            board[i][j].type = 'N';
            snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "*");
        }
    }

    // randomly selecting the number of laddesr (between 2 and 5)
    int numLadders = (rand() % 4) + 2;
    int totalCells = boardHeight * boardLength;

    // adding ladders
    while (numLadders > 0){

        // randomly selecting ladder starting position
        int ladderStartPosition;
        do {
            ladderStartPosition = (rand() % (totalCells - 10)) + 6;
        } while (ladderStartPosition < 0 || ladderStartPosition >= totalCells);

        // iteraring over board to find index which was selected as the ladder start position
        for (int i = 0; i < boardLength; i++){
            for (int j = 0; j < boardHeight; j++){
                if (board[i][j].index == ladderStartPosition){

                    // adjusting that position to be of type 'A' (ladder start) and have ladder symbol
                    board[i][j].type = 'A';
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "|-|");
                }
            }
        }
        numLadders--;
    }

    // ladders are 4 slots long
    int ladderSize = 3;
    int length = 0;

    for (int i = 0; i < boardLength; i++){
        for (int j = 0; j < boardHeight; j++){

            // checking if there is space for the ladder to go upwards
            if (board[i][j].type == 'A' && (i + ladderSize < boardLength)){
                length = 1;
                while (ladderSize >= length){

                    // adding to directly above slots the type of 'L' and correct symbol
                    board[i + length][j].type = 'L';
                    snprintf(board[i + length][j].symbol, sizeof(board[i + length][j].symbol), "|-|");
                    length++;
                }
            }

            // otherwise check if there is enough space for the ladder to go downwards
            else if (board[i][j].type == 'A' && (i - ladderSize >= 0)){

                // adding to directly below slots the type 'L' and correct symbol
                board[i][j].type = 'L';
                length = 1;
                while (ladderSize > length){
                    board[i - length][j].type = 'L';
                    snprintf(board[i - length][j].symbol, sizeof(board[i - length][j].symbol), "|-|");
                    length++;
                }

                // making the lowest slot in this ladder of type 'A' (start of ladder)
                board[i - length][j].type = 'A';
                snprintf(board[i - length][j].symbol, sizeof(board[i - length][j].symbol), "|-|");
            }
        }
    }

    // randomy generating number of snakes
    int numSnakes = rand() % 2;

    while (numSnakes > 0){
        int snakeStartPosition;
        do {
            snakeStartPosition = (rand() % (totalCells - 10)) + 6;
        } while (snakeStartPosition < 0 || snakeStartPosition >= totalCells);

        for (int i = 0; i < boardLength; i++){
            for (int j = 0; j < boardHeight; j++){
                if (board[i][j].index == snakeStartPosition && board[i][j].type != 'A' && board[i][j].type != 'L'){
                    board[i][j].type = 'C';
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "~");
                }
            }
        }
        numSnakes--;
    }

    int snakeSize = 3;
    length = 1;

    for (int i = 0; i < boardLength; i++) {
        for (int j = 0; j < boardHeight; j++) {
            if (board[i][j].type == 'C' && (i + snakeSize < boardLength) && (j + snakeSize < boardHeight)){ //slide from top right
                board[i][j].type = 'S';
                length = 1;
                while (length < snakeSize){
                    board[i + length][j + length].type = 'S';
                    snprintf(board[i + length][j + length].symbol, sizeof(board[i + length][j + length].symbol), "~");
                    length++;
                }
                board[i + length][j + length].type = 'W';
                snprintf(board[i + length][j + length].symbol, sizeof(board[i + length][j + length].symbol), "~");
            }
            else if (board[i][j].type == 'C' && (i - snakeSize >= 0) && (j + snakeSize < boardHeight)){ //slide towards bottom right
                length = 1;
                while (length <= snakeSize){
                    board[i - length][j + length].type = 'S';
                    snprintf(board[i - length][j + length].symbol, sizeof(board[i - length][j + length].symbol), "~");
                    length++;
                }
            }
            else if (board[i][j].type == 'C' && (i + snakeSize < boardLength) && (j - snakeSize >= 0)){ //slide from top left
                board[i][j].type = 'S';
                length = 1;
                while (length < snakeSize){
                    board[i + length][j - length].type = 'S';
                    snprintf(board[i + length][j - length].symbol, sizeof(board[i + length][j - length].symbol), "~");
                    length++;
                }
                board[i + length][j - length].type = 'M';
                snprintf(board[i + length][j - length].symbol, sizeof(board[i + length][j - length].symbol), "~");
            }
            else if (board[i][j].type == 'C'){ //slide towards bottom left
                length = 1;
                while (length <= snakeSize){
                    board[i - length][j - length].type = 'S';
                    snprintf(board[i - length][j - length].symbol, sizeof(board[i - length][j - length].symbol), "~");
                    length++;
                }
            }
        }
    }
<<<<<<< HEAD
=======

    // for (int i = boardLength - 1; i >= 0; i--) {
    //     for (int j = 0; j < boardHeight; j++) {
    //         printf("%c", board[i][j].type);  // Print each slot's symbol with a width of 4
    //     }
    //     printf("\n");  // Newline after each row
    // }
>>>>>>> 8e9ebda34ae8b446df6001f0dce0dc144a270da6
}


void printBoard(int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]) {
    for (int i = boardLength - 1; i >= 0; i--) {
        for (int j = 0; j < boardHeight; j++) {
            printf("%-4s", board[i][j].symbol);  // Print each slot's symbol with a width of 4
        }
        printf("\n");  // Newline after each row
    }
}

void updateBoard(char p1[], char p2[], int *pos1, int *pos2, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]) {
    // Update the board with players' positions
    for (int i = boardLength - 1; i >= 0; i--) {
        for (int j = 0; j < boardHeight; j++) {
            // Check if the player's position matches the slot's index
            if (board[i][j].index == *pos1 && board[i][j].index == *pos2) {
                // Both players on the same slot
                snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "B");  // B for both players
            } else if (board[i][j].index == *pos1) {
                // Player 1's position
                snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "%s", p1);
            } else if (board[i][j].index == *pos2) {
                // Player 2's position
                snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "%s", p2);
            } else {
                // Reset symbol to its original state based on slot type
                if (board[i][j].type == 'L' || board[i][j].type == 'A') {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "|-|");  // Ladder
                }

                else if(board[i][j].type == 'C' || board[i][j].type == 'S' || board[i][j].type == 'M' || board[i][j].type == 'W'){
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "~");  // Snake
                }

                else {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "*"); // Default slot with index
                }
            }
        }
    }
}

int playerMovement(int *pos, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]) {
    int roll = rollDice();
    *pos += roll;

    int winningIndex = boardLength * boardHeight;
    if (*pos >= winningIndex) 
    {
        *pos = winningIndex; 
        return 1; 
    }

    for (int i = 0; i < boardLength; i++) {
        for (int j = 0; j < boardHeight; j++) {
            if(board[i][j].index ==  *pos){
                if(board[i][j].type == 'A'){
                    *pos = board[i+3][j].index;
                }
                else if(board[i][j].type == 'W'){
                    *pos = board[i-3][j-3].index;
                }
                else if(board[i][j].type == 'M'){
                    *pos = board[i-3][j+3].index;
                }
                else if((board[i][j].type == 'C') && (board[i-1][j-1].type == 'S')){
                    *pos = board[i-3][j-3].index;
                }
                else if((board[i][j].type == 'C') && (board[i-1][j+1].type == 'S')){
                    *pos = board[i-3][j+3].index;
                }
            }
        }
    }
    return 0;
}



void letsRoll() {
    while(1){
        char button;
        printf("type 'r' and press enter to roll the dice.\n");
        scanf(" %c", &button);
        if(button == 'r'){
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("rolling dice...\n");
            break;
        }
        else {
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Invalid command.\n");
        }
    }
<<<<<<< HEAD
}

// Function for when user requests help

void help() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("       Welcome to the Epic Snakes & Ladders Game!         \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Below is a list of instructions to win the game of snakes and ladders's\n\n");

    printf(" Rules:\n");
    printf("1. This is a two-player game, where each player takes turns rolling the dice.\n");
    printf("2. Your goal is to be the first to reach the end of the board.\n");
    printf("3. Type 'r' and press enter to roll the dice\n");
    printf("4. Landing on a snakes head marked with a '#' will send you sliding back down the board.\n");
    printf("5. Land on the bottom of ladders |*| to help you climb up and skip ahead!\n");
    printf("\n");

    printf(" Symbols:\n");
    printf(" *   : Neutral spot. Simply a safe spot.\n");
    printf(" |*| : Ladder. Will allow you to climb up!\n");
    printf(" #   : Snake. This will pull you down.\n");
    printf(" P1  : Player 1's current position.\n");
    printf(" P2  : Player 2's current position.\n");
    printf(" B   : Both players on the same slot.\n");
    printf("\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf(" How to Win:\n");
    printf(" * The first player to reach the final spot (Slot 100) is the champion!\n");
    printf(" * Best of luck!\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/*int main(int argc, char *argv[]) {
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

        if (strcmp(status, "in progress") != 0) break;

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
}*/

=======
}
>>>>>>> 8e9ebda34ae8b446df6001f0dce0dc144a270da6
