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
#define PORT 8080
#define SA struct sockaddr

#include<vector>
#include<string>

using namespace std;
   
// Driver function
int main(){
    
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    char message[100] = "";
    string messageTool = "";

    vector<int> connAddress;
   
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
    
    while( connfd = accept(sockfd, (SA*)NULL, NULL) ){

        connAddress.push_back(connfd);

        printf("server accepted a new connection <%d>\n", connfd);

        messageTool.append("<server>:Cliente ").append(to_string(connfd)).append(" se conectou\n");

        strcpy(message, messageTool.c_str());
        
        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

            if( *itr != connfd ) write(*itr, message, sizeof(message));

        }

        int pid;

        if((pid = fork()) == 0) {

            while (recv(connfd, message, 100, 0) > 0) {

                if( strcmp(message, "") != 0 ){
                    
                    if (strcmp(message, "/quit") == 0) {
                        printf("%d has left the chat\n", connfd);
                        
                    } else {
                        printf("Message Received from <%d>: %s\n", connfd, message); 

                        messageTool.append("<").append(to_string(connfd)).append(">:");

                        messageTool += message;
                        messageTool += "\n";

                        stpcpy(message, messageTool.c_str());

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            if( *itr != connfd )
                                write(*itr, message, sizeof(message));

                        }
                    }

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