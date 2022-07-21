#include <netdb.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define LENGTH 10000
#define MAX 4097
#define PORT 8080
#define SA struct sockaddr

#include<iostream>
#include<string>

using namespace std;

int sockfd;
string nickname;

/*
    IRC commands client

    connect: /connect 
    nickname: /nickname <nickname>
    msg: <message>
    quit: /quit
    ack: /ack
*/

// funcao para validar o comando do cliente, retorna true se o comando for valido
bool find(string command, char* find){

    if( strlen(find) > command.length() ) return false;

    for( int i = 0 ; i < strlen(find) ; i++ ){

        if( command[i] != find[i] ) return false;

    }

    return true;

}

// funcao para extrair uma parte da mensagem do cliente, retorna a fatia extraida
char* extract( string command, int position ){

    int start = 0;
    char* extract = new char[50];

    for( int i = position ; i < command.length() ; i++ ){

        extract[start++] = command[i];

    }
    
    extract[command.length()] = '\0';

    return extract;

}

bool runnig = true;

// thread que recebe as mensagens do servidor
void *receiveThread( void *vargp ){

    char receiveMessage[MAX];
    char ack[MAX];
    strcpy(ack, "/ack");

    while(runnig){

        do{

            bzero(receiveMessage, sizeof(receiveMessage));

            read(sockfd, receiveMessage, sizeof(receiveMessage));

                if( find(receiveMessage, (char*)"/nickname ") ){
                
                    nickname = (string) extract(receiveMessage, 10);

                    cout << endl << "Nickname alterado para: " << nickname << endl;

                    write(sockfd, ack, MAX);

                }else if( find(receiveMessage, (char*)"/quit") ){

                    cout << receiveMessage << endl;
                    cout << endl << "Conversa finalizada" << endl;
                
                    runnig = false;

                    write(sockfd, ack, MAX);

                    break;

                }else if( find(receiveMessage, (char*)"/pong") ){

                    cout << endl << "<server>: PONG" << endl;

                    write(sockfd, ack, MAX);

                }else{

                    cout << receiveMessage;

                    if( receiveMessage[MAX-1] == '\0' ){

                        write(sockfd, ack, MAX);

                        break;

                    }

                }

        }while( 1 == 1 );

    }

    return nullptr;

}

// thread que envia as mensagens do cliente
void *sendThread( void *vargp ){

    string input;
    char buff[LENGTH];
    char sendMessage[MAX];

    // infinite loop for chat
    while(runnig) {
        
        bzero(sendMessage, sizeof(sendMessage));

        cout << "@" << nickname << ": ";

        //scanf("\n%[^\n]", buff);

        getline(cin, input);

        strcpy(buff, input.c_str());

        if( strcmp(buff, "/quit") == 0 ){

            bzero(sendMessage, sizeof(sendMessage));
            strcpy(sendMessage, buff);

            write(sockfd, sendMessage, sizeof(sendMessage));

        }else if( find(buff, (char*)"/nickname ") ){

            char* validNickname = new char[50];
            
            validNickname = extract(buff, 10);

            bzero(sendMessage, sizeof(sendMessage));
            strcpy(sendMessage, buff);

            write(sockfd, sendMessage, sizeof(sendMessage));

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

    }

    return nullptr;

}

int main(){

    signal(SIGINT, SIG_IGN);
    
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

    //char input[LENGTH];

    nickname = "";

    pthread_t thread_id_receive;
    pthread_t thread_id_send;
    pthread_t thread_id_teste;

    cout << "To start a connection to the server, send '/connect' " << endl;

    while (1) {

        printf("<$>: ");
        
        //scanf("\n%[^\n]", input);
        
        getline(cin, command);

        if (command == "/connect"){

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

                printf("connected to the server. socket(%d)\n", sockfd);

            }

            cout << endl << "Command List:" << endl << endl;

            cout << "\t/nickname <char>: set a nickname" << endl;
            cout << "\t/ping: receive a 'pong' response from server" << endl;
            cout << "\t/quit: close connection to the server and close the aplication" << endl << endl;
           

            pthread_create(&thread_id_receive, NULL, receiveThread, NULL);
            pthread_create(&thread_id_send, NULL, sendThread, NULL);

            pthread_join(thread_id_receive, NULL);
            pthread_join(thread_id_send, NULL);

            //func(sockfd);

            break;

        }
        
    }
   
    // close the socket
    close(sockfd);
}