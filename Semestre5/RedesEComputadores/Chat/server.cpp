#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <fcntl.h>          // non-blocking socket
#include <sys/types.h>
#define LENGTH 10000
#define MAX 4097
#define PORT 8080
#define SA struct sockaddr

#include<iostream>

#include<vector>
#include<string>








// gcc -Wall -Wextra -g
// g++ server.cpp -o server -pthread -lrt





using namespace std;

int sockfd;

bool running = true;

// .first is the connection, .second is the nickname
vector< pair<int, string> > connAddress;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;

bool find(string command, char* find){

    if( strlen(find) > command.length() ) return false;

    for( int i = 0 ; i < (int) strlen(find) ; i++ ){

        cout << "command[i]: " << command[i] << "find[i]: " << find[i] << endl;

        if( command[i] != find[i] ) return false;

    }

    cout << "find" << endl;

    return true;

}

char* extract( string command, int position ){

    int start = 0;
    char* extract = new char[50];

    for( int i = position ; i < (int) command.length() ; i++ ){

        extract[start++] = command[i];

    }

    extract[command.length()] = '\0';

    return extract;

}

int indexClient(int find){

    for( int i = 0 ; i < (int) connAddress.size() ; i++ ){

        if( connAddress[i].first == find ) return i;

    }

    return -1;

}

void *serverAccept( void *vargp ){

    int connfdAccepted = 0;

    char message[100] = "";
    string messageTool = "";

    while(running){

        cout << "Waiting for connection..." << endl;

        connfdAccepted = accept(sockfd, (SA*)NULL, NULL);

        if( connfdAccepted ){

            cout << "** Tentando fechar mutex da CONEXAO" << endl;

            sem_wait(&semaphore);
            pthread_mutex_lock(&mtx);

            cout << "Fechado para conexao" << endl;

            connAddress.push_back( make_pair(connfdAccepted, to_string(connfdAccepted) ) );

            printf("server accepted a new connection <%d>\n", connfdAccepted);

            messageTool.clear();
            messageTool.append("<server>:Cliente ").append(to_string(connfdAccepted)).append(" se conectou\n");

            strcpy(message, messageTool.c_str());

            for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                cout << itr->first << "|" << itr->second << endl;

                if( itr->first != connfdAccepted )
                    write(itr->first, message, sizeof(message));

            }

            strcpy(message, "<server>:Você está conectado\n");
            write(connfdAccepted, message, sizeof(message));

            cout << "abrindo o mutex da conexaoooo" << endl;
            
            pthread_mutex_unlock(&mtx);
            sem_post(&semaphore);

            cout << "tudo aberto" << endl;

        }

        usleep(100000);

    }

    return nullptr;

}

void acknowledgementFull( int connfd, char* message ){

    for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

        int attempts = 0;

        for( attempts = 0 ; attempts < 5 ; attempts++ ){

            cout << itr->first << "|tentativa = " << attempts+1 << endl;

            write(itr->first, message, sizeof(message));

            sleep(1);

            int lenAck = 0;
            int readedAck = -1;
            char ack[MAX] = "";

            ioctl(itr->first, FIONREAD, &lenAck);

            if (lenAck > 0) {

                readedAck = (read(itr->first, ack, MAX));

                    cout << "|" << ack << "|" << endl;

                if( find(ack, (char*)"/ack") ){

                    cout << "Ack = " << ack << endl;
                    break;
                }
                
            }

        }

        if( attempts == 5 ){
            cout << "No response of " << itr->first << endl;
            itr->first = -1;
        }else{
            cout << "Ack response of " << itr->first << endl;
        }

    }

    return;

}

void acknowledgementSingle( int connfd, char* message ){

    for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

        if( itr->first == connfd ){

            int attempts = 0;

            for( attempts = 0 ; attempts < 5 ; attempts++ ){

                cout << itr->first << "|tentativa = " << attempts+1 << endl;

                write(itr->first, message, sizeof(message));

                sleep(1);

                int lenAck = 0;
                int readedAck = -1;
                char ack[MAX] = "";

                ioctl(itr->first, FIONREAD, &lenAck);

                if (lenAck > 0) {

                    readedAck = (read(itr->first, ack, MAX));

                        cout << "|" << ack << "|" << endl;

                    if( find(ack, (char*)"/ack") ){

                        cout << "Ack = " << ack << endl;
                        break;
                    }
                    
                }

            }

            if( attempts == 5 ){
                cout << "No response of " << itr->first << endl;
                itr->first = -1;
            }else{
                cout << "Ack response of " << itr->first << endl;
            }

        }

    }

    return;

}

