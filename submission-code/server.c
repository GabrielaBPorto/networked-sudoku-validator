/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
//input and output
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
//data types used in system calls
#include <sys/socket.h>
//includes a number of definitions of structs need for sockets
#include <netinet/in.h>
//constants and structs needed for internet domain addresses
#include <time.h>
#include "slibrary.h"
#include "geral_library.h"
#include <signal.h>

//Se uma syscall fails, its called


int main(int argc, char *argv[])
{
    //sockfd and newsockfd - file descriptors store the values returned by the socket system call and the accept system call
    //portno stores de port number where the server is
    int sockfd, newsockfd, portno;
    //clilen adress of the client
    socklen_t clilen;
    //Quando o server le os chars, coloca nesse buffer
    char buffer[10];
    //sockaddr_in constaints the internet address
    char name[11];
    int valor;
    //char board[TAM_BOARD+1];
    //char board_original[TAM_BOARD+1];

    
    char board[TAM_BOARD+1] = 
    {
        2, 8, 6, 1, 9, 0, 0, 4, 7,
        3, 0, 0, 0, 2, 0, 1, 5, 6,
        5, 4, 1, 0, 0, 0, 8, 9, 2,
        1, 9, 0, 6, 0, 0, 0, 8, 0,
        6, 3, 0, 8, 0, 0, 5, 7, 9,
        8, 5, 0, 3, 7, 9, 4, 0, 0,
        7, 0, 5, 0, 0, 0, 6, 0, 4,
        0, 0, 3, 0, 4, 6, 7, 2, 0,
        0, 6, 8, 2, 3, 7, 9, 1, 0,
        '\n'
    };
    char board_original[TAM_BOARD+1] = 
    {
        2, 8, 6, 1, 9, 0, 0, 4, 7,
        3, 0, 0, 0, 2, 0, 1, 5, 6,
        5, 4, 1, 0, 0, 0, 8, 9, 2,
        1, 9, 0, 6, 0, 0, 0, 8, 0,
        6, 3, 0, 8, 0, 0, 5, 7, 9,
        8, 5, 0, 3, 7, 9, 4, 0, 0,
        7, 0, 5, 0, 0, 0, 6, 0, 4,
        0, 0, 3, 0, 4, 6, 7, 2, 0,
        0, 6, 8, 2, 3, 7, 9, 1, 0,
        '\n'
    };
    

    clock_t time[2];

    struct sockaddr_in serv_addr, cli_addr;
    //n number os chars read or written
    int x, y;
    int n, k;
    int game = 0;
    //Se nao é repassado um segundo argumento para ter como porta, mas pode ser colocado um número? Tentativa
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    //socket() creates a new socket 1 - address domain (internet) 2 - type of socket SOCK_STREAM- TCP or SOCK_DGRAM -UDP
    //3 - Qual o protocolo 0 tcp 1 udp ?
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        //if -1 failed
        error("ERROR opening socket");
    //todos os valores dentro é igual a 0
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //Transforma string em int
    portno = atoi(argv[1]);
    //adress family
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Representação de números da sua maquina pode ser diferente da rede
    //host do network
    //cointains the port number. htons() converte o numero da porta in host byte
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
    
    if (newsockfd < 0) 
        error("ERROR on accept");

    /* -- Teste conexão -- */

    bzero(buffer,5);
    
    n = read(newsockfd,buffer, 4);

    if (n < 0) 
        error("ERROR reading from socket");

    fprintf(stderr,"Recebi:%s",buffer);

    if(!strcmp(buffer,"STR\n"))
    {
        k = write(newsockfd,"OK1",strlen("OK1"));
        printf("OK1\n");
    }

    /* -- Player Name -- */

    bzero(name,11);

    n = read(newsockfd, name, 10); // Problema, não está lendo/esperando o nome
    // Ele está recebendo o enter da outra mensagem?
    if(n <= 0)
        fprintf(stderr,"Erro na leitura\n");
    
    printf("O nome do player é %s", name );

    if(strcmp(name,""))
    {
        k = write(newsockfd,"OK2",strlen("OK2"));
    }

    /* -- Sorteio jogo -- */

    game = rand() % 10;
    bzero(buffer,5);
    sprintf (buffer, "G0%d", game);
    printf("Mandando qual o jogo\n");
    k = write(newsockfd,buffer,strlen(buffer));

    /* -- Tabuleiro -- */

    printf("Mandando tabuleiro\n");


    k = write(newsockfd,board,82);
    
    bzero(buffer,5);
    n = read(newsockfd,buffer, 4);
    if (!strcmp(buffer, "BRD\n")) // Board recived
    {
        printf("Board received\n");
        time[0] = clock();
    }
    else
    {
        printf("Board problems\n");
        exit(3);
    }

    bzero(buffer,4);
    n = read(newsockfd,buffer,4);
    int cheio = 0;
    while(!cheio)
    {
        if(buffer[0] == 'C')
        {
            x = buffer[1] - CHAR_NUM;
            y = buffer[2] - CHAR_NUM;

            bzero(buffer,4);
            n = write(newsockfd,"OK3",strlen("OK3"));
            n = read(newsockfd,buffer,3);
            if(buffer[0] == 'W' && buffer[1] == 'T')
            {
                valor = buffer[2] - CHAR_NUM;
                // Realiza a escrita
                if(verifica_linha(board,x-1,valor)){
                    if(verifica_coluna(board,y-1,valor)){
                        if(verifica_quadrado(board,x-1,y-1,valor)){
                            // O valor vai ser colocado na posição x,y
                            int posicion = 9*(x-1)+(y-1);
                            if(board_original[posicion] != '0')
                            {
                                board[posicion] = valor;
                                k = write(newsockfd,"AKW",3);
                                k = write(newsockfd,board,TAM_BOARD);
                            }
                        }
                        else{
                            k = write(newsockfd,"ER3",strlen("ER3"));
                        }
                    }
                    else{
                        k = write(newsockfd,"ER2",strlen("ER2"));
                    }
                }
                else{
                    k = write(newsockfd,"ER1",strlen("ER1"));
                }
            }
            if(!strcmp(buffer,"DEL"))
            {
                int posicion = 9*(x-1)+(y-1);
                if(board_original[posicion] == 0){
                    board[posicion] = 0;
                    k = write(newsockfd,"AKD",strlen("AKD"));
                    k = write(newsockfd,board,TAM_BOARD);
                }
                else{
                    k = write(newsockfd,"ERD",strlen("ERD"));
                }
            }
        }
        //O jogador desistiu
        if(!strcmp(buffer,"GUP")){
            cheio = 1;
        }
        if(tabuleiro_cheio(board))
        {
            cheio = 1;
            k = write(newsockfd,"END",strlen("END"));
        }
        bzero(buffer,4);
        n = read(newsockfd,buffer,4);
        if(n <= 0)
        {   
            break;
        }
    }


    if(k<0){
        exit(2);
    }


    /*Realiza o cálculo de  transformar para ms*/
    time[1] = clock();
    double times = (time[1] - time[0]) * 1000.0 / CLOCKS_PER_SEC;
    fprintf(stderr, "TIM:%gms\n",times);

    close(newsockfd);
    close(sockfd);
    return 0; 
}
