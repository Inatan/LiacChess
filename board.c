#include<stdio.h>
#include"board.h"
#define UNIVERSE            0xffffffffffffffff
#define FIRST_LINE          0xff00000000000000
#define LAST_LINE           0x00000000000000ff
#define LOSE                -500
#define WIN                 500
#define RIGHTMOST_COLUMN    0x0101010101010101
#define LEFTMOST_COLUMN     0x8080808080808080

void debug(int depth, float newValue)
{
    //fflush(stdin);
    if(depth == 3)
    {
        printf("newValue: %.f \n", newValue);
    }

}
int max_move(BITBOARD board, int depth)
{
    U64 mask;
    depth--;
    if(board.allyPawnBoard == 0)
        return LOSE;
    if(board.enemyPawnBoard == 0)
        return WIN;
    if((board.enemyPawnBoard & LAST_LINE) || (board.enemyPawnBoard & FIRST_LINE))
    {
        return LOSE;
    }
    if((board.allyPawnBoard & LAST_LINE) || (board.allyPawnBoard & FIRST_LINE))
    {
        return WIN;
    }

    if(depth <= 0)
    {
        int e;
        int eval = 0;
        for(e=0;e<PAWN_NUM;e++)
        {
            if(board.allyPawns[e])
            {
                eval+= 10;
                if(whoMoves == BRANCAS)
                {
                    eval = eval + log2l(board.allyPawns[e]) * 0.125;
                }
                else
                {
                    eval = eval + ( 64 - log2l(board.allyPawns[e])) * 0.125;
                }
            }

            //printf("log amigo: %d", log2l(board.allyPawns[e]));
            //printf("log inimigo: %d", log2l(board.enemyPawns[e]));
            if(board.enemyPawns[e])
            {
                eval-= 20;
                if(whoMoves == BRANCAS)
                {
                    eval = eval - ( 64 - log2l(board.enemyPawns[e]))* 0.125;
                }
                else
                {
                    eval = eval - log2l(board.enemyPawns[e])* 0.125;
                }
            }
        }
        if(eval >= WIN)
        {
            eval = WIN - 1;
        }
        if(eval <= LOSE)
        {
            eval = LOSE + 1;
        }
        return eval;
    }
    BITBOARD bestMove;
    BITBOARD newmove;
    float bestMoveValue = LOSE - 100;

    int newValue;
    //int matchPoint;
    int i;
    for(i=0;i<PAWN_NUM;i++)
    {
        if(board.allyPawns[i]) //lembrando de se apagar se foi comido
        {
            if(whoMoves == BRANCAS)
            {
                if((board.allyPawns[i]<<9 & board.enemyBoard) && !(board.allyPawns[i] & LEFTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.allyPawns[i] = board.allyPawns[i]<<9;

                    newmove.allyPawnBoard = newmove.allyPawnBoard ^ board.allyPawns[i];
                    newmove.allyPawnBoard = newmove.allyPawnBoard | newmove.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard ^ board.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard | newmove.allyPawns[i];



                    mask = UNIVERSE ^ newmove.allyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;

                    //matchPoint = 0;
                    newValue = 0;
                    newValue = min_move(newmove, depth);

                    if( newValue >= bestMoveValue )
                    {
                        debug(depth,newValue);
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                    }

                }
                if(!((board.allyPawns[i]<<8 & board.enemyBoard) || (board.allyPawns[i]<<8 & board.allyBoard)))
                {
                    newmove = board;
                    newmove.allyPawns[i] = board.allyPawns[i]<<8;

                    newmove.allyPawnBoard = newmove.allyPawnBoard ^ board.allyPawns[i];
                    newmove.allyPawnBoard = newmove.allyPawnBoard | newmove.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard ^ board.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard | newmove.allyPawns[i];


                    newValue = 0;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);
                    if( newValue >= bestMoveValue )
                    {
                        debug(depth,newValue);
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                    }
                }
                if((board.allyPawns[i]<<7 & board.enemyBoard) && !(board.allyPawns[i] & RIGHTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.allyPawns[i] = board.allyPawns[i]<<7;

                    newmove.allyPawnBoard = newmove.allyPawnBoard ^ board.allyPawns[i];
                    newmove.allyPawnBoard = newmove.allyPawnBoard | newmove.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard ^ board.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard | newmove.allyPawns[i];

                    mask = UNIVERSE ^ newmove.allyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = 0;
                    newValue = min_move(newmove, depth);

                    if( newValue >= bestMoveValue )
                    {
                        debug(depth,newValue);
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                    }
                }
            }
            else
            {
                if((board.allyPawns[i]>>9 & board.enemyBoard) && !(board.allyPawns[i] & RIGHTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.allyPawns[i] = board.allyPawns[i]>>9;

                    newmove.allyPawnBoard = newmove.allyPawnBoard ^ board.allyPawns[i];
                    newmove.allyPawnBoard = newmove.allyPawnBoard | newmove.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard ^ board.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard | newmove.allyPawns[i];
                    mask = UNIVERSE ^ newmove.allyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;

                    newValue = 0;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);
                    if( newValue >= bestMoveValue )
                    {
                        debug(depth,newValue);
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                    }
                }
                if(!((board.allyPawns[i]>>8 & board.enemyBoard) || (board.allyPawns[i]>>8 & board.allyBoard)))
                {
                    newmove = board;
                    newmove.allyPawns[i] = board.allyPawns[i]>>8;

                    newmove.allyPawnBoard = newmove.allyPawnBoard ^ board.allyPawns[i];
                    newmove.allyPawnBoard = newmove.allyPawnBoard | newmove.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard ^ board.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard | newmove.allyPawns[i];

                    newValue = 0;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);
                    //printf("New value: %d\n", newValue);
                     //printf("Best move value: %d\n", bestMoveValue);
                    if( newValue >= bestMoveValue )
                    {
                        debug(depth,newValue);
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                    }
                }
                if((board.allyPawns[i]>>7 & board.enemyBoard) && !(board.allyPawns[i] & LEFTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.allyPawns[i] = board.allyPawns[i]>>7;

                    newmove.allyPawnBoard = newmove.allyPawnBoard ^ board.allyPawns[i];
                    newmove.allyPawnBoard = newmove.allyPawnBoard | newmove.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard ^ board.allyPawns[i];
                    newmove.allyBoard = newmove.allyBoard | newmove.allyPawns[i];
                    mask = UNIVERSE ^ newmove.allyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;

                    newValue = 0;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);
                    if( newValue >= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                }
            }
        }
    }

    //rooks
    int r;
    newmove = board;
    for(r=0;r<ROOK_NUM;r++)
    {
        if(board.allyRooks[r])
        {
            i = 1;
            while(!(board.allyRooks[r]<<8*i & (board.allyBoard)) && board.allyRooks[r]<<8*i)
            {
                newmove = board;
                newmove.allyRooks[r] = board.allyRooks[r]<<8*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyRooks[r];
                newmove.allyBoard = newmove.allyBoard | newmove.allyRooks[r];

                if(newmove.allyRooks[r] & newmove.enemyBoard)
                {

                    mask = UNIVERSE ^ newmove.allyRooks[r];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                }
            }
            i = 1;
            while(!(board.allyRooks[r]>>8*i & (board.allyBoard)) && board.allyRooks[r]>>8*i)
            {
                newmove = board;
                newmove.allyRooks[r] = board.allyRooks[r]>>8*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyRooks[r];
                newmove.allyBoard = newmove.allyBoard | newmove.allyRooks[r];

                if(newmove.allyRooks[r] & newmove.enemyBoard)
                {

                    mask = UNIVERSE ^ newmove.allyRooks[r];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                    debug(depth,newValue);
                }
            }
            i = 1;
            while(!(board.allyRooks[r]<<1*i & (RIGHTMOST_COLUMN | board.allyBoard)) && board.allyRooks[r]<<1*i)
            {
                newmove = board;
                newmove.allyRooks[r] = board.allyRooks[r]<<1*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyRooks[r];
                newmove.allyBoard = newmove.allyBoard | newmove.allyRooks[r];

                if(newmove.allyRooks[r] & newmove.enemyBoard)
                {
                    mask = UNIVERSE ^ newmove.allyRooks[r];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                    debug(depth,newValue);
                }
            }
            i = 1;
            while(!(board.allyRooks[r]>>1*i & (LEFTMOST_COLUMN | board.allyBoard)) && board.allyRooks[r]>>1*i)
            {
                newmove = board;
                newmove.allyRooks[r] = board.allyRooks[r]>>1*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyRooks[r];
                newmove.allyBoard = newmove.allyBoard | newmove.allyRooks[r];

                if(newmove.allyRooks[r] & newmove.enemyBoard)
                {
                    mask = UNIVERSE ^ newmove.allyRooks[r];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                    debug(depth,newValue);
                }
            }
        }

    }

    int b;
    newmove = board;
    for(b=0;b<BISHOP_NUM;b++)
    {
        if(board.allyBishops[b])
        {
            i = 1;
            while(!(board.allyBishops[b]<<9*i & (RIGHTMOST_COLUMN| board.allyBoard)) && board.allyBishops[b]<<9*i)
            {
                newmove = board;
                newmove.allyBishops[b] = board.allyBishops[b]<<9*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyBishops[b];
                newmove.allyBoard = newmove.allyBoard | newmove.allyBishops[b];

                if(newmove.allyBishops[b] & newmove.enemyBoard)
                {

                    mask = UNIVERSE ^ newmove.allyBishops[b];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                    debug(depth,newValue);
                }
            }
            i = 1;
            while(!(board.allyBishops[b]>>9*i & (LEFTMOST_COLUMN  | board.allyBoard)) && board.allyBishops[b]>>9*i)
            {
                newmove = board;
                newmove.allyBishops[b] = board.allyBishops[b]>>9*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyBishops[b];
                newmove.allyBoard = newmove.allyBoard | newmove.allyBishops[b];

                if(newmove.allyBishops[b] & newmove.enemyBoard)
                {

                    mask = UNIVERSE ^ newmove.allyBishops[b];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                    debug(depth,newValue);
                }
            }
            i = 1;
            while(!(board.allyBishops[b]<<7*i & ( LEFTMOST_COLUMN | board.allyBoard)) && board.allyBishops[b]<<7*i)
            {
                newmove = board;
                newmove.allyBishops[b] = board.allyBishops[b]<<7*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyBishops[b];
                newmove.allyBoard = newmove.allyBoard | newmove.allyBishops[b];

                if(newmove.allyBishops[b] & newmove.enemyBoard)
                {

                    mask = UNIVERSE ^ newmove.allyBishops[b];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                    debug(depth,newValue);
                }
            }
            i = 1;
            while(!(board.allyBishops[b]>>7*i & (RIGHTMOST_COLUMN | board.allyBoard)) && board.allyBishops[b]>>7*i)
            {
                newmove = board;
                newmove.allyBishops[b] = board.allyBishops[b]>>7*(i);

                newmove.allyBoard = newmove.allyBoard ^ board.allyBishops[b];
                newmove.allyBoard = newmove.allyBoard | newmove.allyBishops[b];

                if(newmove.allyBishops[b] & newmove.enemyBoard)
                {

                    mask = UNIVERSE ^ newmove.allyBishops[b];
                    newmove.enemyBoard = newmove.enemyBoard & mask;
                    newmove.enemyBishops[0] = newmove.enemyBishops[0] & mask;
                    newmove.enemyBishops[1] = newmove.enemyBishops[1] & mask;
                    newmove.enemyRooks[0] = newmove.enemyRooks[0] & mask;
                    newmove.enemyRooks[1] = newmove.enemyRooks[1] & mask;
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard & mask;
                    newmove.enemyPawns[0] = newmove.enemyPawns[0] & mask;
                    newmove.enemyPawns[1] = newmove.enemyPawns[1] & mask;
                    newmove.enemyPawns[2] = newmove.enemyPawns[2] & mask;
                    newmove.enemyPawns[3] = newmove.enemyPawns[3] & mask;
                    newmove.enemyPawns[4] = newmove.enemyPawns[4] & mask;
                    newmove.enemyPawns[5] = newmove.enemyPawns[5] & mask;
                    newmove.enemyPawns[6] = newmove.enemyPawns[6] & mask;
                    newmove.enemyPawns[7] = newmove.enemyPawns[7] & mask;
                    newValue = min_move(newmove, depth);
                    //debug(depth,newValue);

                    if( newValue > bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue - 0.01;
                        debug(depth,newValue);
                    }
                    break;
                }
                i++;

                newValue = 0;
                newValue = min_move(newmove, depth);

                if( newValue > bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue - 0.01;
                    debug(depth,newValue);
                }
            }
        }

    }

    finalBoard = bestMove;
    printf("Depth %d Best %f\n",depth,bestMoveValue);
    return bestMoveValue;

}


int min_move(BITBOARD board, int depth)
{
    U64 mask;
    depth--;
    if(board.allyPawnBoard == 0)
        return LOSE;
    if(board.enemyPawnBoard == 0)
        return WIN;
    if((board.enemyPawnBoard & LAST_LINE) || (board.enemyPawnBoard & FIRST_LINE))
    {
        return LOSE;
    }
    if((board.allyPawnBoard & LAST_LINE) || (board.allyPawnBoard & FIRST_LINE))
    {
        return WIN;
    }
    if(depth <= 0)
    {
        int e;
        int eval = 0;
        for(e=0;e<PAWN_NUM;e++)
        {
            if(board.allyPawns[e])
            {
                eval+= 10;
                if(whoMoves == BRANCAS)
                {
                    eval = eval + log2l(board.allyPawns[e]) * 0.125;
                }
                else
                {
                    eval = eval + ( 64 - log2l(board.allyPawns[e])) * 0.125;
                }
            }

            //printf("log amigo: %d", log2l(board.allyPawns[e]));
            //printf("log inimigo: %d", log2l(board.enemyPawns[e]));
            if(board.enemyPawns[e])
            {
                eval-= 20;
                if(whoMoves == BRANCAS)
                {
                    eval = eval - ( 64 - log2l(board.enemyPawns[e]))* 0.125;
                }
                else
                {
                    eval = eval - log2l(board.enemyPawns[e])* 0.125;
                }
            }
        }
        if(eval >= WIN)
        {
            eval = WIN - 1;
        }
        if(eval <= LOSE)
        {
            eval = LOSE + 1;
        }
        return eval;
    }
    BITBOARD bestMove;
    BITBOARD newmove;
    int bestMoveValue = WIN + 100;

    int newValue;
    //int matchPoint;
    int i;
    for(i=0;i<PAWN_NUM;i++)
    {
        if(board.enemyPawns[i]) //lembrando de se apagar se foi comido
        {
            if(whoMoves == PRETAS)
            {
                if((board.enemyPawns[i]<<9 & board.allyBoard) && !(board.enemyPawns[i] & LEFTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.enemyPawns[i] = board.enemyPawns[i]<<9;

                    newmove.enemyPawnBoard = newmove.enemyPawnBoard ^ board.enemyPawns[i];
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard | newmove.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard ^ board.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard | newmove.enemyPawns[i];

                    mask = UNIVERSE ^ newmove.enemyPawns[i];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;

                    //matchPoint = 0;
                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                }
                if(!((board.enemyPawns[i]<<8 & board.enemyBoard) || (board.enemyPawns[i]<<8 & board.allyBoard)))
                {
                    newmove = board;
                    newmove.enemyPawns[i] = board.enemyPawns[i]<<8;

                    newmove.enemyPawnBoard = newmove.enemyPawnBoard ^ board.enemyPawns[i];
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard | newmove.enemyPawns[i];


                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }
                }
                if((board.enemyPawns[i]<<7 & board.allyBoard) && !(board.enemyPawns[i] & RIGHTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.enemyPawns[i] = board.enemyPawns[i]<<7;

                    newmove.enemyPawnBoard = newmove.enemyPawnBoard ^ board.enemyPawns[i];
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard | newmove.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard ^ board.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard | newmove.enemyPawns[i];
                    mask = UNIVERSE ^ newmove.enemyPawns[i];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;

                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }
                }
            }
            else
            {
                if((board.enemyPawns[i]>>9 & board.allyBoard) && !(board.enemyPawns[i] & RIGHTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.enemyPawns[i] = board.enemyPawns[i]>>9;

                    newmove.enemyPawnBoard = newmove.enemyPawnBoard ^ board.enemyPawns[i];
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard | newmove.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard ^ board.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard | newmove.enemyPawns[i];
                    mask = UNIVERSE ^ newmove.enemyPawns[i];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;
                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }
                }
                if(!((board.enemyPawns[i]>>8 & board.enemyBoard) || (board.enemyPawns[i]>>8 & board.allyBoard)))
                {
                    newmove = board;
                    newmove.enemyPawns[i] = board.enemyPawns[i]>>8;

                    newmove.enemyPawnBoard = newmove.enemyPawnBoard ^ board.enemyPawns[i];
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard | newmove.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard ^ board.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard | newmove.enemyPawns[i];

                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }
                }
                if((board.enemyPawns[i]>>7 & board.allyBoard) && !(board.enemyPawns[i] & LEFTMOST_COLUMN))
                {
                    newmove = board;
                    newmove.enemyPawns[i] = board.enemyPawns[i]>>7;

                    newmove.enemyPawnBoard = newmove.enemyPawnBoard ^ board.enemyPawns[i];
                    newmove.enemyPawnBoard = newmove.enemyPawnBoard | newmove.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard ^ board.enemyPawns[i];
                    newmove.enemyBoard = newmove.enemyBoard | newmove.enemyPawns[i];
                    mask = UNIVERSE ^ newmove.enemyPawns[i];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;

                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }
                }
            }
        }



    }

    //rooks
    int r;
    newmove = board;
    for(r=0;r<ROOK_NUM;r++)
    {
        if(board.enemyRooks[r])
        {
            i = 1;
            while(!(board.enemyRooks[r]<<8*i & (board.enemyBoard)) && board.enemyRooks[r]<<8*i)
            {
                newmove = board;
                newmove.enemyRooks[r] = board.enemyRooks[r]<<8*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyRooks[r];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyRooks[r];

                if(newmove.enemyRooks[r] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyRooks[r];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;
                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
            i = 1;
            while(!(board.enemyRooks[r]>>8*i & (board.enemyBoard)) && board.enemyRooks[r]>>8*i)
            {
                newmove = board;
                newmove.enemyRooks[r] = board.enemyRooks[r]>>8*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyRooks[r];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyRooks[r];

                if(newmove.enemyRooks[r] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyRooks[r];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;

                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
            i = 1;
            while(!(board.enemyRooks[r]<<1*i & (RIGHTMOST_COLUMN | board.enemyBoard)) && board.enemyRooks[r]<<1*i)
            {
                newmove = board;
                newmove.enemyRooks[r] = board.enemyRooks[r]<<1*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyRooks[r];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyRooks[r];

                if(newmove.enemyRooks[r] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyRooks[r];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;

                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
            i = 1;
            while(!(board.enemyRooks[r]>>1*i & (LEFTMOST_COLUMN | board.enemyBoard)) && board.enemyRooks[r]>>1*i)
            {
                newmove = board;
                newmove.enemyRooks[r] = board.enemyRooks[r]>>1*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyRooks[r];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyRooks[r];

                if(newmove.enemyRooks[r] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyRooks[r];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;

                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
        }

    }

    int b;
    newmove = board;
    for(b=0;b<BISHOP_NUM;b++)
    {
        if(board.enemyBishops[b])
        {
            i = 1;
            while(!(board.enemyBishops[b]<<9*i & (RIGHTMOST_COLUMN| board.enemyBoard)) && board.enemyBishops[b]<<9*i)
            {
                newmove = board;
                newmove.enemyBishops[b] = board.enemyBishops[b]<<9*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyBishops[b];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyBishops[b];

                if(newmove.enemyBishops[b] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyBishops[b];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;

                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
            i = 1;
            while(!(board.enemyBishops[b]>>9*i & (LEFTMOST_COLUMN  | board.enemyBoard)) && board.enemyBishops[b]>>9*i)
            {
                newmove = board;
                newmove.enemyBishops[b] = board.enemyBishops[b]>>9*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyBishops[b];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyBishops[b];

                if(newmove.enemyBishops[b] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyBishops[b];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;
                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
            i = 1;
            while(!(board.enemyBishops[b]<<7*i & ( LEFTMOST_COLUMN | board.enemyBoard)) && board.enemyBishops[b]<<7*i)
            {
                newmove = board;
                newmove.enemyBishops[b] = board.enemyBishops[b]<<7*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyBishops[b];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyBishops[b];

                if(newmove.enemyBishops[b] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyBishops[b];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;
                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
            i = 1;
            while(!(board.enemyBishops[b]>>7*i & (RIGHTMOST_COLUMN | board.enemyBoard)) && board.enemyBishops[b]>>7*i)
            {
                newmove = board;
                newmove.enemyBishops[b] = board.enemyBishops[b]>>7*(i);

                newmove.enemyBoard = newmove.enemyBoard ^ board.enemyBishops[b];
                newmove.enemyBoard = newmove.enemyBoard | newmove.enemyBishops[b];

                if(newmove.enemyBishops[b] & newmove.allyBoard)
                {
                    mask = UNIVERSE ^ newmove.enemyBishops[b];
                    newmove.allyBoard = newmove.allyBoard & mask;
                    newmove.allyBishops[0] = newmove.allyBishops[0] & mask;
                    newmove.allyBishops[1] = newmove.allyBishops[1] & mask;
                    newmove.allyRooks[0] = newmove.allyRooks[0] & mask;
                    newmove.allyRooks[1] = newmove.allyRooks[1] & mask;
                    newmove.allyPawnBoard = newmove.allyPawnBoard & mask;
                    newmove.allyPawns[0] = newmove.allyPawns[0] & mask;
                    newmove.allyPawns[1] = newmove.allyPawns[1] & mask;
                    newmove.allyPawns[2] = newmove.allyPawns[2] & mask;
                    newmove.allyPawns[3] = newmove.allyPawns[3] & mask;
                    newmove.allyPawns[4] = newmove.allyPawns[4] & mask;
                    newmove.allyPawns[5] = newmove.allyPawns[5] & mask;
                    newmove.allyPawns[6] = newmove.allyPawns[6] & mask;
                    newmove.allyPawns[7] = newmove.allyPawns[7] & mask;
                    newValue = 0;
                    newValue = max_move(newmove, depth);

                    if( newValue <= bestMoveValue )
                    {
                        bestMove = newmove;
                        bestMoveValue = newValue + 0.01;
                    }

                    break;
                }
                i++;

                newValue = 0;
                newValue = max_move(newmove, depth);

                if( newValue <= bestMoveValue )
                {
                    bestMove = newmove;
                    bestMoveValue = newValue + 0.01;
                }
            }
        }
    }
    return bestMoveValue;
}


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


BITBOARD BoardParser(int player, char Board[64])
{
    BITBOARD BitBoard;
    BitBoard= InitBitBoard(&BitBoard);
    whoMoves = player;
    if(player==1)
    {
        BitBoard=BoardParserBrancos(Board,&BitBoard);
    }

    if(player==-1)
    {
        BitBoard=BoardParserPretos(Board,&BitBoard);
    }
    //DumpBitBoard(BitBoard);
    return BitBoard;
}

BITBOARD BoardParserPretos(char board[64],BITBOARD *BitBoard)
{
    int i,countAPawn=0,countEPawn=0,countABishop=0,countEBishop=0,countARook=0,countERook=0;
    int j; //endian fix

    for(j=0; j<BOARD_SIZE; j++)
    {
        i = BOARD_SIZE - j - 1;
        if(board[j]=='r')
        {
            BitBoard->allyRooks[countARook]=pow(2,i);
            BitBoard->allyBoard = BitBoard->allyBoard | BitBoard->allyRooks[countARook];
            countARook++;
        }
        if(board[j]=='R')
        {
            BitBoard->enemyRooks[countERook]=pow(2,i);
            BitBoard->enemyBoard = BitBoard->enemyBoard | BitBoard->enemyRooks[countERook];
            countERook++;
        }
        if(board[j]=='b')
        {
            BitBoard->allyBishops[countABishop]=pow(2,i);
            BitBoard->allyBoard = BitBoard->allyBoard | BitBoard->allyBishops[countABishop];
            countABishop++;
        }
        if(board[j]=='B')
        {
            BitBoard->enemyBishops[countEBishop]=pow(2,i);
            BitBoard->enemyBoard = BitBoard->enemyBoard | BitBoard->enemyBishops[countEBishop];
            countEBishop++;
        }
        if(board[j]=='p')
        {
            BitBoard->allyPawns[countAPawn]=pow(2,i);
            BitBoard->allyBoard = BitBoard->allyBoard | BitBoard->allyPawns[countAPawn];
            BitBoard->allyPawnBoard = BitBoard->allyPawnBoard | BitBoard->allyPawns[countAPawn];
            countAPawn++;
        }
        if(board[j]=='P')
        {
            BitBoard->enemyPawns[countEPawn]=pow(2,i);
            BitBoard->enemyBoard = BitBoard->enemyBoard | BitBoard->enemyPawns[countEPawn];
            BitBoard->enemyPawnBoard = BitBoard->enemyPawnBoard | BitBoard->enemyPawns[countEPawn];
            countEPawn++;
        }
    }
    return *BitBoard;
}

BITBOARD BoardParserBrancos(char board[64],BITBOARD *BitBoard)
{
    int i,countAPawn=0,countEPawn=0,countABishop=0,countEBishop=0,countARook=0,countERook=0;
    int j;
    for(j=0; j<BOARD_SIZE; j++)
    {
        i = BOARD_SIZE - j - 1;
        if(board[j]=='R')
        {
            BitBoard->allyRooks[countARook]=pow(2,i);
            BitBoard->allyBoard = BitBoard->allyBoard | BitBoard->allyRooks[countARook];

            countARook++;
        }
        if(board[j]=='r')
        {
            BitBoard->enemyRooks[countERook]=pow(2,i);
            BitBoard->enemyBoard = BitBoard->enemyBoard | BitBoard->enemyRooks[countERook];

            countERook++;
        }
        if(board[j]=='B')
        {
            BitBoard->allyBishops[countABishop]=pow(2,i);
            BitBoard->allyBoard = BitBoard->allyBoard | BitBoard->allyBishops[countABishop];

            countABishop++;
        }
        if(board[j]=='b')
        {
            BitBoard->enemyBishops[countEBishop]=pow(2,i);
            BitBoard->enemyBoard = BitBoard->enemyBoard | BitBoard->enemyBishops[countEBishop];

            countEBishop++;
        }
        if(board[j]=='P')
        {
            BitBoard->allyPawns[countAPawn]=pow(2,i);
            BitBoard->allyBoard = BitBoard->allyBoard | BitBoard->allyPawns[countAPawn];
            BitBoard->allyPawnBoard = BitBoard->allyPawnBoard | BitBoard->allyPawns[countAPawn];
            countAPawn++;
        }
        if(board[j]=='p')
        {
            BitBoard->enemyPawns[countEPawn]=pow(2,i);
            BitBoard->enemyBoard = BitBoard->enemyBoard | BitBoard->enemyPawns[countEPawn];
            BitBoard->enemyPawnBoard = BitBoard->enemyPawnBoard | BitBoard->enemyPawns[countEPawn];
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
    printf("\n");
}
void PegarCoordenadas(BITBOARD BitBoardAtual, BITBOARD BitBoardFuturo, int * saida)
{
    U64 changes = BitBoardAtual.allyBoard ^ BitBoardFuturo.allyBoard;
    U64 first_pos = BitBoardAtual.allyBoard & changes;
    U64 next_pos = BitBoardFuturo.allyBoard & changes;

    first_pos=log2l(first_pos);
    saida[0]= first_pos/8;
    saida[1]= 7 - first_pos%8;
    next_pos=log2l(next_pos);
    saida[2]= next_pos/8;
    saida[3]= 7 - next_pos%8;
}
int *PegarCooredenadas(BITBOARD *BitBoardAtual, BITBOARD *BitBoardFuturo)
{
    U64 valor,posicaoAtual,posicaoFutura;
    int i;
    int saida[4]={-1,-1,-1,-1};
    for(i=0;i<BISHOP_NUM;i++)
    {
        valor=BitBoardAtual->allyBishops[i]^BitBoardFuturo->allyBishops[i];
        if(valor!=0)
        {
            print_board(valor);
            posicaoAtual=valor&BitBoardAtual->allyBishops[i];
            posicaoAtual=log2l(posicaoAtual);
            posicaoAtual=63-posicaoAtual;
            saida[0]= posicaoAtual/8;
            saida[1]= posicaoAtual%8;
            posicaoFutura=valor&BitBoardFuturo->allyBishops[i];
            posicaoFutura=log2l(posicaoFutura);
            posicaoFutura=63-posicaoFutura;
            saida[2]= posicaoFutura/8;
            saida[3]= posicaoFutura%8;
            return saida;
        }
    }
    for(i=0;i<ROOK_NUM;i++)
    {
        valor=BitBoardAtual->allyRooks[i]^BitBoardFuturo->allyRooks[i];
        if(valor!=0)
        {
            posicaoAtual=valor&BitBoardAtual->allyRooks[i];
            print_board(posicaoAtual);
            posicaoAtual=log2(posicaoAtual);
            printf("%d \n",posicaoAtual);
            posicaoAtual=63-posicaoAtual;
            printf("%d \n",posicaoAtual);
            saida[0]= posicaoAtual/8;
            saida[1]= posicaoAtual%8;
            posicaoFutura=valor&BitBoardFuturo->allyRooks[i];
            print_board(posicaoFutura);
            posicaoFutura=log2(posicaoFutura);
            printf("%d \n",posicaoFutura);
            posicaoFutura=63-posicaoFutura;
            saida[2]= posicaoFutura/8;
            saida[3]= posicaoFutura%8;
            return saida;
        }
    }
    for(i=0;i<PAWN_NUM;i++)
    {
        valor=BitBoardAtual->allyPawns[i]^BitBoardFuturo->allyPawns[i];
        if(valor!=0)
        {
            print_board(valor);
            posicaoAtual=valor&BitBoardAtual->allyPawns[i];
            posicaoAtual=log2l(posicaoAtual);
            posicaoAtual=63-posicaoAtual;
            saida[0]= posicaoAtual/8;
            saida[1]= posicaoAtual%8;
            posicaoFutura=valor&BitBoardFuturo->allyPawns[i];
            posicaoFutura=log2l(posicaoFutura);
            posicaoFutura=63-posicaoFutura;
            saida[2]= posicaoFutura/8;
            saida[3]= posicaoFutura%8;
            return saida;
        }
    }
    return saida;
}
