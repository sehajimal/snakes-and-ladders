#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "slot.h"

void printBoard(int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]);

int rollDice() {
    int roll = rand() % 6 + 1; //Generate a number on a valid, 6-side dice
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

    while (numSnakes > 0){ //While there remains a number of snakes, determine a random start position of the snakes.
        int snakeStartPosition;
        do {
            snakeStartPosition = (rand() % (totalCells - 10)) + 6; //Ensures no snakes end up too close to the start and end positions
        } while (snakeStartPosition < 0 || snakeStartPosition >= totalCells);

        for (int i = 0; i < boardLength; i++){ //Iterate through board and assign the snake start positions as type 'C'
            for (int j = 0; j < boardHeight; j++){
                if (board[i][j].index == snakeStartPosition && board[i][j].type != 'A' && board[i][j].type != 'L'){
                    board[i][j].type = 'C';
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "$"); //All parts of a snake are represented with '$'
                }
            }
        }
        numSnakes--;
    }

    int snakeSize = 3; //All snakes will be a total of 4 slots long (including the start)
    length = 1;

    for (int i = 0; i < boardLength; i++) { //Iterate through board to assign all positions after the snake starting spot as type 'S'
        for (int j = 0; j < boardHeight; j++) {
            if (board[i][j].type == 'C' && (i + snakeSize < boardLength) && (j + snakeSize < boardHeight)){ //slide from top right
                board[i][j].type = 'S';
                length = 1;
                while (length < snakeSize){
                    board[i + length][j + length].type = 'S'; //move up diagonally towards top right
                    snprintf(board[i + length][j + length].symbol, sizeof(board[i + length][j + length].symbol), "$");
                    length++; //Counts 3 more spots from the star
                }
                board[i + length][j + length].type = 'W'; //After the top of the snake has been reached, reassign the top position to be the new start of the snake ('W' for top right)
                snprintf(board[i + length][j + length].symbol, sizeof(board[i + length][j + length].symbol), "$");
            }
            else if (board[i][j].type == 'C' && (i - snakeSize >= 0) && (j + snakeSize < boardHeight)){ //slide towards bottom right
                length = 1;
                while (length <= snakeSize){
                    board[i - length][j + length].type = 'S'; //Reassign snake positions below the start of the snake when going towards bottom right
                    snprintf(board[i - length][j + length].symbol, sizeof(board[i - length][j + length].symbol), "$");
                    length++;
                }
            }
            else if (board[i][j].type == 'C' && (i + snakeSize < boardLength) && (j - snakeSize >= 0)){ //slide from top left
                board[i][j].type = 'S';
                length = 1;
                while (length < snakeSize){ 
                    board[i + length][j - length].type = 'S'; //move up diagonally towards top left
                    snprintf(board[i + length][j - length].symbol, sizeof(board[i + length][j - length].symbol), "$");
                    length++;
                }
                board[i + length][j - length].type = 'M'; //After the top of the snake has been reached, reassign the top position to be the new start of the snake ('M' for top left)
                snprintf(board[i + length][j - length].symbol, sizeof(board[i + length][j - length].symbol), "$");
            }
            else if (board[i][j].type == 'C'){ //slide towards bottom left
                length = 1;
                while (length <= snakeSize){
                    board[i - length][j - length].type = 'S'; //Reassign snake positions below the start of the snake when going towards bottom left
                    snprintf(board[i - length][j - length].symbol, sizeof(board[i - length][j - length].symbol), "$");
                    length++;
                }
            }
        }
    }
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
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "$");  // Snake
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
    *pos += roll; //add value from dice roll to previus player position

    int winningIndex = boardLength * boardHeight; //locates final position on board
    if (*pos >= winningIndex) 
    {
        *pos = winningIndex; //assign winning condition to player's position if end of board is reached
        return 1; 
    }

    for (int i = 0; i < boardLength; i++) {
        for (int j = 0; j < boardHeight; j++) {
            if(board[i][j].index ==  *pos){ //Iterate through board until current position of current player is reached
                if(board[i][j].type == 'A'){ //If position is start of a ladder, move up 3 rows
                    *pos = board[i+3][j].index;
                }
                else if(board[i][j].type == 'W'){ //If position is start of snake that slides from top right, slide down left 3 times
                    *pos = board[i-3][j-3].index;
                }
                else if(board[i][j].type == 'M'){ //If position is start of snake that starts from top left, slide down right 3 times
                    *pos = board[i-3][j+3].index;
                }
                else if((board[i][j].type == 'C') && (board[i-1][j-1].type == 'S')){ //If position is start of snake with a snake segment to its bottom left, slide down left 3 times
                    *pos = board[i-3][j-3].index;
                }
                else if((board[i][j].type == 'C') && (board[i-1][j+1].type == 'S')){ //If position is start of snake with a snake segment to its bottom right, slide down right 3 times
                    *pos = board[i-3][j+3].index;
                }
            }
        }
    }
    return 0;
}



void letsRoll() {
    while(1){ //keep prompting for a roll until user enters 'r'
        char button;
        printf("type 'r' and press enter to roll the dice.\n");
        scanf(" %c", &button); //store user input for prompt
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
}
