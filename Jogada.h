#include <stdio.h>

typedef struct Jogada
{
    int pos;
    int posDesejada;
} JOGADA;

JOGADA CriarJogada(int pos, int posDesejada, JOGADA jogada);
