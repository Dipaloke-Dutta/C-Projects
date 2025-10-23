#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define COMPUTER 'O'
#define PLAYER 'X'

char board[3][3]; // Board for the game


void resetBoard();
void displayBoard();
void playermove();
void computermove();
int checkFreeSpace();
char checkWinner();
void printWinner(char winner);

int main() {
    char winner, play_again;
    int response;
    srand(time(0)); //Moved to main for random seed value everytime

    do {
        winner = ' ';
        //Change start
		do{
        // Prompt the user to choose who goes first
        printf("Press\n1 to move first\n2 to move last\n");
        scanf("%d", &response);
    }while(response<1 || response>2);

    // Change end
		resetBoard();
        // Ensure board is displayed immediately
        displayBoard();

        while (winner == ' ' && checkFreeSpace() > 0) {
            if (response == 1) { // Player moves first
                playermove();
                displayBoard();
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpace() == 0) break;

                computermove();
                displayBoard();
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpace() == 0) break;
            } else { // Computer moves first
                computermove();
                displayBoard();
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpace() == 0) break;

                playermove();
                displayBoard();
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpace() == 0) break;
            }
        }

        // Display the final result
        printWinner(winner);

        printf("WOULD YOU LIKE TO PLAY AGAIN? (Y/N): ");
        scanf(" %c", &play_again);
        play_again = toupper(play_again);

    } while (play_again == 'Y' || play_again == 'y' );

    return 0;
}

void resetBoard() {
    int i,j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void displayBoard() {
    printf("\n %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

int checkFreeSpace() {
    int freeSpace = 9,i,j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (board[i][j] != ' ') freeSpace--;
    return freeSpace;
}

void playermove() {
    int x, y;
    do {
        printf("Enter The Row (1-3):");
    	scanf("%d", &x);
    	x--;
    	printf("\nEnter The Column (1-3):");
    	scanf("%d",&y);
    	y--;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ') {
            board[x][y] = PLAYER;
            break;
        } else {
            printf("Invalid Move. Try Again.\n");
        }
    } while (1);
}

char checkWinner() {
    int i;
    for (i = 0; i < 3; i++) { // Check rows
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }
    for (i = 0; i < 3; i++) { // Check columns
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) return board[0][0]; // Check diagonals
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) return board[0][2];

    return ' ';
}

void computermove() {
    int x, y;
    int i,j;
    //srand(time(0));

    // 1. Try to win
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                if (checkWinner() == COMPUTER) return;
                board[i][j] = ' '; // Undo move
            }
        }
    }

    // 2. Try to block the player from winning
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = PLAYER;
                if (checkWinner() == PLAYER) {
                    board[i][j] = COMPUTER;
                    return;
                }
                board[i][j] = ' '; // Undo move
            }
        }
    }

    // 3. Pick a random available spot
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');

    board[x][y] = COMPUTER;
}

void printWinner(char winner) {
    if (winner == PLAYER)
        printf("YOU WIN!\n");
    else if (winner == COMPUTER)
        printf("YOU LOSE!\n");
    else
        printf("IT'S A TIE!\n");
}

