#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>  // For toupper

using namespace std;

#define COMPUTER 'O'
#define PLAYER 'X'

class TicTacToe {
private:
    vector<vector<char>> board;

public:
    TicTacToe() {
        board.resize(3, vector<char>(3, ' '));
    }

    void resetBoard() {
        for (auto &row : board)
            fill(row.begin(), row.end(), ' ');
    }

    void displayBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
            if (i < 2) cout << "---|---|---\n";
        }
        cout << "\n";
    }

    int checkFreeSpace() {
        int freeSpace = 9;
        for (const auto &row : board)
            for (char cell : row)
                if (cell != ' ') freeSpace--;
        return freeSpace;
    }

    void playermove() {
        int x, y;
        while (true) {
            cout << "Enter The Row (1-3): ";
            cin >> x;
            cout << "Enter The Column (1-3): ";
            cin >> y;
            x--; y--; // Convert to 0-based index
            
            if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ') {
                board[x][y] = PLAYER;
                break;
            } else {
                cout << "Invalid Move. Try Again.\n";
            }
        }
    }

    void computermove() {
        int x, y;

        // 1. Try to win
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    if (checkWinner() == COMPUTER) return;
                    board[i][j] = ' '; // Undo move
                }
            }
        }

        // 2. Try to block the player from winning
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
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

    char checkWinner() {
        for (int i = 0; i < 3; i++) { // Check rows
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
                return board[i][0];
        }
        for (int i = 0; i < 3; i++) { // Check columns
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
                return board[0][i];
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) return board[0][0]; // Check diagonals
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) return board[0][2];

        return ' ';
    }

    void printWinner(char winner) {
        if (winner == PLAYER)
            cout << "YOU WIN!\n";
        else if (winner == COMPUTER)
            cout << "YOU LOSE!\n";
        else
            cout << "IT'S A TIE!\n";
    }
};

int main() {
    TicTacToe game;
    char winner, play_again;
    int response;
    srand(time(0)); // Seed random number generator

    do {
        winner = ' ';
        do {
            cout << "Press\n1 to move first\n2 to move last\n";
            cin >> response;

            if (cin.fail() || (response != 1 && response != 2)) { // Input validation
                cin.clear(); // Clear error flag
                cin.ignore(10000, '\n'); // Discard invalid input
                cout << "Invalid input. Enter 1 or 2.\n";
            }

        } while (response < 1 || response > 2);

        game.resetBoard();
        game.displayBoard();

        while (winner == ' ' && game.checkFreeSpace() > 0) {
            if (response == 1) { // Player moves first
                game.playermove();
                game.displayBoard();
                winner = game.checkWinner();
                if (winner != ' ' || game.checkFreeSpace() == 0) break;

                game.computermove();
                game.displayBoard();
                winner = game.checkWinner();
                if (winner != ' ' || game.checkFreeSpace() == 0) break;
            } else { // Computer moves first
                game.computermove();
                game.displayBoard();
                winner = game.checkWinner();
                if (winner != ' ' || game.checkFreeSpace() == 0) break;

                game.playermove();
                game.displayBoard();
                winner = game.checkWinner();
                if (winner != ' ' || game.checkFreeSpace() == 0) break;
            }
        }

        game.printWinner(winner);

        cout << "WOULD YOU LIKE TO PLAY AGAIN? (Y/N): ";
        cin >> play_again;
        play_again = toupper(play_again);
        cin.ignore();  // Ensure buffer is cleared

    } while (play_again == 'Y');

    return 0;
}
