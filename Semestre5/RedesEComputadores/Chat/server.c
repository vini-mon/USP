#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define LENGTH 10000
#define MAX 4097
#define PORT 8081
#define SA struct sockaddr
   
// Função destinada ao chat entre cliente e servidor
void func(int connfd)
{
    int n;
    int exit;
    char buff[LENGTH];
    char sendMessage[MAX];
    char receiveMessage[MAX];
    // infinite loop for chat
    for (;;) {

        do{

            bzero(receiveMessage, sizeof(receiveMessage));
   
            // read the message from client and copy it in buffer
            read(connfd, receiveMessage, sizeof(receiveMessage));

            printf("\n\tMensagem recebida: ");

            for( int i = 0 ; i < MAX-1 ; i++ ){

                printf("%c", receiveMessage[i]);

            }

            printf("\n");

            if( receiveMessage[MAX-1] == '\0' ){

                break;

            }

        }while( 1 == 1 );

        printf("\n");

        bzero(sendMessage, sizeof(sendMessage));

        printf("\nEscreva uma mensagem: ");

        scanf("\n%[^\n]", buff);

        int ctrl = 0;

        for( int i = 0 ; i < strlen(buff); i++ ){

            sendMessage[ctrl] = buff[i];

            if( ctrl == MAX-1 ){

                sendMessage[MAX-1] = '*';

                write(connfd, sendMessage, sizeof(sendMessage));

                bzero(sendMessage, sizeof(sendMessage));

                ctrl = -1;

                i--;

            }else if( i == strlen(buff)-1 ){

                sendMessage[MAX-1] = '\0';

                write(connfd, sendMessage, sizeof(sendMessage));

                bzero(sendMessage, sizeof(sendMessage));

                break;

            }

            ctrl++;

        }

        printf("\nEsperando por uma resposta...\n");

    }
}
   
// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {

        printf("socket creation failed...\n");
        exit(0);

    }else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {

        printf("socket bind failed...\n");
        exit(0);

    }else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {

        printf("Listen failed...\n");
        exit(0);

    }else
        printf("Server listening..\n");

    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    //connfd = accept(sockfd, (SA*)&cli, &len);

    char message[100] = "";
    
    while( connfd = accept(sockfd, (SA*)NULL, NULL) ){

        printf("address: %d", connfd);

        printf("server accepted you!\n");

        strcpy(message, "<server>:**alguem se conectou**\n");
        write(connfd, message, sizeof(message));

        int pid;

        if((pid = fork()) == 0) {

            while (recv(connfd, message, 100, 0) > 0) {

                if( strcmp(message, "") != 0 ){

                    printf("Message Received: %s\n", message);
                    
                    strcpy(message, "<server>:Recebemos a sua mensagem, é nois\n");
                    write(connfd, message, sizeof(message));

                }

                stpcpy(message, "");

            }

            exit(0);

        }else{

            strcpy(message, "<server>:Você está conectado");
            write(connfd, message, sizeof(message));

        }

    }

    // After chatting close the socket
    close(sockfd);
}