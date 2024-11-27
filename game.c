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
            if (board[i][j].index == *pos) {
                if (board[i][j].type == 'S') {
                    printf("You landed on a snake! Sliding down...\n");

                    // Move down the snake
                    while ((i - 1) >= 0) { // Ensure we stay within bounds
                        if ((j - 1) >= 0 && board[i - 1][j - 1].type == 'S') {
                            i--; // Move up a row
                            j--; // Move left
                        } else if ((j + 1) < boardHeight && board[i - 1][j + 1].type == 'S') {
                            i--; // Move up a row
                            j++; // Move right
                        } else {
                            break; // No more snake segments in this direction
                        }
                    }

                    *pos = board[i][j].index; // Update player's position to the final snake segment
                }

                // If it's a ladder
                else if (board[i][j].type == 'L') {
                    printf("You found a ladder! Climbing up...\n");
                    while (i + 1 < boardLength && board[i+1][j].type == 'L') {
                        i++;
                    }
                    *pos = board[i][j].index; // Update position to the top of the ladder
                }
                return 0; // Game continues
            }
        }
    }

    // If not on a snake or ladder, position remains unchanged
    return 0;
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

//function for when user does help flag
void help() 
{
    printf("Usage: game\n");
    printf("        This snakes and ladders game is played from the command line and the\n\n");
    printf("Playing the game example:\n");
    printf(" {game}   This will convert the integers from the range -3 to 3 to base 2.\n");
    printf(" Can use 2 flags {-b Base} and {-r Start finish}\n");
    printf(" the flag {-r Start finish} will allow 'convert' to output a range of conversions of long integers [START,FINISH]. Without it it will use standard input\n");
    printf(" The {-b Base} flag tells 'convert' which base to do the conversion to. And not using it will automatically convert to base 16\n");
}


int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--help") == 0) 
    {
        help();
        return 0;
    }

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
}

