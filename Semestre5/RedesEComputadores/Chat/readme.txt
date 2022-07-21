Alunos:

Vinícius Santos Monteiro - 11932463
Victor Gomes de Carvalho - 11275168

Link para o drive:
    https://drive.google.com/drive/folders/1iwVvQZ2OOJsrEm5nZs-_s3Dy9AqBVOIf?usp=sharing

Link para o GitHub:
    https://github.com/vini-mon/USP/tree/main/Semestre5/RedesEComputadores/Chat

Vesao do Kernel
    $ uname -r
    
    5.4.0-122-generic

Linux
    $ egrep '^(VERSION|NAME)=' /etc/os-release

    NAME="Linux Mint"
    VERSION="20.3 (Una)"


Para compilar o programa:

    Primeiro deve-se compilar e rodar o "server"

        g++ server.cpp -o server -pthread -lrt
        ./server

    Em seguida, em outro terminal, compile o client

        g++ client.cpp -o client -pthread 
        
    Para testar a comunicacão no chat, abra outros terminais e rode o cliente

        ./client

    Se aparecer a mensagem "server accept the client..." do lado do servidor,
    significa que o cliente e o servidor estão conectados com sucesso. Caso
    contrário, verifique as portas e o IP do seu computador.

    > Lista de comandos do servidor:

        /                 - Forca o fechamento o servidor

    > Lista de comandos do client:
    
        /connect          - Cria a conexão com o servidor
        /quit             - Desliga a conexão com o servidor e termina o programa
        /ping             - Envia um ping para o servidor que retorna um pong
        /nickname <char*> - Define o nickname do cliente no servidor