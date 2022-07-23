#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/types.h>
#define LENGTH 10000
#define MAX 4097
#define PORT 8080
#define SA struct sockaddr

#include<iostream>

#include<vector>
#include<string>

/*
    IRC commands client

    turn of server: /
*/

using namespace std;

int sockfd;

bool running = true;

// .first is the connection, .second is the nickname
vector< pair<int, string> > connAddress;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;

// funcao para validar o comando do cliente, retorna true se o comando for valido
bool find(string command, char* find){

    if( strlen(find) > command.length() ) return false;

    for( int i = 0 ; i < (int) strlen(find) ; i++ ){

        if( command[i] != find[i] ) return false;

    }

    cout << "find" << endl;

    return true;

}

// funcao para extrair uma parte da mensagem do cliente, retorna a fatia extraida
char* extract( string command, int position ){

    int start = 0;
    char* extract = new char[50];

    for( int i = position ; i < (int) command.length() ; i++ ){

        extract[start++] = command[i];

    }

    extract[command.length()] = '\0';

    return extract;

}

// funcao que verifica o index do cliente que enviou a mensagem de acordo com o socket de conexão
int indexClient(int find){

    for( int i = 0 ; i < (int) connAddress.size() ; i++ ){

        if( connAddress[i].first == find ) return i;

    }

    return -1;

}

// thread de configuração de conexão com o cliente
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

        usleep(1000);

    }

    return nullptr;

}

// funcao que verifica se todos os clientes receberam a mensagem enviada. Depois de 5 tentativas falhas, o servidor fecha a conexao com o cliente
void acknowledgementFull( char* message ){

    for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

        int attempts = 0;

        for( attempts = 0 ; attempts < 5 ; attempts++ ){

            write(itr->first, message, MAX);

            usleep(5000);

            int lenAck = 0;
            char ack[MAX] = "";

            ioctl(itr->first, FIONREAD, &lenAck);

            if (lenAck > 0) {

                read(itr->first, ack, MAX);

                if( find(ack, (char*)"/ack") ){

                    break;

                }
                
            }

        }

        if( attempts == 5 ){
            cout << "No response of " << itr->first << endl;
            cout << "Closing connection" << endl;
            itr->first = -1;
        }else{
            //cout << "Ack response of " << itr->first << endl;
        }

    }

    return;

}

// funcao que verifica se um cliente especifico recebeu a mensagem enviada. Depois de 5 tentativas falhas, o servidor fecha a conexao com o cliente
void acknowledgementSingle( int connfd, char* message ){

    for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

        if( itr->first == connfd ){

            int attempts = 0;

            for( attempts = 0 ; attempts < 5 ; attempts++ ){

                write(itr->first, message, MAX);

                usleep(5000);

                int lenAck = 0;
                char ack[MAX] = "";

                ioctl(itr->first, FIONREAD, &lenAck);

                if (lenAck > 0) {

                    read(itr->first, ack, MAX);

                    if( find(ack, (char*)"/ack") ){

                        break;

                    }
                    
                }

            }

            if( attempts == 5 ){
                cout << "No response of " << itr->first << endl;
                cout << "Closing connection" << endl;
                itr->first = -1;
            }else{
                //cout << "Ack response of " << itr->first << endl;
            }

        }

    }

    return;

}

// thread de recebimento, envio e redirecionamento de mensagens dos clientes
void *messageThread( void *vargp ){

    int connfd;
    char message[MAX+1] = "";
    string messageTool = "";

    while(running){

        sem_wait(&semaphore);
        pthread_mutex_lock(&mtx);

        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

            connfd = itr->first;

            int len = 0;
            int readed = -1;

            ioctl(connfd, FIONREAD, &len);

            if (len > 0) {

                readed = (read(connfd, message, MAX));
                
            }

            if( readed >= 0 ){

                cout << "<" << connAddress[indexClient(connfd)].first << "|" << connAddress[indexClient(connfd)].second << "> Mensagem recebida: " << message << endl;

                if( strcmp(message, "") != 0 ){
                    
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

                            acknowledgementFull(message);

                            messageTool.clear();
                            messageTool.append("/nickname ").append(connAddress[ indexClient(connfd) ].second);
                            stpcpy(message, messageTool.c_str());

                            acknowledgementSingle(connfd, message);

                        }else{

                            messageTool.clear();
                            messageTool.append("<server>: este apelido já está em uso.\n");

                            stpcpy(message, messageTool.c_str());

                            acknowledgementSingle(connfd, message);

                        }

                    }else if (strcmp(message, "/quit") == 0) {

                        for( auto itr = connAddress.begin() ; itr != connAddress.end() ; itr++ ){

                            if( itr->first == connfd ){

                                strcpy(message, "/quit");

                                acknowledgementSingle(connfd, message);

                                itr->first = -1;
                                break;

                            }

                        }

                        messageTool.clear();
                        messageTool.append("<server>:Cliente ").append(to_string(connfd)).append(" saiu\n");

                        strcpy(message, messageTool.c_str());

                        acknowledgementFull(message);

                        //close(connfd);

                        cout << connfd << " has left the chat" << endl;
                        
                    }else if (strcmp(message, "/ping") == 0) {

                        cout << "Ping from " << connfd << endl;

                        strcpy(message, "/pong");
                        acknowledgementSingle(connfd, message);
                        
                    }else if (strcmp(message, "/ack") != 0){

                        messageTool.clear();
                        messageTool.append("<").append(connAddress[indexClient(connfd)].second).append(">:");

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

        }

        pthread_mutex_unlock(&mtx);
        sem_post(&semaphore);

        usleep(1000);

    } 

    return nullptr;

}

// funcao principal do servidor
int main(){

    signal(SIGINT, SIG_IGN);
    
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
        cout << "Semaphore error..." << endl;
        exit(0);
    }

    if(pthread_mutex_init(&mtx, nullptr) != 0){
        cout << "Mutex error..." << endl;
        exit(0);
    }

    cout << endl << "To close the server, send '/' " << endl << endl;

    cout << "Server Online!" << endl;

    pthread_create(&thread_id_server, NULL, serverAccept, NULL);
    pthread_create(&thread_id_message, NULL, messageThread, NULL);

    char input = '.';

    while( running ){

        while(true){

            scanf("%c", &input);

            if( input == '/' )
                break;

        }

        running = false;

    }

    cout << "Server closed" << endl;

    pthread_mutex_destroy(&mtx);
    sem_destroy(&semaphore);
    cout << "Semaphore and Mutex destoyed" << endl;

    // After chatting close the socket
    close(sockfd);
    cout << "Socket closed" << endl;

    cout << endl << "Bye bye! :)" << endl;

    exit(0);

}