#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 4096
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Digite a string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("Do Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client fechando...\n");
            break;
        }
    }
}
   
int main()
{
    int sockfd, connfd;
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
    servaddr.sin_addr.s_addr = inet_addr("172.17.238.192");
    servaddr.sin_port = htons(PORT);
   
    // conecta a socket do cliente com a socket do servidor
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("conexão com o server falhou...\n");
        exit(0);
    }
    else
        printf("conectado ao servidor..\n");
   
    // chat
    func(sockfd);
   
    // fecha o socket
    close(sockfd);
}