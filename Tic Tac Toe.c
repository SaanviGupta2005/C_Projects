#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 3

char board[BOARD_SIZE][BOARD_SIZE];

void initBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    printf("  1   2   3\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            printf("  --|---|--\n");
        }
    }
    printf("\n");
}

bool makeMove(int row, int col, char mark) {
    if (row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE) {
        return false;
    }
    if (board[row - 1][col - 1] != ' ') {
        return false;
    }
    board[row - 1][col - 1] = mark;
    return true;
}

bool checkWin(char mark) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        // check rows
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) {
            return true;
        }
        // check columns
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark) {
            return true;
        }
    }
    // check diagonals
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) {
        return true;
    }
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) {
        return true;
    }
    return false;
}

int main() {
    initBoard();
    int row, col, moveCount = 0;
    char player = 'X';
    bool gameOver = false;
    printf("Tic Tac Toe Game\n");
    printf("================\n");
    printBoard();

    while (!gameOver) {
        printf("Player %c's turn. Enter row and column: ", player);
        scanf("%d %d", &row, &col);
        if (makeMove(row, col, player)) {
            moveCount++;
            printBoard();
            if (checkWin(player)) {
                printf("Player %c wins!\n", player);
                gameOver = true;
            } else if (moveCount == BOARD_SIZE * BOARD_SIZE) {
                printf("Game ends in a draw.\n");
                gameOver = true;
            } else {
                player = (player == 'X') ? 'O' : 'X';
            }
        } else {
            printf("Invalid move. Please try again.\n");
        }
    }

    return 0;
}
