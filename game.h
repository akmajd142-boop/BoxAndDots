#ifndef GAME_H
#define GAME_H

#include "board.h"
void initBoard(Board *b);
int isValidMove(const Board *b, int r1, int c1, int r2, int c2);
int makeMove(Board *b, int r1, int c1, int r2, int c2);
int isGameOver(const Board *b);

char getWinner(const Board *b);

#endif 
