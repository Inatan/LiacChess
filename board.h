#include<stdio.h>
#include<math.h>
#define NULL_BOARD 0x0000000000000000
#define TRUE 1
#define FALSE !TRUE
#define BRANCAS 1
#define PRETAS -1 // RACISMO
#define BOARD_SIZE 64
#define PAWN_NUM 8
#define ROOK_NUM 2
#define BISHOP_NUM 2
#define msb 0x8000000000000000

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

typedef unsigned long long U64;

typedef struct a_board
{
    U64 enemyBoard;
    U64 allyBoard;
    U64 enemyPawnBoard;
    U64 allyPawnBoard;
    U64 enemyPawns[PAWN_NUM];
    U64 allyPawns[PAWN_NUM];
    U64 enemyBishops[BISHOP_NUM];
    U64 allyBishops[BISHOP_NUM];
    U64 enemyRooks[ROOK_NUM];
    U64 allyRooks[ROOK_NUM];
}BITBOARD;

void DumpBitBoard(BITBOARD BitBoard);
void print_board(U64 board);
BITBOARD InitBitBoard(BITBOARD *BitBoard);
BITBOARD BoardParserBrancos(char board[64],BITBOARD *BitBoard);
BITBOARD BoardParserPretos(char board[64],BITBOARD *BitBoard);
BITBOARD BoardParser(int whoMoves, char Board[64]);
