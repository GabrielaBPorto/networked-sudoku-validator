#ifndef __SBIBLIOTECA__
#define __SBIBLIOTECA__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "geral_library.h"


// Colocar os tabuleros possiveis aqui?


void error(const char *msg);

int tabuleiro_cheio(char *board);

int verifica_coluna(char *board, int y,int valor);

int verifica_linha(char *board, int x, int valor);

int verifica_quadrado(char *board, int x, int y, int valor);

void atribui_tabuleiro (char *board, int game);

#endif