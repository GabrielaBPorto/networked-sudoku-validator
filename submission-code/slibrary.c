#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "slibrary.h"
#include "geral_library.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int tabuleiro_cheio(char *board)
{
    for (int i = 0; i < TAM_BOARD; i++)
    {
        if(board[i] == 0)
        {
            return(0);
        }
    }
    return(1);
}

int verifica_coluna(char *board, int y, int valor)
{
    int i = y;
    while(i<81)
    {
        if(board[i] == valor)
        {
            return(0);
        }
        i+=9;
    }
    return(1);
}

int verifica_linha(char *board, int x, int valor)
{
    //divisão inteira


    int linha = x*9;
    
    int i = linha;
    while(i<(linha+9)){
        if(board[i] == valor)
            return(0);
        i++;
    }
    return(1);
}

int verifica_quadrado(char *board, int x, int y, int valor)
{
    int linha = (x)/3 * 3;
    int coluna = (y)/3 * 3;
    int posicion = 9*linha + coluna;
    
    for( int i = 0; i < 3; i++ ){
        if (board[posicion + i] == valor ||
            board[posicion + 9 + i] == valor ||
            board[posicion + 18 + i] == valor)
            return(0);
    }
    
    return(1);
}


void atribui_tabuleiro (char *board, int game)
{
    int i = 0;
	//if (game == 0)
    //{
    for (i =0 ; i< TAM_BOARD; i++)
    {
        //board[i] = BOARD_0[i];
    }

    //}
}

