#include "board.h"
#define TOTALCASAS 63

void QualJoga(int *cor)
{
    int erro;
    // if (cor == BRANCAS)
    //erro=moveBRANCAS();
    // else
    //erro=movePRETAS();
}

int *SalvaMovimentosBrancas(int *totalPecas)
{
    int i=0;
    int countPecas=0;
    while(countPecas < totalPecas)
    {
        if(board[i]== 'R')
        {
            //salva movimentos torre
            countPecas++;
        }
        if(board[i]=='B')
        {
            //move bispo
            countPecas++;
        }
        if(board[i]=='P')
        {
            //move peao
            countPecas++;
        }
        i++;
    }
    return 0;

}

int *SalvaMovimentosPretas(int *totalPecas)
{
    int i=TOTALCASAS;
    int countPecas=0;
    while(countPecas < totalPecas)
    {
        if(board[i]== 'r')
        {
            //salva movimentos torre
            countPecas++;
        }
        if(board[i]=='b')
        {
            //move bispo
            countPecas++;
        }
        if(board[i]=='p')
        {
            //move peao
            countPecas++;
        }
        i--;
    }
    return 0;

}

int *SalvaMovimentosTorre(int pos)
{
    int i;
    if(pos+8 <=TOTALCASAS )
    {
        i=pos+8;
        while(i<=TOTALCASAS && board[i]=='.')
        {
            //salvajogada
            i+=8;
        }
        if(i<=63 && board[i]!='.' )
            //salvaposicao
    }
    if(pos-8 <0)
    {
        i=pos-8;
        while(i>=0 && board[i]=='.')
        {
            //salva jogada
            i-=8;
        }
        if(i>=0 && board[i]!='.')
            //salvaposicao
    }

    if( (pos+1)%8 > 0)
    {
        i=pos+1;
        while(i%8>0 && board[i]=='.')
        {
            //salva jogada
            i++;
        }
        if(i%8>0 && board[i]!='.')
            //salva jogada
    }

    if((pos-1)%8<7)
    {
        i=pos-1;
        while(i%8<7 && board[i]!='.')
        {
            //salva jogada
            i--;
        }
        if(i%8<7 && board[i]!='.')
            //salva jogada
    }
}

int *SalvaMovimentosBispo(int pos)
{
    int i;
    if(pos+9 <= TOTALCASAS && (pos+9)%8!=0 )
    {
        i=pos+8;
        while(i<=TOTALCASAS && board[i]=='.'&& pos%8!=0)
        {
            //salvajogada
            i+=9;
        }
        if(i<=TOTALCASAS && board[i]!='.'&& pos%8!=0)
            //salva jogada
    }
    if(pos-9 >=0 && pos%8!=0)
    {
        i=pos-9;
        while(i>=0 && board[i]=='.' && pos%8!=0)
        {
            //salva jogada
            i-=9;
        }
        if(i>=0 && board[i]!='.' && pos%8!=0)
            //salva jogada
    }

    if(pos+7 <= TOTALCASAS && pos%8!=7 )
    {
        i=pos+7;
        while(i<=TOTALCASAS && board[i]=='.'&& pos%7!=0)
        {
            //salvajogada
            i+=7;
        }
        if(i<=TOTALCASAS && board[i]!='.'&& pos%7!=0)
            //salva jogada
    }

    if(pos-7 >=0 && pos%8!=7)
    {
        i=pos-7;
        while(i>=0 && board[i]=='.' && pos%8!=7)
        {
            //salva jogada
            i-=7;
        }
        if(i>=0 && board[i]!='.' && pos%8!=7)
            //salva jogada
    }

}
int *SalvaMovimentosPeao(int pos)
{
    if(pos+8>TOTALCASAS){
        //vitória
    }
    else{
        if(board[pos+8]=='.')
            // salvaposição
        if(board[pos+7]!='.')
            //salva posição
        if(board[pos+9]!='.')
            //salva posição
        }
}


/* move(int posAtual, int posFutura){
    if(peca='r')
    {

    }


}
*/
