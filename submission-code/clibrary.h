#ifndef __CBIBLIOTECA__
#define __CBIBLIOTECA__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "geral_library.h"


void error(const char *msg);

void print_board (char board[TAM_BOARD]);

void help ();


#endif