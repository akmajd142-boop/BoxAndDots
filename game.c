#include <stdlib.h>
#include "game.h"

void initBoard(Board *b) {
    for (int r = 0; r < DOT_ROWS; r++)
        for (int c = 0; c < DOT_COLS - 1; c++)
            b->hLines[r][c] = LINE_EMPTY;

    for (int r = 0; r < DOT_ROWS - 1; r++)
        for (int c = 0; c < DOT_COLS; c++)
            b->vLines[r][c] = LINE_EMPTY;

    for (int r = 0; r < BOX_ROWS; r++)
        for (int c = 0; c < BOX_COLS; c++)
            b->boxes[r][c] = NO_OWNER;

    b->scoreA = 0;
    b->scoreB = 0;
    b->currentPlayer = PLAYER_A;
}

static int inBounds(int r, int c) {
    return r >= 0 && r < DOT_ROWS && c >= 0 && c < DOT_COLS;
}

static int isBoxComplete(const Board *b, int r, int c) {
    return b->hLines[r][c] == LINE_DRAWN &&
           b->hLines[r + 1][c] == LINE_DRAWN &&
           b->vLines[r][c] == LINE_DRAWN &&
           b->vLines[r][c + 1] == LINE_DRAWN;
}

int isValidMove(const Board *b, int r1, int c1, int r2, int c2) {
    if (!inBounds(r1, c1) || !inBounds(r2, c2))
        return 0;

    if (abs(r1 - r2) + abs(c1 - c2) != 1)
        return 0;

    if (r1 == r2) {
        int c = (c1 < c2) ? c1 : c2;
        return b->hLines[r1][c] == LINE_EMPTY;
    }

    int r = (r1 < r2) ? r1 : r2;
    return b->vLines[r][c1] == LINE_EMPTY;
}

static int claimIfComplete(Board *b, int r, int c) {
    if (r < 0 || r >= BOX_ROWS || c < 0 || c >= BOX_COLS)
        return 0;

    if (b->boxes[r][c] != NO_OWNER || !isBoxComplete(b, r, c))
        return 0;

    b->boxes[r][c] = b->currentPlayer;
    if (b->currentPlayer == PLAYER_A)
        b->scoreA++;
    else
        b->scoreB++;
    return 1;
}

int makeMove(Board *b, int r1, int c1, int r2, int c2) {
    int claimed = 0;

    if (r1 == r2) {
        int c = (c1 < c2) ? c1 : c2;
        b->hLines[r1][c] = LINE_DRAWN;
        claimed += claimIfComplete(b, r1 - 1, c);
        claimed += claimIfComplete(b, r1, c);
    } else {
        int r = (r1 < r2) ? r1 : r2;
        b->vLines[r][c1] = LINE_DRAWN;
        claimed += claimIfComplete(b, r, c1 - 1);
        claimed += claimIfComplete(b, r, c1);
    }

    if (claimed == 0)
        b->currentPlayer = (b->currentPlayer == PLAYER_A) ? PLAYER_B : PLAYER_A;

    return claimed;
}

int isGameOver(const Board *b) {
    return b->scoreA + b->scoreB == TOTAL_BOXES;
}

char getWinner(const Board *b) {
    if (b->scoreA > b->scoreB)
        return PLAYER_A;
    if (b->scoreB > b->scoreA)
        return PLAYER_B;
    return 'T';
}
