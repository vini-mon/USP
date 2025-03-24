# CAD_Trabalhos
Trabalhos para a disciplina de SSC0903 Computação de Alto Desempenho.

## Instruções para rodar os códigos do trabalho 2
Os códigos foram criados para serem executados dentro do cluster.
Em primeiro lugar conecte - se com o cluster. Coloque os arquivos lá dentro. Os arquivos podem ser upados pelo git. (link do repositório [aqui] (https://github.com/brenoslivio/CAD_Trabalhos)).
### Código sequencial
Após entrar upar o repositório no cluster entre no diretório `Trab2/seq` . Com isso, você estará no repositório do código sequencial. Agora basta rodar o programa. No terminal, digite:
```bash
make all #Compila o progama
make run N=<número de cidades> #Executa o programa sequencial para N cidades
```
### Código paralelo
Após entrar upar o repositório no cluster entre no diretório `Trab2/mpi` . Com isso, você estará no repositório do código sequencial. Agora basta rodar o programa. No terminal, digite:
```bash
make all #Compila o progama
make run np=<número de processos a serem criados> N=<número de cidades> #Executa o programa paralelo para np processos e N cidades
```

Observe que o programa acima pode apresentar erro se alguma das máquinas que está descrita no arquivo hosts parar de funcionar. Nesse caso deve - se retirar o nome desta máquina do arquivo.
