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
#include <time.h>

#define OKK OKK

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char message[4];
    char name[11];
    char board[82];
	
    if (argc < 3) 
	{
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    // Criação de socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = internet; SOCK_STREAM = tipo stream
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) 
	{
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno); // host to network -> pra conversarem na mesma lingua
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    

    /* -- Teste conexão -- */

    bzero(message,4);
	sprintf (message, "STR\n");
    n = write(sockfd,message,strlen(message));
    
    bzero(message,4);
    n = read(sockfd,message,3);
    if ( strcmp(message, "OK1") == 0 )
    {
    	printf("Connection established\n");
    }
    else
    {
    	printf("Connection problems\n");
    	exit(1);
    }

    /* -- Player Name -- */

	printf("Please enter your name (up to 10 char): ");
    bzero(name,11);
    fgets(name,10,stdin);
	n = write(sockfd,name,strlen(name));

	bzero(message,4);
    n = read(sockfd,message,3);
    printf("Recebido: %s\n",message);

    if ( strcmp(message, "OK2") == 0 )
    {
    	printf("Registered name\n");
    }
    else
    {
    	printf("Name problems\n");
    	exit(2);
    }  

    /* -- Sorteio jogo -- */

	bzero(message,4);
    n = read(sockfd,message,3);

    /* -- Tabuleiro -- */

	bzero(board,82);
	n = read(sockfd,board,82);
	print_board(board);

 	bzero(message,4);
	sprintf (message, "BRD\n");
    n = write(sockfd,message,strlen(message));

    printf("Use HLP para aprender a jogar o jogo\n");
    int cheio = 0;
    while(!cheio)
    {
        bzero(message,4);
        printf("Faca sua jogada (C<numero linha><numero coluna>).\n");
        scanf("%s",message);
        if(!strcmp(message,""))
        {
            bzero(message,4);
            n = read(sockfd,message,4);
        }
        if(!strcmp(message,"HLP"))
        {
            help();
        }
        if(message[0] == 'C')
        {
            n = write(sockfd,message,strlen(message));
            bzero(message,4);
            n = read(sockfd,message,4);
            if(!strcmp(message,"OK3"))
            {
            	printf("Escreva WT<int> para inserir ou DEL para apagar.\n");
                bzero(message,sizeof(message));
                scanf("%s",message);// WT1 or DEL
                if(strcmp(message,"DEL") && (message[0] != 'W' && message[1] != 'T'))
                {
                    help();
                }
                else
                {
                    n = write(sockfd,message,strlen(message));
                    bzero(message,4);
            		n = read(sockfd,message,3);
            		if(strcmp(message,"AKW") == 0)
            		{ 
            			bzero(board,TAM_BOARD);
            			n = read(sockfd,board,TAM_BOARD);
						print_board(board);
            		}
                    if(!strcmp(message,"ER1"))
                    {
                        printf("Já existe o número na linha. Try again\n");
                    }
                    if(!strcmp(message,"ER2"))
                    {
                        printf("Já existe o número na coluna. Try again\n");
                    }
                    if(!strcmp(message,"ER3"))
                    {
                        printf("Já existe o número no quadrado. Try again\n");
                    }
                    if (!strcmp(message,"AKD"))
                    {
                        printf("Jogada valida\n");
                        bzero(board,TAM_BOARD);
                        n = read(sockfd,board,TAM_BOARD);
                        print_board(board);
                    }
                    if(!strcmp(message,"ERD"))
                    {
                        printf("Você tentou deletar algo do tabuleiro original\n");
                    }
                }
            }
        }
        if(!strcmp(message,"GUP"))
        {   
            printf("Você desistiu!");
            n = write(sockfd,message,strlen(message));
            if(n<0){
                exit(3);
            }
            cheio = 1;
        }       
        if(!strcmp(message,"END"))
        {
            cheio =1;
        }
    }
    
    close(sockfd);
    return (0);
}
