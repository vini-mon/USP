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
#define MAX 5
#define PORT 8080
#define SA struct sockaddr
   
// Função destinada ao chat entre cliente e servidor
void func(int connfd)
{
    int n;
    char buff[LENGTH];
    char sendMessage[MAX];
    char receiveMessage[MAX];
    // infinite loop for chat
    for (;;) {

        bzero(receiveMessage, sizeof(receiveMessage));
   
        // read the message from client and copy it in buffer
        read(connfd, receiveMessage, sizeof(receiveMessage));

        for( int i = 0; i < MAX+1; i++ ){

            if( receiveMessage[i] == '\n' ){

                printf("fFrom client: %s", receiveMessage);

                bzero(receiveMessage, sizeof(receiveMessage));

                printf("fim\n");

                break;

            }

            if( receiveMessage[i] == '\0' ){

                printf("fFrom client: %s", receiveMessage);
                bzero(receiveMessage, sizeof(receiveMessage));

                printf("fechou\n");

                read(connfd, receiveMessage, sizeof(receiveMessage));

                i = 0;

            }

        }

        n = 0;
        // copy server message in the buffer
        //while ((buff[n++] = getchar()) != '\n');

        printf("White a messsage: ");
        scanf("\n%[^\n]", buff);

        buff[strlen(buff)] = '\n';

        int ctrl = 0;

        for( int i = 0 ; i < LENGTH ; i++ ){

            if( buff[i] == '\n' ){

                sendMessage[ctrl] = '\n';

                write(connfd, sendMessage, sizeof(sendMessage));
                bzero(sendMessage, sizeof(sendMessage));

                break;

            }

            if( i == MAX-1 || buff[i] == '\0' ){

                sendMessage[ctrl] = '\0';

                write(connfd, sendMessage, sizeof(sendMessage));

                bzero(sendMessage, sizeof(sendMessage));

                ctrl = 0;
                i--;

            }else{

                sendMessage[ctrl] = buff[i];
                ctrl++;

            }

        }
   
        // and send that buffer to client
        //write(connfd, sendMessage, sizeof(sendMessage));
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
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
    }
    else
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
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // Function for chatting between client and server
    func(connfd);
   
    // After chatting close the socket
    close(sockfd);
}