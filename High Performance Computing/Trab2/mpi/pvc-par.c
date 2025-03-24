/*
    Projeto desenvolvido pelos alunos:
    Fabio Henrique Alves Cavaleti - 11200550
    Lucas Massao Fukusawa Dagnone - 11295810 
    Vinícius Santos Monteiro	  - 11932463
*/

/* OBS: Para rodar o código, digite no terminal:
   - make all
   - make run np= <numero de processos> N= <numero de cidades>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

#define MASTER 0
#define MAX 10 // Valor máximo de um caminho

#define MAX_CITIES 21 // Limite máximo de cidades no programa
#define INF 1e9;

long long fac[MAX_CITIES + 1]; // Vetor com valores dos fatoriais

void precompute_fac()
{
    fac[0] = 1;

    for(int i = 1; i < MAX_CITIES; i++)
    {
        fac[i] = i * fac[i - 1];
    }

}

// Essa função calcula qual é a k-ésima permutação que é representada pelo índice k
int* nth_permutation(int nro_cities, int k) {
    
    // encontrando o fatorial de n
    // int fact = 1;
    int * path = (int *) malloc(sizeof(int) * nro_cities);

    for( int i = 0; i < nro_cities; i++ ){
        path[i] = i;
    }

    // verificando se k é válido (1 <= k <= n!)
    if (k < 1 || k > fac[nro_cities]) {
        return NULL;
    }

    // criando uma cópia do array original
    int copy[nro_cities];
    for (int i = 0; i < nro_cities; i++) {
        copy[i] = path[i];
    }

    // encontrando a enésima permutação
    for (int i = 0; i < nro_cities; i++) {
        fac[nro_cities] /= (nro_cities - i);
        int index = (k - 1) / fac[nro_cities];

        // adicionando o elemento na posição index ao array resultado
        path[i] = copy[index];

        // removendo o elemento na posição index da cópia do array original
        for (int j = index; j < nro_cities - i - 1; j++) {
            copy[j] = copy[j + 1];
        }

        k -= index * fac[nro_cities];
    }

    return path;
}

/* Essa função encontra que é a próxima permutação na ordem lexicográfica baseada na permutação atual,
 ou seja, encontra a permutação de indice n+1 dado uma permutação de indice n.
*/
void next_permutation(int path[], int n) {
    // encontrando o primeiro índice da direita para o qual o valor do elemento é menor que o seu sucessor
    int i;
    for (i = n - 2; i >= 0; i--) {
        if (path[i] < path[i + 1]) {
        break;
        }
    }

    // se não houver tal índice, a permutação é a última permutação (ordem decrescente)
    if (i < 0) {
        printf("Essa é a última permutação\n");
        return;
    }

    // encontrando o primeiro índice da direita para o qual o valor do elemento é maior que o valor do elemento na posição i
    int j;
    for (j = n - 1; j > i; j--) {
        if (path[j] > path[i]) {
        break;
        }
    }

    // trocando os valores de arr[i] e arr[j]
    int temp = path[i];
    path[i] = path[j];
    path[j] = temp;

    // revertendo a ordem dos elementos da direita de i + 1
    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        temp = path[left];
        path[left] = path[right];
        path[right] = temp;
        left++;
        right--;
    }
}

// Calcula custo de um caminho
int get_path_cost(int path[], int** adj_mtx, int nro_cities)
{
    int cost = 0;

    for(int i = 0; i < nro_cities - 1; i++)
    {
        cost += adj_mtx[path[i]][path[i + 1]];
    }

    cost += adj_mtx[path[nro_cities - 1]][path[0]];

    return cost;
}

