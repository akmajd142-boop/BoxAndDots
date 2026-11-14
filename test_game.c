#include <stdio.h>
#include "game.h"

static int passed = 0;
static int failed = 0;

static void check(int condition, const char *name) {
    if (condition) {
        printf("PASS: %s\n", name);
        passed++;
    } else {
        printf("FAIL: %s\n", name);
        failed++;
    }
}

static void testInit(void) {
    Board b;
    initBoard(&b);
    check(b.scoreA == 0 && b.scoreB == 0, "init: scores are 0");
    check(b.currentPlayer == PLAYER_A, "init: player A starts");
    check(b.hLines[0][0] == LINE_EMPTY && b.vLines[3][5] == LINE_EMPTY, "init: lines empty");
    check(b.boxes[3][4] == NO_OWNER, "init: boxes unowned");
    check(!isGameOver(&b), "init: game not over");
}

static void testValidMoves(void) {
    Board b;
    initBoard(&b);
    check(isValidMove(&b, 0, 0, 0, 1), "valid: horizontal move");
    check(isValidMove(&b, 0, 0, 1, 0), "valid: vertical move");
    check(isValidMove(&b, 0, 1, 0, 0), "valid: reversed dot order");
    check(isValidMove(&b, 4, 4, 4, 5), "valid: bottom-right edge");
    check(!isValidMove(&b, 0, 0, 1, 1), "invalid: diagonal");
    check(!isValidMove(&b, 0, 0, 0, 2), "invalid: dots too far apart");
    check(!isValidMove(&b, 0, 0, 0, 0), "invalid: same dot");
    check(!isValidMove(&b, -1, 0, 0, 0), "invalid: negative row");
    check(!isValidMove(&b, 4, 5, 5, 5), "invalid: row out of range");
    check(!isValidMove(&b, 0, 5, 0, 6), "invalid: column out of range");

    makeMove(&b, 0, 0, 0, 1);
    check(!isValidMove(&b, 0, 0, 0, 1), "invalid: line already drawn");
    check(!isValidMove(&b, 0, 1, 0, 0), "invalid: line already drawn (reversed)");
}

static void testTurnSwitch(void) {
    Board b;
    initBoard(&b);
    int claimed = makeMove(&b, 0, 0, 0, 1);
    check(claimed == 0, "turn: no box claimed");
    check(b.currentPlayer == PLAYER_B, "turn: switches to B");
    makeMove(&b, 2, 2, 2, 3);
    check(b.currentPlayer == PLAYER_A, "turn: switches back to A");
}

static void testCompleteOneBox(void) {
    Board b;
    initBoard(&b);
    makeMove(&b, 0, 0, 0, 1);
    makeMove(&b, 1, 0, 1, 1);
    makeMove(&b, 0, 0, 1, 0);
    char player = b.currentPlayer;
    int claimed = makeMove(&b, 0, 1, 1, 1);
    check(claimed == 1, "box: one box claimed");
    check(b.boxes[0][0] == player, "box: owned by the player who closed it");
    check(b.currentPlayer == player, "box: same player plays again");
    check((player == PLAYER_A ? b.scoreA : b.scoreB) == 1, "box: score increased");
}

static void testCompleteTwoBoxes(void) {
    Board b;
    initBoard(&b);
    makeMove(&b, 0, 0, 0, 1);
    makeMove(&b, 1, 0, 1, 1);
    makeMove(&b, 0, 0, 1, 0);
    makeMove(&b, 0, 1, 0, 2);
    makeMove(&b, 1, 1, 1, 2);
    makeMove(&b, 0, 2, 1, 2);
    char player = b.currentPlayer;
    int claimed = makeMove(&b, 0, 1, 1, 1);
    check(claimed == 2, "double: two boxes claimed");
    check(b.boxes[0][0] == player && b.boxes[0][1] == player, "double: both boxes owned");
    check((player == PLAYER_A ? b.scoreA : b.scoreB) == 2, "double: score increased by 2");
    check(b.currentPlayer == player, "double: same player plays again");
}

static void testFullGame(void) {
    Board b;
    initBoard(&b);
    for (int r = 0; r < DOT_ROWS; r++)
        for (int c = 0; c < DOT_COLS - 1; c++)
            makeMove(&b, r, c, r, c + 1);
    for (int r = 0; r < DOT_ROWS - 1; r++)
        for (int c = 0; c < DOT_COLS; c++)
            if (isValidMove(&b, r, c, r + 1, c))
                makeMove(&b, r, c, r + 1, c);
    check(isGameOver(&b), "full: game over after all lines");
    check(b.scoreA + b.scoreB == TOTAL_BOXES, "full: all 20 boxes claimed");
    char w = getWinner(&b);
    char expected = b.scoreA > b.scoreB ? PLAYER_A : (b.scoreB > b.scoreA ? PLAYER_B : 'T');
    check(w == expected, "full: winner matches scores");
}

static void testWinner(void) {
    Board b;
    initBoard(&b);
    b.scoreA = 11; b.scoreB = 9;
    check(getWinner(&b) == PLAYER_A, "winner: A");
    b.scoreA = 8; b.scoreB = 12;
    check(getWinner(&b) == PLAYER_B, "winner: B");
    b.scoreA = 10; b.scoreB = 10;
    check(getWinner(&b) == 'T', "winner: tie");
}

int main(void) {
    testInit();
    testValidMoves();
    testTurnSwitch();
    testCompleteOneBox();
    testCompleteTwoBoxes();
    testFullGame();
    testWinner();
    printf("\n%d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;
}
