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

#include<iostream>
#include<string>

using namespace std;

string nickname;

/*

    map IRC commands

    connect: /connect 
    nickname: /nickname <nickname>
    msg: <message>
    quit: /quit
    ack: /ack


*/

bool find(string command, char* find){

    if( strlen(find) > command.length() ) return false;

    for( int i = 0 ; i < strlen(find) ; i++ ){

        if( command[i] != find[i] ) return false;

    }

    return true;

}

char* extract( string command, int position ){

    int start = 0;
    char* extract = new char[50];

    for( int i = position ; i < command.length() ; i++ ){

        extract[start++] = command[i];

    }
    
    extract[command.length()] = '\0';

    return extract;

}

void func(int sockfd){

    int n;
    char buff[LENGTH];
    char sendMessage[MAX];
    char receiveMessage[MAX];

    // infinite loop for chat
    for (;;) {

        if( fork() == 0 ){
        
            bzero(sendMessage, sizeof(sendMessage));

            cout << "<" << nickname << ">: ";

            scanf("\n%[^\n]", buff);

            if( strcmp(buff, "/quit") == 0 ){

                //strcpy(sendMessage, buff);

                //write(sockfd, sendMessage, sizeof(sendMessage));

                //bzero(sendMessage, sizeof(sendMessage));

                printf("Finalizando conexão");
                close(sockfd);
                exit(0);
                // break;

            }else if( find(buff, (char*)"/nickname ") ){

                char* validNickname = new char[50];
                
                validNickname = extract(buff, 10);

                strcpy(sendMessage, buff);

                write(sockfd, sendMessage, sizeof(sendMessage));

                bzero(sendMessage, sizeof(sendMessage));

            }else{

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

            }

        }else{
            
            do{

                //printf("\nEsperando por uma resposta...\n");

                bzero(receiveMessage, sizeof(receiveMessage));
    
                // read the message from client and copy it in buffer
                read(sockfd, receiveMessage, sizeof(receiveMessage));

                cout << receiveMessage << endl; 

                if( find(receiveMessage, (char*)"/nickname ") ){

                    cout << receiveMessage << endl;
                
                    nickname = (string) extract(receiveMessage, 10);

                    cout << "Nickname alterado para: " << nickname << endl;

                }else{

                    printf("%s", receiveMessage);

                    if( receiveMessage[MAX-1] == '\0' ){

                        break;

                    }

                }

            }while( 1 == 1 );

        }

    }
    
}

void *receiveThread( void *vargp ){

    return NULL;

}

void *sendThread( void *vargp ){

    cout << "deu certo mano?" << endl;

    return NULL;

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

    string command = "";

    char input[LENGTH];

    nickname = "$";
/*
    pthread_t thread_id1;
    pthread_t thread_id2;

    pthread_create(&thread_id1, NULL, receiveThread, NULL);
    pthread_create(&thread_id2, NULL, sendThread, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
*/

    while (1) {

        printf("<$>: ");
        
        scanf("\n%[^\n]", input);

        command = input;

        if (command != "/connect"){

            bzero(&servaddr, sizeof(servaddr));
   
            // assign IP, PORT
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
            servaddr.sin_port = htons(PORT);
        
            // connect the client socket to server socket
            if ( connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0 ) {

                printf("connection with the server failed...\n");
                exit(0);

            }else{

                printf("connected to the server..\n");

            }

           // write(sockfd, sendMessage, sizeof(sendMessage));
        
            // function for chat
            
            func(sockfd);

            break;

        }
        
    }
   
    // close the socket
    close(sockfd);
}