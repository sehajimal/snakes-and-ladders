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
                snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "*");
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
                if (board[i][j].type == 'L') {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "|-|");  // Ladder
                } else if (board[i][j].type == 'S') {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "~");    // Snake
                } else {
                    snprintf(board[i][j].symbol, sizeof(board[i][j].symbol), "*"); // Default slot with index
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
        printf("type 'r' and press enter to roll the dice.\n");
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
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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

//function for when user does help flag
void help() 
{
    printf("Usage: convert [-b BASE] [-r START FINISH]\n");
    printf("        1 < BASE < 37\n");
    printf("        START and FINISH are long integers\n\n");
    printf("Testing the utility example:\n");
    printf(" {convert -b 2 -r -3 3}   This will convert the integers from the range -3 to 3 to base 2.\n");
    printf(" Can use 2 flags {-b Base} and {-r Start finish}\n");
    printf(" the flag {-r Start finish} will allow 'convert' to output a range of conversions of long integers [START,FINISH]. Without it it will use standard input\n");
    printf(" The {-b Base} flag tells 'convert' which base to do the conversion to. And not using it will automatically convert to base 16\n");
}

