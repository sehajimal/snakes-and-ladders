#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int rollDice() {
    return rand() % 6 + 1;
}


void generateBoard(char p1[], char p2[], int *pos1, int *pos2) {
    char board[10][10][5];
    int count = 1;
    for(int i = 1; i<=10; i++){
        for(int j = 1; j<=10; j++){
            if(count == 40 || count == 30 || count == 20 || count == 10){
                sprintf(board[i-1][j-1], "%s", "|-|");
            }
            else if(count == 82 || count == 72 || count == 62){
                sprintf(board[i-1][j-1], "%s", "|-|");
            }
            else if(count == 17 || count == 27 || count == 37 || count == 47){
                sprintf(board[i-1][j-1], "%s", "|-|");
            }
            else if(count == 29 || count == 18 || count == 7){
                sprintf(board[i-1][j-1], "%s", "~");
            }
            else if(count == 93 || count == 84 || count == 75 || count == 66){
                sprintf(board[i-1][j-1], "%s", "~");
            }
            else {
                sprintf(board[i-1][j-1], "%d", count);
            }    
            count++;
            }
        }
    
    int newCount = 1;
    for(int i = 1; i<=10; i++){
        for(int j = 9; j<=0; j--){
            newCount++;
           if((newCount == *pos1) && (newCount == *pos2)) {
            strcpy(board[i-1][j-1], "B");
           }
           else if(newCount == *pos1){
            strcpy(board[i-1][j-1], p1);
           }
           else if(newCount == *pos2){
            strcpy(board[i-1][j-1], p2);
           }
        }
    }
   
    for(int i = 9; i>=0; i--){
        for(int j = 9; j>=0; j--){
            printf("%-4s", board[i][j]);
        }
        printf("\n");
    }
}

int player1Movement(char state[], int *pos1){
    int roll = rollDice();
    srand(time(0));
    *pos1+=roll;


    if(*pos1 == 10) {
        *pos1 = 40;
    }
    else if(*pos1 == 62) {
        *pos1 = 82;
    }
    else if(*pos1 == 17) {
        *pos1 = 47;
    }
    else if(*pos1 == 29) {
        *pos1 = 7;
    }
    else if(*pos1 == 93) {
        *pos1 = 66;
    }


    if(*pos1 == 100){
        return 1;
    }
    return 0;
}


int player2Movement(char state[], int *pos2){
    int roll = rollDice();
    *pos2+=roll;


    if(*pos2 == 10) {
        *pos2 = 40;
    }
    else if(*pos2 == 62) {
        *pos2 = 82;
    }
    else if(*pos2 == 17) {
        *pos2 = 47;
    }
    else if(*pos2 == 29) {
        *pos2 = 7;
    }
    else if(*pos2 == 93) {
        *pos2 = 66;
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


    char status[100] = "in progress";
    int player1Pos = 0;
    int player2Pos = 0;


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

