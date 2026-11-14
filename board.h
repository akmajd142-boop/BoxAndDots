#ifndef BOARD_H
#define BOARD_H
#define DOT_ROWS 5     
#define DOT_COLS 6    
#define BOX_ROWS 4     
#define BOX_COLS 5     
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS)   

#define LINE_EMPTY 0
#define LINE_DRAWN 1

#define NO_OWNER ' '
#define PLAYER_A 'A'
#define PLAYER_B 'B'

typedef struct {
    int hLines[DOT_ROWS][DOT_COLS - 1];    
    int vLines[DOT_ROWS - 1][DOT_COLS];     
    char boxes[BOX_ROWS][BOX_COLS];         
    int scoreA;
    int scoreB;
    char currentPlayer;                    
} Board;

#endif /* BOARD_H */
