#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int rollDice() {
    int roll = rand() % 6 + 1;
    printf("You rolled a %d\n", roll);
    return roll;
}


void generateBoard(char p1[], char p2[], int *pos1, int *pos2) {
    char board[10][10][5];
    int count;

    for (int i = 9; i >= 0; i--) { 
        for (int j = 0; j < 10; j++) {
            if (i % 2 == 0) { 
                count = i * 10 + (9 - j) + 1;
            } else {          
                count = i * 10 + j + 1;
            }

            if (count == 81 || count == 80 || count == 61 || count == 60 ||
                count == 36 || count == 25 || count == 16 || count == 69 || 
                count == 52 || count == 49 || count == 32) {
                sprintf(board[i][j], "|-|");
            } else if (count == 21 || count == 19 || count == 3 || 
                       count == 94 || count == 86 || count == 76 || count == 64) {
                sprintf(board[i][j], "~");
            } else {
                sprintf(board[i][j], "%d", count);
            }
        }
    }

    for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            int boardPosition = (i % 2 == 0) ? (i * 10 + (9 - j) + 1) : (i * 10 + j + 1);
            if (boardPosition == *pos1 && boardPosition == *pos2) {
                strcpy(board[i][j], "B");
            } else if (boardPosition == *pos1) {
                strcpy(board[i][j], p1);
            } else if (boardPosition == *pos2) {
                strcpy(board[i][j], p2);
            }
        }
    }

    for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            printf("%-4s", board[i][j]);
        }
        printf("\n");
    }
}


int player1Movement(char state[], int *pos1){
    int roll = rollDice();
    srand(time(0));
    *pos1+=roll;


    if(*pos1 == 60) {
        *pos1 = 81;
    }
    else if(*pos1 == 16) {
        *pos1 = 36;
    }
    else if(*pos1 == 32) {
        *pos1 = 69;
    }
    else if(*pos1 == 21) {
        *pos1 = 3;
    }
    else if(*pos1 == 94) {
        *pos1 = 64;
    }


    if(*pos1 == 100){
        return 1;
    }
    return 0;
}


int player2Movement(char state[], int *pos2){
    int roll = rollDice();
    *pos2+=roll;


    if(*pos2 == 60) {
        *pos2 = 81;
    }
    else if(*pos2 == 16) {
        *pos2 = 36;
    }
    else if(*pos2 == 32) {
        *pos2 = 69;
    }
    else if(*pos2 == 21) {
        *pos2 = 3;
    }
    else if(*pos2 == 94) {
        *pos2 = 64;
    }


    if(*pos2 == 100){
        return 1;
    }
    return 0;
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


    char player1[5] = "P1";
    char player2[5] = "P2";


    generateBoard(player1, player2, &player1Pos, &player2Pos);

    while(strcmp(status, "in progress") == 0){
        printf("Player 1 roll the dice.\n");
        letsRoll();
        if(player1Movement(status, &player1Pos)){
            strcpy(status, "Player 1 has won!");
            printf("%s\n", status);
        }
        generateBoard(player1, player2, &player1Pos, &player2Pos);
        printf("Player 2 roll the dice.\n");
        letsRoll();
        if(player2Movement(status, &player2Pos)){
            strcpy(status, "Player 2 has won!");
            printf("%s\n", status);
        }
        generateBoard(player1, player2, &player1Pos, &player2Pos);
    }


    return 0;
}

