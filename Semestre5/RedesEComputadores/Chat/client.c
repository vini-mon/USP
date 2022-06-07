#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define LENGTH 10000
#define MAX 5
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

        printf("\nEnter the string : ");

        //n = 0;
        //while ((buff[n++] = getchar()) != '\n');

        scanf("\n%[^\n]", buff);

        buff[strlen(buff)] = '\n';

        int ctrl = 0;

        for( int i = 0 ; i < LENGTH ; i++ ){

            if( buff[i] == '\n' ){

                sendMessage[ctrl] = '\n';

                write(sockfd, sendMessage, sizeof(sendMessage));
                bzero(sendMessage, sizeof(sendMessage));

                break;

            }

            if( i == MAX-1 || buff[i] == '\0' ){

                sendMessage[ctrl] = '\0';

                write(sockfd, sendMessage, sizeof(sendMessage));

                bzero(sendMessage, sizeof(sendMessage));

                ctrl = 0;
                i--;

            }else{

                sendMessage[ctrl] = buff[i];
                ctrl++;

            }

        }

        read(sockfd, receiveMessage, sizeof(receiveMessage));

        printf("From Server : %s", receiveMessage);

        if( (strncmp(receiveMessage, "exit", 4)) == 0 ){

            printf("Client Exit...\n");
            break;

        }

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