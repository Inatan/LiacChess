#include<stdio.h>
#include"board.h"

BITBOARD InitBitBoard(BITBOARD *BitBoard)
{
    BitBoard->allyBoard=NULL_BOARD;
    BitBoard->enemyBoard=NULL_BOARD;
    BitBoard->allyPawnBoard=NULL_BOARD;
    BitBoard->enemyPawnBoard=NULL_BOARD;
    BitBoard->allyBishops[0]=NULL_BOARD;
    BitBoard->allyBishops[1]=NULL_BOARD;
    BitBoard->enemyBishops[0]=NULL_BOARD;
    BitBoard->enemyBishops[1]=NULL_BOARD;
    BitBoard->allyRooks[0]=NULL_BOARD;
    BitBoard->allyRooks[1]=NULL_BOARD;
    BitBoard->enemyRooks[0]=NULL_BOARD;
    BitBoard->enemyRooks[1]=NULL_BOARD;
    BitBoard->allyPawns[0]=NULL_BOARD;
    BitBoard->allyPawns[1]=NULL_BOARD;
    BitBoard->allyPawns[2]=NULL_BOARD;
    BitBoard->allyPawns[3]=NULL_BOARD;
    BitBoard->allyPawns[4]=NULL_BOARD;
    BitBoard->allyPawns[5]=NULL_BOARD;
    BitBoard->allyPawns[6]=NULL_BOARD;
    BitBoard->allyPawns[7]=NULL_BOARD;
    BitBoard->enemyPawns[0]=NULL_BOARD;
    BitBoard->enemyPawns[1]=NULL_BOARD;
    BitBoard->enemyPawns[2]=NULL_BOARD;
    BitBoard->enemyPawns[3]=NULL_BOARD;
    BitBoard->enemyPawns[4]=NULL_BOARD;
    BitBoard->enemyPawns[5]=NULL_BOARD;
    BitBoard->enemyPawns[6]=NULL_BOARD;
    BitBoard->enemyPawns[7]=NULL_BOARD;
    return *BitBoard;
}


BITBOARD BoardParser(int whoMoves, char Board[64])
{
    BITBOARD BitBoard;
    BitBoard= InitBitBoard(&BitBoard);
    if(whoMoves==1)
    {
        BitBoard=BoardParserBrancos(Board,&BitBoard);
    }

    if(whoMoves==-1)
    {
        BitBoard=BoardParserPretos(Board,&BitBoard);
    }
    DumpBitBoard(BitBoard);
    return BitBoard;
}

BITBOARD BoardParserPretos(char board[64],BITBOARD *BitBoard)
{
    int i,countAPawn=0,countEPawn=0,countABishop=0,countEBishop=0,countARook=0,countERook=0;
    for(i=0; i<BOARD_SIZE; i++)
    {
        if(board[i]=='r')
        {
            BitBoard->allyRooks[countARook]=pow(2,i);
            BitBoard->allyBoard+=pow(2,i);
            countARook++;
        }
        if(board[i]=='R')
        {
            BitBoard->enemyRooks[countERook]=pow(2,i);
            BitBoard->enemyBoard+=pow(2,i);
            countERook++;
        }
        if(board[i]=='b')
        {
            BitBoard->allyBishops[countABishop]=pow(2,i);
            BitBoard->allyBoard+=pow(2,i);
            countABishop++;
        }
        if(board[i]=='B')
        {
            BitBoard->enemyBishops[countEBishop]=pow(2,i);
            BitBoard->enemyBoard+=pow(2,i);
            countEBishop++;
        }
        if(board[i]=='p')
        {
            BitBoard->allyPawns[countAPawn]=pow(2,i);
            BitBoard->allyBoard+=pow(2,i);
            BitBoard->allyPawnBoard+=pow(2,i);
            countAPawn++;
        }
        if(board[i]=='P')
        {
            BitBoard->enemyBoard+=pow(2,i);
            BitBoard->enemyPawns[countEPawn]=pow(2,i);
            BitBoard->enemyPawnBoard+=pow(2,i);
            countEPawn++;
        }
    }
    return *BitBoard;
}

BITBOARD BoardParserBrancos(char board[64],BITBOARD *BitBoard)
{
    int i,countAPawn=0,countEPawn=0,countABishop=0,countEBishop=0,countARook=0,countERook=0;
    for(i=0; i<BOARD_SIZE; i++)
    {
        if(board[i]=='R')
        {
            BitBoard->allyBoard+=pow(2,i);
            BitBoard->allyRooks[countARook]=pow(2,i);
            countARook++;
        }
        if(board[i]=='r')
        {
            BitBoard->enemyBoard+=pow(2,i);
            BitBoard->enemyRooks[countERook]=pow(2,i);
            countERook++;
        }
        if(board[i]=='B')
        {
            BitBoard->allyBoard+=pow(2,i);
            BitBoard->allyBishops[countABishop]=pow(2,i);
            countABishop++;
        }
        if(board[i]=='b')
        {

            BitBoard->enemyBoard+=pow(2,i);
            BitBoard->enemyBishops[countEBishop]=pow(2,i);
            countEBishop++;
        }
        if(board[i]=='P')
        {
            BitBoard->allyBoard+=pow(2,i);
            BitBoard->allyPawns[countAPawn]=pow(2,i);
            BitBoard->allyPawnBoard+=pow(2,i);
            countAPawn++;
        }
        if(board[i]=='p')
        {
            BitBoard->enemyBoard+=pow(2,i);
            BitBoard->enemyPawns[countEPawn]=pow(2,i);
            BitBoard->enemyPawnBoard+=pow(2,i);
            countEPawn++;
        }
    }

    return *BitBoard;
}
void DumpBitBoard(BITBOARD BitBoard)
{
    int i;
    printf("Ally Board:\n");
    print_board(BitBoard.allyBoard);
    printf("Ally Bishop:\n");
    for(i=0; i<BISHOP_NUM; i++)
    {
        printf("\n");
        print_board(BitBoard.allyBishops[i]);
    }
    printf("Ally Rook:\n");
    for(i=0; i<ROOK_NUM; i++)
    {
        print_board(BitBoard.allyRooks[i]);
        printf("\n");
    }
    printf("Ally Pawns Board:\n");
    print_board(BitBoard.allyPawnBoard);
    printf("Ally Pawns:\n");
    for(i=0; i<PAWN_NUM; i++)
    {
       print_board(BitBoard.allyPawns[i]);
       printf("\n");
    }
    printf("Enemy Board:\n");
    print_board(BitBoard.enemyBoard);
    printf("Enemy Bishop:\n");
    for(i=0; i<BISHOP_NUM; i++)
    {
         print_board(BitBoard.enemyBishops[i]);
         printf("\n");
    }

    printf("Enemy Rook:\n");
    for(i=0; i<ROOK_NUM; i++)
    {
        print_board(BitBoard.enemyRooks[i]);
        printf("\n");
    }
    printf("Enemy Pawns Board:\n");
    print_board(BitBoard.enemyPawnBoard);
    printf("Enemy Pawns:\n");
    for(i=0; i<PAWN_NUM; i++)
    {
        print_board(BitBoard.enemyPawns[i]);
        printf("\n");
    }


}

void print_board(U64 board)
{
    int i,j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(board & msb)
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
            board = board << 1;
        }
        printf("\n");
    }
}
