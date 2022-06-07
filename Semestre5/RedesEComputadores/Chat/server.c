#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 4096
#define PORT 8080
#define SA struct sockaddr
   
// Função destinada ao chat entre cliente e servidor
void func(int connfd)
{
    char buff[MAX];
    int n;
    // loop infinito pro chat
    for (;;) {
        bzero(buff, MAX);
   
        // lê a mensagem do cliente e copia pro buffer
        read(connfd, buff, sizeof(buff));
        printf("Do cliente: %s\t Para cliente : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copia a mensagem do server no buffer
        while ((buff[n++] = getchar()) != '\n')
            ;
   
        // e manda pro cliente
        write(connfd, buff, sizeof(buff));
   
        // Se a mensagem contém 'exit' o server fecha
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server fechando...\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // Criação do socket e verificação
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("a criação do socket falhou...\n");
        exit(0);
    }
    else
        printf("Socket criado com sucesso..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // atribui IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Ligando a socket recém-crada com o dado IP 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("ligação do socket falhou...\n");
        exit(0);
    }
    else
        printf("Socket ligado com sucesso..\n");
   
    // Agora o server está pronto
    if ((listen(sockfd, 5)) != 0) {
        printf("Escuta falhou...\n");
        exit(0);
    }
    else
        printf("Server ouvindo..\n");
    len = sizeof(cli);
   
    // Aceita o pacote de dado do cliente
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("aceitação de pacote falhou...\n");
        exit(0);
    }
    else
        printf("server aceitou o cliente...\n");
   
    // Chat entre cliente e servidor
    func(connfd);
   
    // Depois do chat fecha a socket
    close(sockfd);
}