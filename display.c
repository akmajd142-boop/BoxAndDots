#include <stdio.h>
#include "display.h"

void printBoard(const Board *b) {
    printf("  ");
    for (int c = 0; c < DOT_COLS; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < DOT_ROWS; r++) {
        printf("%d ", r);

        // Print dots and horizontal lines.
        for (int c = 0; c < DOT_COLS; c++) {
            printf(".");

            if (c < DOT_COLS - 1) {
                printf("%c", b->hLines[r][c] ==
                       LINE_DRAWN ? '-' : ' ');
            }
        }
        printf("\n");

        // Print vertical lines and box owners.
        if (r < BOX_ROWS) {
            printf("  ");

            for (int c = 0; c < DOT_COLS; c++) {
                printf("%c", b->vLines[r][c] ==
                       LINE_DRAWN ? '|' : ' ');

                if (c < BOX_COLS) {
                    printf("%c", b->boxes[r][c]);
                }
            }
            printf("\n");
        }
    }
}

void printScores(const Board *b) {
    for (int i = 0; i < 50; i++) {
        printf("*");
    }
    printf("\n");

    printf("Player A score: %d\n", b->scoreA);
    printf("Player B score: %d\n", b->scoreB);

    for (int i = 0; i < 50; i++) {
        printf("*");
    }
    printf("\n");
}
