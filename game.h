#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Define the Slot structure
struct Slot {
    char symbol[5];
    int index;
    // L for ladder, S for snake, N for nothing
    char type;
};

// Function prototypes
void printBoard(int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]);
int rollDice();
void generateBoard(char p1[], char p2[], int *pos1, int *pos2, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]);
void updateBoard(char p1[], char p2[], int *pos1, int *pos2, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]);
int playerMovement(int *pos, int boardLength, int boardHeight, struct Slot board[boardLength][boardHeight]);
void letsRoll();