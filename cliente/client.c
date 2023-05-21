#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "clibrary.h"


int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int game;

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
    printf("Recebido: %s\n",message);

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
    printf("Recebido: %s\n",message);

    /* -- Tabuleiro -- */

	bzero(board,82);
	n = read(sockfd,board,82);
    printf("O número de chars recebidos foi %d\n", n);
	print_board(board);

 	bzero(message,4);
	sprintf (message, "BRD\n");
    n = write(sockfd,message,strlen(message));

    //Comecei a mexer aqui Helena 
    //Enquanto nao receber a mensagem END do servidor, continua pegando coisa do cliente

    // while(!strcmp(message,"END")){
        bzero(message,4);
        fgets(message,4,stdin);
        if(!strcmp(message,"GUP") || message[0] != 'C')
        {
            printf("Por favor escreva de novo\n");
        }
        else
        {
            printf("Viva\n");
            n = write(sockfd,message,strlen(message));

            n = read(sockfd,message,4);
            printf("messagem é %s\n", message );
            // if(message[0] == 'C')
            if(!strcmp(message,"OK3"))
            {
                bzero(message,sizeof(message));
                scanf("%s",message);// WT1 or DEL
                if(!strcmp(message,"DEL") || (message[0] != 'W' && message[1] != 'T'))
                {
                    printf("Por favor escreva de novo2\n");
                }
                else
                {
                    n = write(sockfd,message,strlen(message));
                }
            }
            bzero(message,4);
            n = read(sockfd,message,4);
        }

        
    // }
    

    close(sockfd);
    return (0);
}