void *messageThread( void *vargp ){

    int connfd;
    char message[MAX+1] = "";
    char ack[MAX] = "";
    string messageTool = "";

    while(running){

        cout << "\n\n\nTentando fechar aqui na MENSAGEM" << endl;

        sem_wait(&semaphore);
        pthread_mutex_lock(&mtx);

        //cout << "fechado para receber mensageeeem" << endl;
            //cout << "to aqui" << connfd << endl;

        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

            connfd = itr->first;

            /*
                int flags = fcntl(connfd, F_GETFL, 0);
                fcntl(connfd, F_SETFL, flags | O_NONBLOCK);
            */

            int len = 0;
            int readed = -1;

            ioctl(connfd, FIONREAD, &len);

            if (len > 0) {

                readed = (read(connfd, message, MAX));
                
            }

            //cout << sockfd << "|lendo de <" << connfd << "|" << itr->second << ">" << endl;

            //cout << readed << endl;
            //cout << readed << endl;

            if( readed >= 0 ){

                cout << "Mensagem recebida: " << message << endl;

                if( strcmp(message, "") != 0 ){

                    cout << "Vamos verificar: " << message << endl;
                    
                    if( find(message, (char*)"/nickname ") ){

                        bool valid = true;
                        string validNickname = new char[50];
                        
                        validNickname = (string) extract(message, 10);

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            if( itr->second == validNickname ){

                                valid = false;

                            } 

                        }

                        if( valid ){

                            connAddress[ indexClient(connfd) ].second = validNickname;

                            messageTool.clear();
                            messageTool.append("<server>: <").append(to_string(connfd)).append("> mudou seu nome para: ").append(connAddress[ indexClient(connfd) ].second).append("\n");

                            cout << messageTool << endl;

                            stpcpy(message, messageTool.c_str());

                            acknowledgementFull(connfd, message);

                            cout << "voltamos ao loop" << endl;

                            usleep(10000);

                            messageTool.clear();
                            messageTool.append("/nickname ").append(connAddress[ indexClient(connfd) ].second);
                            stpcpy(message, messageTool.c_str());

                            acknowledgementSingle(connfd, message);

                        }else{

                            messageTool.clear();
                            messageTool.append("<server>: este apelido já está em uso.\n");

                            stpcpy(message, messageTool.c_str());

                            write(connfd, message, sizeof(message));

                        }

                    }else if (strcmp(message, "/quit") == 0) {

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            if( itr->first == connfd ){

                                strcpy(message, "/quit");

                                write(itr->first, message, sizeof(message));
                                itr->first = -1;
                                break;

                            }

                        }

                        messageTool.clear();
                        messageTool.append("<server>:Cliente ").append(to_string(connfd)).append(" saiu\n");

                        strcpy(message, messageTool.c_str());

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            write(itr->first, message, sizeof(message));

                        }

                        //close(connfd);

                        printf("%d has left the chat\n", connfd);
                        
                    }else if (strcmp(message, "/ping") == 0) {

                        strcpy(message, "/pong");

                        cout << "Ping from " << connfd << endl;

                        write(connfd, message, sizeof(message));
                        
                    }else if( (strcmp(message, "/ack") != 0 )){

                        cout << connfd << endl;
                        cout << connAddress[indexClient(connfd)].second << endl;
                        cout << message << endl;

                        //printf("Message Received from <%d|%s>: %s\n", connfd, connAddress[indexClient(connfd)].second.c_str() , message);

                        messageTool.clear();
                        messageTool.append("<").append(connAddress[indexClient(connfd)].second).append(">:");

                        messageTool += message;
                        messageTool += "\n";

                        stpcpy(message, messageTool.c_str());

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            cout << "enviando para " << itr->first << "|" << itr->second << endl;

                            if( (int) itr->first != connfd )
                                write(itr->first, message, sizeof(message));

                        }

                        cout << "enviou" << endl;

                    }

                }

                stpcpy(message, "");


            }

        }

        cout << "abrindo o mutex da mensagem" << endl;

        pthread_mutex_unlock(&mtx);
        sem_post(&semaphore);

        usleep(100000);

    } 

    return nullptr;

}

int main(){
    
    struct sockaddr_in servaddr;

    int flagsSock = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flagsSock | O_NONBLOCK);
   
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


    string teste = "aaaa";
    connAddress.push_back( make_pair( 99, teste ) );

    teste = "bbbb";
    connAddress.push_back( make_pair( 77, teste ) );


    pthread_t thread_id_server;
    pthread_t thread_id_message;

    if(sem_init(&semaphore, 0, 1) != 0){
        cout << "erro ao inicializar o semaforo" << endl;
        exit(0);
    }

    if(pthread_mutex_init(&mtx, nullptr) != 0){
        cout << "erro ao iniciar o mutex" << endl;
        exit(0);
    }

    pthread_create(&thread_id_server, NULL, serverAccept, NULL);
    pthread_create(&thread_id_message, NULL, messageThread, NULL);

    string input = "";

    while( input != "/" ){
        getline(cin, input);
    }

    cout << "Finalizando threads" << endl;

    exit(0);

    running = false;

    pthread_join(thread_id_server, nullptr);
    pthread_join(thread_id_message, nullptr);

    cout << "Threads end" << endl;

    pthread_mutex_destroy(&mtx);
    sem_destroy(&semaphore);

    // After chatting close the socket
    close(sockfd);

    exit(0);

}