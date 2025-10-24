#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 4

typedef struct {
    int hasWumpus;
    int hasPit;
    int hasGold;
    int hasBreeze;
    int hasStench;
    int hasBeenVisited;
} Room;

Room cave[GRID_SIZE][GRID_SIZE];
int playerRow = 0, playerCol = 0;
int isGameOver = 0;

void setupCave() {
    srand(time(0));

    int wumpusRow = rand() % GRID_SIZE;
    int wumpusCol = rand() % GRID_SIZE;
    while (wumpusRow == 0 && wumpusCol == 0) {
        wumpusRow = rand() % GRID_SIZE;
        wumpusCol = rand() % GRID_SIZE;
    }
    cave[wumpusRow][wumpusCol].hasWumpus = 1;

    if (wumpusRow > 0) cave[wumpusRow-1][wumpusCol].hasStench = 1;
    if (wumpusRow < GRID_SIZE-1) cave[wumpusRow+1][wumpusCol].hasStench = 1;
    if (wumpusCol > 0) cave[wumpusRow][wumpusCol-1].hasStench = 1;
    if (wumpusCol < GRID_SIZE-1) cave[wumpusRow][wumpusCol+1].hasStench = 1;

    int totalPits = 0;
    while (totalPits < 3) {
        int pitRow = rand() % GRID_SIZE;
        int pitCol = rand() % GRID_SIZE;
        if ((pitRow != 0 || pitCol != 0) && !cave[pitRow][pitCol].hasWumpus && !cave[pitRow][pitCol].hasPit) {
            cave[pitRow][pitCol].hasPit = 1;
            if (pitRow > 0) cave[pitRow-1][pitCol].hasBreeze = 1;
            if (pitRow < GRID_SIZE-1) cave[pitRow+1][pitCol].hasBreeze = 1;
            if (pitCol > 0) cave[pitRow][pitCol-1].hasBreeze = 1;
            if (pitCol < GRID_SIZE-1) cave[pitRow][pitCol+1].hasBreeze = 1;
            totalPits++;
        }
    }

    int goldRow = rand() % GRID_SIZE;
    int goldCol = rand() % GRID_SIZE;
    while ((goldRow == 0 && goldCol == 0) || cave[goldRow][goldCol].hasPit || cave[goldRow][goldCol].hasWumpus) {
        goldRow = rand() % GRID_SIZE;
        goldCol = rand() % GRID_SIZE;
    }
    cave[goldRow][goldCol].hasGold = 1;
}

void showPercepts() {
    Room *currentRoom = &cave[playerRow][playerCol];
    if (currentRoom->hasStench) printf("You smell something foul nearby.\n");
    if (currentRoom->hasBreeze) printf("You feel a breeze...\n");
    if (currentRoom->hasGold) {
        printf("Shiny GOLD! You win!\n");
        isGameOver = 1;
    }
}

void movePlayer(char direction) {
    int newRow = playerRow;
    int newCol = playerCol;

    switch (direction) {
        case 'w': newRow--; break;
        case 's': newRow++; break;
        case 'a': newCol--; break;
        case 'd': newCol++; break;
        default: printf("Invalid input.\n"); return;
    }

    if (newRow < 0 || newRow >= GRID_SIZE || newCol < 0 || newCol >= GRID_SIZE) {
        printf("You hit a wall!\n");
        return;
    }

    playerRow = newRow;
    playerCol = newCol;
    Room *currentRoom = &cave[playerRow][playerCol];
    currentRoom->hasBeenVisited = 1;

    if (currentRoom->hasPit) {
        printf("Oh no! You fell into a pit! Game over.\n");
        isGameOver = 1;
    } else if (currentRoom->hasWumpus) {
        printf("Chomp! The Wumpus got you. Game over.\n");
        isGameOver = 1;
    } else {
        showPercepts();
    }
}

int main() {
    setupCave();
    cave[0][0].hasBeenVisited = 1;

    printf("Welcome to the Wumpus World!\nMove with W (up), A (left), S (down), D (right).\n");

    while (!isGameOver) {
        char playerMove;
        printf("\nYour move (w/a/s/d): ");
        scanf(" %c", &playerMove);
        movePlayer(playerMove);
    }

    return 0;
}
