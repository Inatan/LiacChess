//#include "board.h"
//#include "Jogada.h"
//#define TOTALCASAS 63
//
//void QualJoga(int *cor, int totalpecas)
//{
//    int erro;
//    JOGADA *jogadas;
//    if (cor == BRANCAS)
//        SalvaMovimentosBrancas(totalpecas, jogadas);
//    else
//        SalvaMovimentosBrancas(totalpecas, jogadas);
//}
//JOGADA *SalvarJogada(JOGADA *jogadas, int pos, int posDesejada){
//    int tamanho=sizeof(jogadas);
//    JOGADA jogada;
//    CriarJogada(pos,posDesejada,jogada);
//    jogadas=(JOGADA*) realloc(jogadas,sizeof(jogadas)+1);
//    jogadas[tamanho]=jogada;
//    return jogadas;
//
//}
//
//void SalvaMovimentosBrancas(int *totalPecas, JOGADA *jogadas)
//{
//    int i=0;
//    int countPecas=0;
//    while(countPecas < totalPecas)
//    {
//        if(board[i]== 'R')
//        {
//            SalvaMovimentosTorre(i,jogadas);
//            countPecas++;
//        }
//        if(board[i]=='B')
//        {
//            SalvaMovimentosBispo(i,jogadas);
//            countPecas++;
//        }
//        if(board[i]=='P')
//        {
//            SalvaMovimentosPeao(i,jogadas);
//            countPecas++;
//        }
//        i++;
//    }
//
//}
//
//void SalvaMovimentosPretas(int *totalPecas, JOGADA *jogadas)
//{
//    int i=TOTALCASAS;
//    int countPecas=0;
//    while(countPecas < totalPecas)
//    {
//        if(board[i]== 'r')
//        {
//            SalvaMovimentosTorre(i,jogadas);
//            countPecas++;
//        }
//        if(board[i]=='b')
//        {
//            SalvaMovimentosBispo(i,jogadas);
//            countPecas++;
//        }
//        if(board[i]=='p')
//        {
//            SalvaMovimentosPeao(i,jogadas);
//            countPecas++;
//        }
//        i--;
//    }
//
//}
//
//void SalvaMovimentosTorre(int pos, JOGADA *jogadas)
//{
//    int i;
//    if(pos+8 <=TOTALCASAS )
//    {
//        i=pos+8;
//        while(i<=TOTALCASAS && board[i]=='.')
//        {
//            SalvarJogada(jogadas,pos,i+8);
//            i+=8;
//        }
//        if(i<=63 && board[i]!='.' && ((board[pos]=='r' && board[i+8]<98)||(board[pos]=='R' && board[i+8]>98)) )
//            SalvarJogada(jogadas,pos,i+8);
//    }
//    if(pos-8 <0)
//    {
//        i=pos-8;
//        while(i>=0 && board[i]=='.')
//        {
//            SalvarJogada(jogadas,pos,i-8);
//            i-=8;
//        }
//        if(i>=0 && board[i]!='.' && ((board[pos]=='r' && board[i-8]<98)||(board[pos]=='R' && board[i-8]>98)))
//            SalvarJogada(jogadas,pos,i-8);
//    }
//
//    if( (pos+1)%8 > 0)
//    {
//        i=pos+1;
//        while(i%8>0 && board[i]=='.')
//        {
//            SalvarJogada(jogadas,pos,i+1);
//            i++;
//        }
//        if(i%8>0 && board[i]!='.' && ((board[pos]=='r' && board[i+1]<98)||(board[pos]=='R' && board[i+1]>98)))
//            SalvarJogada(jogadas,pos,i+1);
//    }
//
//    if((pos-1)%8<7)
//    {
//        i=pos-1;
//        while(i%8<7 && board[i]!='.')
//        {
//            SalvarJogada(jogadas,pos,i-1);
//            i--;
//        }
//        if(i%8<7 && board[i]!='.' && ((board[pos]=='r' && board[i-1]<98)||(board[pos]=='R' && board[i-1]>98)))
//            SalvarJogada(jogadas,pos,i-1);
//    }
//}
//
//void SalvaMovimentosBispo(int pos, JOGADA *jogadas)
//{
//    int i;
//    if(pos+9 <= TOTALCASAS && (pos+9)%8!=0 )
//    {
//        i=pos+8;
//        while(i<=TOTALCASAS && board[i]=='.'&& i%8!=0)
//        {
//            SalvarJogada(jogadas,pos,i+9);
//            i+=9;
//        }
//        if(i<=TOTALCASAS && board[i]!='.'&& pos%8!=0 && ((board[pos]=='b' && board[i+9]<98)||(board[pos]=='B' && board[i+9]>98)))
//            SalvarJogada(jogadas,pos,i+9);
//    }
//    if(pos-9 >=0 && pos%8!=0)
//    {
//        i=pos-9;
//        while(i>=0 && board[i]=='.' && i%8!=0)
//        {
//            SalvarJogada(jogadas,pos,i-9);
//            i-=9;
//        }
//        if(i>=0 && board[i]!='.' && pos%8!=0 && ((board[pos]=='b' && board[i-9]<98)||(board[pos]=='B' && board[i-9]>98)))
//            SalvarJogada(jogadas,pos,i-9);
//    }
//
//    if(pos+7 <= TOTALCASAS && pos%8!=7 )
//    {
//        i=pos+7;
//        while(i<=TOTALCASAS && board[i]=='.'&& i%7!=0)
//        {
//            SalvarJogada(jogadas,pos,i+7);
//            i+=7;
//        }
//        if(i<=TOTALCASAS && board[i]!='.'&& pos%7!=0 && ((board[pos]=='b' && board[i+7]<98)||(board[pos]=='B' && board[i+7]>98)))
//            SalvarJogada(jogadas,pos,i+7);
//    }
//
//    if(pos-7 >=0 && pos%8!=7)
//    {
//        i=pos-7;
//        while(i>=0 && board[i]=='.' && i%8!=7 )
//        {
//            SalvarJogada(jogadas,pos,i-7);
//            i-=7;
//        }
//        if(i>=0 && board[i]!='.' && i%8!=7 && ((board[pos]=='b' && board[i-7]<98)||(board[pos]=='B' && board[i-7]>98)) )
//            SalvarJogada(jogadas,pos,i-7);
//    }
//
//}
//void SalvaMovimentosPeao(int pos, JOGADA *jogadas)
//{
//    if(pos+8>TOTALCASAS){
//        //vitória
//    }
//    else{
//        if(board[pos+8]=='.') // verifica se está livre a proxima casa
//            SalvarJogada(jogadas,pos,pos+8);
//        if(board[pos+7]!='.' && pos%8!=0 && ((board[pos]=='p' && board[pos+7]<98)||(board[pos]=='P' && board[pos+7]>98)))
//            // verifica se na proxima diagonal existe algun inimigo de forma não permitindo contar jogadas com peças da mesma cor
//            SalvarJogada(jogadas,pos,pos+7);
//        if(board[pos+9]!='.' && pos%8!=7 && ((board[pos]=='p' && board[pos+9]<98)||(board[pos]=='P' && board[pos+9]>98)))
//            SalvarJogada(jogadas,pos,pos+9);
//        }
//}
//
//
//// sem zueira
