#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<winsock2.h>
#include "cJSON.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main ()
{
    // long long int val=pow(10,64);
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    int tamanho;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
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
        return 1;
    }
    puts("Connected");

    char *name,*cor,retorno[10000];
    cJSON *entrada,*saida,*jogada;
    entrada=cJSON_CreateObject();
    cJSON_AddItemToObject(entrada, "name", cJSON_CreateString("Bobot"));
    name=cJSON_PrintUnformatted(entrada);
    puts(name);

    if( send(s , name , strlen(name) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
    //Receive a reply from the server
    if((tamanho = recv(s , retorno , 10000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
        return 1;
    }
    retorno[tamanho]='\0';
    puts("Reply received\n");
    saida=cJSON_Parse(retorno);
    name=cJSON_Print(saida);
    puts(name);


    if( send(s , name , strlen(name) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    int from[2];
    int to[2];
    while(cJSON_GetObjectItem(saida,"winner")->valueint==0 && cJSON_GetObjectItem(saida,"draw")->valueint==0)
    {
        if( cJSON_GetObjectItem(saida,"who_moves")->valueint==1)
        {
            jogada= cJSON_CreateObject();
            from[0]=0;
            from[1]=0;
            to[0]=0;
            to[1]=1;
            cJSON_AddItemToObject(jogada, "from", cJSON_CreateIntArray(from,2));
            cJSON_AddItemToObject(jogada, "to", cJSON_CreateIntArray(to,2));
            name=cJSON_Print(jogada);
            if( send(s , name , strlen(name) , 0) < 0)
            {
                puts("Send failed");
                return 1;
            }
            if((tamanho = recv(s , retorno , 10000 , 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                return 1;
            }
            retorno[tamanho]='\0';
            saida=cJSON_Parse(retorno);
            name=cJSON_Print(saida);

            from[0]=0;
            from[1]=1;
            to[0]=0;
            to[1]=0;
            jogada= cJSON_CreateObject();
            cJSON_AddItemToObject(jogada, "from", cJSON_CreateIntArray(from,2));
            cJSON_AddItemToObject(jogada, "to", cJSON_CreateIntArray(to,2));
            name=cJSON_Print(jogada);
            if( send(s , name , strlen(name) , 0) < 0)
            {
                puts("Send failed");
                return 1;
            }

            if((tamanho = recv(s , retorno , 10000 , 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                return 1;
            }

            retorno[tamanho]='\0';
            saida=cJSON_Parse(retorno);
            name=cJSON_Print(saida);

        }
        else
        {
            jogada= cJSON_CreateObject();
            from[0]=7;
            from[1]=0;
            to[0]=7;
            to[1]=1;
            cJSON_AddItemToObject(jogada, "from", cJSON_CreateIntArray(from,2));
            cJSON_AddItemToObject(jogada, "to", cJSON_CreateIntArray(to,2));
            name=cJSON_Print(jogada);
            if( send(s , name , strlen(name) , 0) < 0)
            {
                puts("Send failed");
                return 1;
            }
            if((tamanho = recv(s , retorno , 10000 , 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                return 1;
            }
            retorno[tamanho]='\0';
            saida=cJSON_Parse(retorno);
            name=cJSON_Print(saida);

            from[0]=7;
            from[1]=1;
            to[0]=7;
            to[1]=0;
            jogada= cJSON_CreateObject();
            cJSON_AddItemToObject(jogada, "from", cJSON_CreateIntArray(from,2));
            cJSON_AddItemToObject(jogada, "to", cJSON_CreateIntArray(to,2));
            name=cJSON_Print(jogada);
            if( send(s , name , strlen(name) , 0) < 0)
            {
                puts("Send failed");
                return 1;
            }
            if((tamanho = recv(s , retorno , 10000 , 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                return 1;
            }
            retorno[tamanho]='\0';

            saida=cJSON_Parse(retorno);
            name=cJSON_Print(saida);
        }
    }
    name=NULL;

    return 0;
}
