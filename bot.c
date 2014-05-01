#include "board.h"

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
        i++;
    }
    return 0;

}

int *SalvaMovimentosPretas(int *totalPecas)
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

int *SalvaMovimentosTorre(int pos)
{
    int i;
    if(pos+8 >63 )
    {
        i=pos+8;
        while(i>63 && board[i]!='.')
        {
            //salvajogada
            i+=8;
        }
    }
    if(pos-8 <0)
    {
        i=pos-8;
        while(i<0 && board[i]!='.')
        {
            //salva jogada
            i-=8;
        }
    }

    if( pos+1 > (pos/8)+1)
    {
        i=pos+1;
        while(i<(pos/8)+1 && board[i]!='.')
        {
            //salva jogada
            i++;
        }
    }

    if(pos-1> (pos/8)-1)
    {
        i=pos-1;
        while(i<(pos/8)-1 && board[i]!='.')
        {
            //salva jogada
            i--;
        }
    }
}

/* move(int posAtual, int posFutura){
    if(peca='r')
    {

    }


}
*/
