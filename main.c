#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<winsock2.h>
#include "board.h"
#include "cJSON.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library

BOARD enviaPosicao(int fromX, int fromY,int toX,int toY,BOARD *Board);
BOARD conectar(char *name,BOARD *Board);

WSADATA wsa;
struct sockaddr_in server;
SOCKET *s;

int main ()
{
    // long long int val=pow(10,64);
//    WSADATA wsa;
    BOARD Board;

    //struct sockaddr_in *server;
    char *name="",retorno[10000];
    Board=conectar(name,&Board);
    puts(Board.board);
    int tamanho;
    while(Board.winner==0 && Board.draw==0)
    {
        if( Board.whoMoves==1)
        {
            Board= enviaPosicao(0,0,0,1,&Board);
            Board= enviaPosicao(0,1,0,0,&Board);
        }
        else
        {
            Board= enviaPosicao(7,0,7,1,&Board);
            Board= enviaPosicao(7,1,7,0,&Board);
        }
    }
    name=NULL;

    return 0;
}

BOARD conectar(char *name,BOARD *Board)
{

    int tamanho;
    char retorno[10000];
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        Board=NULL;
        return *Board;
    }

    printf("Initialised.");

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 50100 );

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        Board=NULL;
        return *Board;
    }
    puts("Connected");
    cJSON *entrada,*saida;
    entrada=cJSON_CreateObject();
    cJSON_AddItemToObject(entrada, "name", cJSON_CreateString("Bobot"));
    name=cJSON_PrintUnformatted(entrada);
    puts(name);

    if( send(s , name , strlen(name) , 0) < 0)
    {
        puts("Send failed");
        Board=NULL;
        return *Board;
    }
    puts("Data Send\n");
    if((tamanho = recv(s , retorno , 10000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
        Board=NULL;
        return *Board;
    }
    retorno[tamanho]='\0';
    puts("Reply received\n");
    saida=cJSON_Parse(retorno);
    name=cJSON_Print(saida);
    puts(name);
    Board->whiteInfractions=cJSON_GetObjectItem(saida,"white_infractions")->valueint;
    Board->blackInfractions=cJSON_GetObjectItem(saida,"black_infractions")->valueint;
    Board->fiftymoves=cJSON_GetObjectItem(saida,"50moves")->valueint;
    Board->enpassant[0]=cJSON_GetObjectItem(saida,"enpassant")->valueint;
    Board->enpassant[1]=cJSON_GetObjectItem(saida,"enpassant")->next->valueint;
    Board->draw=cJSON_GetObjectItem(saida,"draw")->valueint;
    Board->badmove=cJSON_GetObjectItem(saida,"bad_move")->valueint;
    Board->winner= cJSON_GetObjectItem(saida,"winner")->valueint;
    Board->board=cJSON_GetObjectItem(saida,"board")->valuestring;
    Board->whoMoves=cJSON_GetObjectItem(saida,"who_moves")->valueint;
    return *Board;
}

BOARD enviaPosicao(int fromX, int fromY,int toX,int toY,BOARD *Board)
{
    cJSON *jogada;
    cJSON *saida;
    char retorno[10000];
    int tamanho;
    int from[2];
    from[0]=fromX;
    from[1]= fromY;
    int to[2];
    to[0]=toX;
    to[1]=toY;
    jogada= cJSON_CreateObject();
    char *name;


    cJSON_AddItemToObject(jogada, "from", cJSON_CreateIntArray(from,2));
    cJSON_AddItemToObject(jogada, "to", cJSON_CreateIntArray(to,2));
    name=cJSON_Print(jogada);
    if( send(s , name , strlen(name) , 0) < 0)
    {
        puts("Send failed");
        Board= NULL;
        return *Board;
    }
    if((tamanho = recv(s , retorno , 10000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
        Board=NULL;
        return *Board;
    }
    retorno[tamanho]='\0';
    saida=cJSON_Parse(retorno);
    name=cJSON_Print(saida);
    Board->whiteInfractions=cJSON_GetObjectItem(saida,"white_infractions")->valueint;
    Board->blackInfractions=cJSON_GetObjectItem(saida,"black_infractions")->valueint;
    Board->fiftymoves=cJSON_GetObjectItem(saida,"50moves")->valueint;
    Board->enpassant[0]=cJSON_GetObjectItem(saida,"enpassant")->valueint;
    Board->enpassant[1]=cJSON_GetObjectItem(saida,"enpassant")->next->valueint;
    Board->draw=cJSON_GetObjectItem(saida,"draw")->valueint;
    Board->badmove=cJSON_GetObjectItem(saida,"bad_move")->valueint;
    Board->winner= cJSON_GetObjectItem(saida,"winner")->valueint;
    Board->board=cJSON_GetObjectItem(saida,"board")->valuestring;
    Board->whoMoves=cJSON_GetObjectItem(saida,"who_moves")->valueint;
    return *Board;
}
