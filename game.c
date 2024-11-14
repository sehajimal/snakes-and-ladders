#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


struct Slot {
    char symbol[5];
    int index;
    // L for ladder, S for snake, N for nothing
    char type;
};

int rollDice() {
    int roll = rand() % 6 + 1;
    printf("You rolled a %d\n", roll);
    return roll;
}


void generateBoard (char p1[], char p2[], int *pos1, int *pos2, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]) {
    //struct Slot board[boardLength][boardHeight];
    int count;

    // Generating the board
    for (int i = boardLength - 1; i >= 0; i--) { 
        for (int j = 0; j < boardHeight; j++) {
            if (i % 2 == 0) { 
                count = i * boardHeight + (boardHeight - j);
            } else {          
                count = i * boardHeight + j + 1;
            }

            // Set the index for each slot
            board[i][j].index = count;

            // Assign type and symbol based on conditions
            //! REFACTOR TO WORK WITH DYNAMIC SIZED BOARDS
                // maybe generate 3 snakes and 3 ladders all the time
            if (count == 81 || count == 80 || count == 61 || count == 60 ||
                count == 36 || count == 25 || count == 16 || count == 69 || 
                count == 52 || count == 49 || count == 32) {
                board[i][j].type = 'L';                     // Ladder
                snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "|-|");
            } else if (count == 21 || count == 19 || count == 3 || 
                       count == 94 || count == 86 || count == 76 || count == 64) {
                board[i][j].type = 'S';                     // Snake
                snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "~");
            } else {
                board[i][j].type = 'N';                     // Regular slot
                snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "%d", count);
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
/*
void updateBoard (char p1[], char p2[], int *pos1, int *pos2, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]) {
    //char board[boardLength][boardHeight][5];
    //int count;

    // adding player position to board
    for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            int boardPosition = (i % 2 == 0) ? (i * boardLength + (boardHeight - j)) : (i * boardLength + j + 1);
            if (boardPosition == *pos1 && boardPosition == *pos2) {
                strcpy(board[i][j], "B");
            } else if (boardPosition == *pos1) {
                strcpy(board[i][j], p1);
            } else if (boardPosition == *pos2) {
                strcpy(board[i][j], p2);
            }
        }
    }
    #include <string.h>
*/
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
                if (board[i][j].type == 'L') {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "|-|");  // Ladder
                } else if (board[i][j].type == 'S') {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "~");    // Snake
                } else {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "%d", board[i][j].index); // Default slot with index
                }
            }
        }
    }
}

//! REFACTOR TO WORK WITH DYNAMIC SNAKE AND LADDER PALCEMENT
int playerMovement(int *pos) {
    int roll = rollDice();
    *pos += roll;

    // Check for snakes and ladders
    if (*pos == 60) {
        *pos = 81;
    }
    else if (*pos == 16) {
        *pos = 36;
    }
    else if (*pos == 32) {
        *pos = 69;
    }
    else if (*pos == 21) {
        *pos = 3;
    }
    else if (*pos == 94) {
        *pos = 64;
    }

    // Check if player has won
    if (*pos == 100) {
        return 1;  // Player has won
    }
    return 0;  // Game continues
}


void letsRoll() {
    while(1){
        char button;
        printf("Press 'R' to roll the dice.\n");
        scanf(" %c", &button);
        if(button == 'r'){
            printf("rolling dice...\n");
            break;
        }
        else {
            printf("Invalid command.\n");
        }
    }
}


int main() {
    printf("Let's play Snakes and Ladders!\n");
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
        printf("Player 1, roll the dice.\n");
        letsRoll();  // Assuming this function simulates dice roll output
        if (playerMovement(&player1Pos)) {
            strcpy(status, "Player 1 has won!");
            printf("%s\n", status);
        }

        // Update and print the board after Player 1's move
        updateBoard(player1, player2, &player1Pos, &player2Pos, boardLength, boardHeight, board);
        printBoard(boardLength, boardHeight, board);

        if (strcmp(status, "in progress") != 0) break;

        // Player 2's turn
        printf("Player 2, roll the dice.\n");
        letsRoll();  // Assuming this function simulates dice roll output
        if (playerMovement(&player2Pos)) {
            strcpy(status, "Player 2 has won!");
            printf("%s\n", status);
        }

        // Update and print the board after Player 2's move
        updateBoard(player1, player2, &player1Pos, &player2Pos, boardLength, boardHeight, board);
        printBoard(boardLength, boardHeight, board);
    }

    return 0;
}

