#include <stdio.h>
#include "game.h"
#include "display.h"
#include "input.h"

int main(void) {
    Board board;
    initBoard(&board);

    int r1, c1, r2, c2;

    while (!isGameOver(&board)) {
        printBoard(&board);

        printf("Player %c's turn. Enter the row and "
               "column of the first dot (e.g., A0 -> 0 0) "
               "and second dot:\n", board.currentPlayer);

        if (!readMove(&r1, &c1, &r2, &c2)) {
            printf("Input ended. Exiting game.\n");
            return 1;
        }

        if (!isValidMove(&board, r1, c1, r2, c2)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        int claimed = makeMove(&board, r1, c1, r2, c2);

        if (claimed > 0) {
            printf("%d box(es) claimed!\n", claimed);
        }

        printScores(&board);
    }

    printBoard(&board);
    printScores(&board);

    char winner = getWinner(&board);

    if (winner == 'T') {
        printf("Game over! It's a tie!\n");
    } else {
        printf("Game over! Player %c wins!\n", winner);
    }

    return 0;
}
