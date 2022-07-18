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

#include<iostream>

#include<vector>
#include<string>

using namespace std;

// .first is the connection, .second is the nickname
vector< pair<int, char*> > connAddress;

bool find(string command, char* find){

    cout << command << "|" << find << endl;

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

int indexClient(int find){

    for( int i = 0 ; i < connAddress.size() ; i++ ){

        if( connAddress[i].first == find ) return i;

    }

    return -1;

}

// Driver function
int main(){
    
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    char message[100] = "";
    string messageTool = "";
   
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

    char* teste = new char[50];

    teste = (char*) "testeeeee";
    connAddress.push_back( make_pair(99, teste) );

    teste = (char*) "jamal";
    connAddress.push_back( make_pair(98, teste) );

    
    while( connfd = accept(sockfd, (SA*)NULL, NULL) ){

        connAddress.push_back( make_pair(connfd, new char[50]) );

        printf("server accepted a new connection <%d>\n", connfd);

        messageTool.clear();
        messageTool.append("<server>:Cliente ").append(to_string(connfd)).append(" se conectou\n");

        strcpy(message, messageTool.c_str());
        
        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

            if( itr->first != connfd )
                write(itr->first, message, sizeof(message));

        }

        int pid;

        if((pid = fork()) == 0) {

            while (recv(connfd, message, 100, 0) > 0) {

                if( strcmp(message, "") != 0 ){
                    
                    if (strcmp(message, "/quit") == 0) {
                        printf("%d has left the chat\n", connfd);
                        
                    }else if( find(message, (char*)"/nickname ") ){

                        bool valid = true;
                        char* validNickname = new char[50];
                        
                        validNickname = extract(message, 10);

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            cout << "|" << itr->second << "|" << "|" << validNickname << "|" << endl;

                            if( strcmp(itr->second, validNickname) == 0 ){

                                valid = false;
                                break;

                            } 

                        }

                        if( valid ){

                            connAddress[ indexClient(connfd) ].second = validNickname;

                            messageTool.clear();
                            messageTool.append("<server>: <").append(to_string(connfd)).append("> mudou seu nome para: ").append(validNickname);

                            cout << messageTool << endl;

                            stpcpy(message, messageTool.c_str());

                            for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                                write(itr->first, message, sizeof(message));

                            }

                        }else{

                            messageTool.clear();
                            messageTool.append("<server>: este apelido já está em uso.\n");

                            stpcpy(message, messageTool.c_str());

                            write(connfd, message, sizeof(message));

                        }

                    }else{

                        printf("Message Received from <%d>: %s\n", connfd, message); 

                        messageTool.clear();
                        messageTool.append("<").append(to_string(connfd)).append(">:");

                        messageTool += message;
                        messageTool += "\n";

                        stpcpy(message, messageTool.c_str());

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            if( (int) itr->first != connfd )
                                write(itr->first, message, sizeof(message));

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