void print_mtx(int ** M, int N)
{
    printf("\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int nro_cities;
    nro_cities = atoi(argv[1]);
    precompute_fac();

    int npes, myrank;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    srand(123);
    
    int ** adj_mtx = (int **) malloc(nro_cities * sizeof(int *));
    for(int i = 0 ; i < nro_cities; i++)
    {
        adj_mtx[i] = (int *) malloc(nro_cities * sizeof(int));
    }

   //gera matriz de adj
    if(myrank == MASTER) 
    {
    
        for(int i = 0; i < nro_cities; i++){
            for(int j = 0; j<nro_cities; j++){
                if( i == j ){
                    adj_mtx[i][j] = 0;
                }else{
                    adj_mtx[i][j] = rand()%MAX+1;
                }
            }
        }

        print_mtx(adj_mtx, nro_cities);

        for(int pe = 1 ; pe < npes ; pe++) {
			for (int i = 0 ; i < nro_cities ; i++) {
				MPI_Send(&adj_mtx[i][0], nro_cities, MPI_INT, pe, pe, MPI_COMM_WORLD);
			}
		}

    }
	else
    {
		for (int i = 0 ; i < nro_cities ; i++)
        {
			MPI_Recv( &adj_mtx[i][0], nro_cities, MPI_INT, MASTER, myrank, MPI_COMM_WORLD, &status);
		}
	}

    MPI_Barrier(MPI_COMM_WORLD);

    double start_time, end_time;

    start_time = MPI_Wtime();

    int min_path_value = INF;
    int min_path[nro_cities];

    long long perm_per_node = fac[nro_cities - 1]/npes;
    long long rest = fac[nro_cities - 1] % npes;

    long long start_perm_idx, end_perm_idx;

    if(rest == 0)
    {
        start_perm_idx = (myrank*perm_per_node) + 1;
        end_perm_idx = (myrank + 1) * perm_per_node;
    }
    else
    {
        if(myrank < rest)
        {
            start_perm_idx = (myrank * (perm_per_node + 1)) + 1;
            end_perm_idx = (myrank + 1) * (perm_per_node + 1);
        }
        else
        {
            start_perm_idx = (perm_per_node + 1) * rest + perm_per_node * (myrank - rest) + 1;
            end_perm_idx = (perm_per_node + 1) * rest + (perm_per_node + 1 - rest) * perm_per_node;
        }
    }

    if(start_perm_idx <= end_perm_idx)// Verifica se o intervalo está correto
    {
        long long curr_perm_idx = start_perm_idx;
        int * curr_perm = (int *) malloc(sizeof(int) * nro_cities);
        curr_perm = nth_permutation(nro_cities, curr_perm_idx);
        if(curr_perm != NULL)
        {
            while(curr_perm_idx <= end_perm_idx)
            {
                int path_cost = get_path_cost(curr_perm, adj_mtx, nro_cities);
                if(path_cost < min_path_value)
                {
                    min_path_value = path_cost;
                    for(int i = 0; i < nro_cities; i++)
                    {
                        min_path[i] = curr_perm[i];
                    }
                }
                next_permutation(curr_perm, nro_cities);
                curr_perm_idx++;
            }
        }
    }

    // Agora iremos receber na MASTER os minimos de cada máquina e encontrar o verdadeiro minimo
    if(myrank == MASTER)
    {
        for(int pe = 1; pe < npes; pe++)
        {
            int aux_min_value;
            int aux_min_path[nro_cities + 1];

            MPI_Recv(&aux_min_value, 1, MPI_INT, pe, pe, MPI_COMM_WORLD, &status);
            MPI_Recv(&aux_min_path[0], nro_cities + 1, MPI_INT, pe, pe, MPI_COMM_WORLD, &status);

            if(aux_min_value < min_path_value)
            {
                min_path_value = aux_min_value;
                for(int i = 0; i < nro_cities; i++)
                {
                    min_path[i] = aux_min_path[i];
                }
            }
        }
    }
    else
    {
        MPI_Send(&min_path_value, 1, MPI_INT, MASTER, myrank, MPI_COMM_WORLD);
        MPI_Send(&min_path, nro_cities + 1, MPI_INT, MASTER, myrank, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    if(myrank == MASTER)
    {
        double time = end_time - start_time;
        printf("Valor do caminho minimo: %d\n", min_path_value);
        printf("caminho minimo: ");
        for(int i = 0; i < nro_cities; i++)
        {
            printf(" %d ", min_path[i]);
        }
        printf(" 0 ");

        printf("\nTempo de execução: %f\n", time);
    }

    MPI_Finalize();

    return 0;
}
