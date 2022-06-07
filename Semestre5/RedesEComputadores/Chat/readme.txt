Alunos:

Vinícius Santos Monteiro - 11932463
Victor Gomes de Carvalho - 11275168

Para compilar o programa:

    Primeiro deve-se compilar e rodar o "server"

        gcc server.c -o server
        ./server

    Em seguida, em outro terminal, deve-se rodar o client

        gcc client.c -o client
        ./client

    Se aparecer a mensagem "server accept the client..." do lado do servidor,
    significa que o cliente e o servidor estão conectados com sucesso. Caso
    contrário, verifique as portas e o IP do seu computador.

    Para fazer o teste da quantidade máxima de caracteres de uma mensagem, basta
    diminuir a constante MAX para, por exemplo, 5. Assim, verificando a quebra
    da mensagem em duas. (Nota: faça isso nos dois arquivos .c!!!)
