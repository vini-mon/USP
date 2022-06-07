#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define LENGTH 10000
#define MAX 4097
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd){

    int n;
    char buff[LENGTH];
    char sendMessage[MAX];
    char receiveMessage[MAX];

    // infinite loop for chat
    for (;;) {
        
        bzero(sendMessage, sizeof(sendMessage));

        printf("\nEscreva uma mensagem: ");

        scanf("\n%[^\n]", buff);

        int ctrl = 0;

        for( int i = 0 ; i < strlen(buff); i++ ){

            sendMessage[ctrl] = buff[i];

            if( ctrl == MAX-1 ){

                sendMessage[MAX-1] = '*';

                write(sockfd, sendMessage, sizeof(sendMessage));

                bzero(sendMessage, sizeof(sendMessage));

                ctrl = -1;

                i--;

            }else if( i == strlen(buff)-1 ){

                sendMessage[MAX-1] = '\0';

                write(sockfd, sendMessage, sizeof(sendMessage));

                bzero(sendMessage, sizeof(sendMessage));

                break;

            }

            ctrl++;

        }

        printf("\nEsperando por uma resposta...\n");

        do{

            bzero(receiveMessage, sizeof(receiveMessage));
   
            // read the message from client and copy it in buffer
            read(sockfd, receiveMessage, sizeof(receiveMessage));

            printf("\n\tMensagem recebida: ");

            for( int i = 0 ; i < MAX-1 ; i++ ){

                printf("%c", receiveMessage[i]);

            }

            printf("\n");

            if( receiveMessage[MAX-1] == '\0' ){

                break;

            }

        }while( 1 == 1 );

    }
    
}
   
int main(){
    
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {

        printf("socket creation failed...\n");
        exit(0);

    }else{

        printf("Socket successfully created..\n");
        
    }
        
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {

        printf("connection with the server failed...\n");
        exit(0);

    }else{

        printf("connected to the server..\n");

    }
   
    // function for chat
    func(sockfd);
   
    // close the socket
    close(sockfd);
}