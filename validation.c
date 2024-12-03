#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("       Welcome to the Epic Snakes & Ladders Game!         \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Below is a list of instructions to win the game of snakes and ladders's\n\n");

    printf(" Rules:\n");
    printf("1. This is a two-player game, where each player takes turns rolling the dice.\n");
    printf("2. Your goal is to be the first to reach the end of the board.\n");
    printf("3. Type 'r' and press enter to roll the dice\n");
    printf("4. Landing on a snakes head marked with a '$' will send you sliding back down the board.\n");
    printf("5. Land on the bottom of ladders |-| to help you climb up and skip ahead!\n");
    printf("\n");

    printf(" Symbols:\n");
    printf(" *   : Neutral spot. Simply a safe spot.\n");
    printf(" |-| : Ladder. Will allow you to climb up!\n");
    printf(" $   : Snake. This will pull you down.\n");
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

void usage() {
    printf("Usage: ./game [boardLength] [boardHeight]\n");
    printf("boardLength and boardHeight must be integers between 8 and 30.\n");
    printf("The 2nd and 3rd arguments represent the dimensions of a custom board. For example, if './game 10 12' is entered, the game will be played on a 10 x 12 board.");
}

void error() {
    fprintf(stderr, "Error: Invalid input. Use --help for usage instructions.\n");
}

int isInputValid(const char *str, int *result) {
    char *endptr;
    long value = strtol(str, &endptr, 10); // convert string to long
    if (*endptr != '\0' || endptr == str) {
        return 0; // not a valid integer
    }
    if (value < 8 || value > 30) {
        return 0; // out of range
    }
    *result = (int)value;
    return 1; // valid
}