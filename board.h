#include<stdio.h>
#define TRUE 1
#define FALSE !TRUE
#define BRANCAS 1
#define PRETAS -1 // RACISMO
#define BOARD_SIZE 64

typedef struct Board
{
    char board[BOARD_SIZE];
    int fiftymoves;
    int winner;
    int draw;
    int badmove;
    int blackInfractions;
    int whiteInfractions;
    int whoMoves;
    int enpassant[2];
} BOARD;

