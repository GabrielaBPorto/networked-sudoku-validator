#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "clibrary.h"
#include "geral_library.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void print_board (char board[TAM_BOARD])
{
	int i = 0;
	system("clear");
	for (i=1; i<=TAM_BOARD; i++)
	{
		printf("|");
		if (board[i-1] == 0)
		{
			printf(" ");
		}
		else
		{
			printf("%d", board[i-1]);
		}
		if (i%9 == 0)
		{
			printf("|\n");
		}
	}
}

void help ()
{
	printf("Para fazer uma jogada use o seguinte comando:\nC<numero linha><numero coluna> \nPara escrever:\nWT<int>\nPara deletar:\nDEL\nPara desistir:\nGUP\nO jogo irá sair quando terminar");
	printf("\nEsplicacao de como jogar.\n");
}
