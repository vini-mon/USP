/*
SSC0903 - Computação de Alto Desempenho
Turma A

Trabalho 1

Breno Lívio Silva de Almeida, 10276675
Fabio Henrique Alves Cavaleti - 11200550
Lucas Massao Fukusawa Dagnone - 11295810
Vinícius Santos Monteiro - 11932463

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#define MAX 10

// dados por cidade, região e do Brasil como um todo, i.e., em três níveis. Os dados retornados
// para cada nível são: a menor e a maior nota, a mediana, a média aritmética simples, e o
// desvio padrão

//  Serão dados prêmios em dinheiro para a cidade e para a região com as
// maiores médias aritméticas simples das notas

// R regiões tem C cidades, com A alunos
// NTA = R * C * A

// Função que retorna desvio padrão de um dado vetor
float std(int* freq_notas, float media)
{
    float sd = 0;
    int total_freqs = 0;

    int i;
    for (i = 0; i < 101; i++)
    {
        sd += freq_notas[i]*pow(i - media, 2);
        total_freqs += freq_notas[i];
    }

    sd = sqrt(sd / total_freqs);

    return sd;
}

// Função que retorna média de um dado vetor
float mean(int* freq_notas)
{
    float avg = 0;
    int total_freqs = 0;
    
    int i;
    for (i = 0; i < 101; i++)
    {
        avg += i*freq_notas[i];
        total_freqs += freq_notas[i];
    }

    avg /= total_freqs;
    
    return avg;
}

// Função que retorna mediana de um dado vetor
float median(int* freq_notas)
{
    int curr_freq = 0, total_freqs = 0;
    
    int i, j;
    for (i = 0; i < 101; i++)
    {
        total_freqs += freq_notas[i];
    }

    float* notas = (float*)malloc(total_freqs * sizeof(float));

    float med;

    for (i = 0; i < 101; i++)
    {
        for (j = 0; j < freq_notas[i]; j++)
        {
            notas[curr_freq] = i;
            curr_freq++;
        }
        if (curr_freq > total_freqs/2)
            break;
    }

    if (total_freqs % 2 == 0)
    {
        med = (notas[(total_freqs / 2) - 1] +  notas[(total_freqs / 2)]) / 2;
    } else 
    {
        med = notas[(total_freqs / 2)];
    }

    free(notas);

    return med;
}

// Função que retorna valor máximo de um dado vetor
int max(int* freq_notas)
{
    int highest;
    
    int i;
    for (i = 100; i >= 0; i--)
    {
        if (freq_notas[i] != 0)
        {
            highest = i;
            break;
        }
    }
    
    return highest;
}

// Função que retorna valor mínimo de um dado vetor
int min(int* freq_notas)
{
    int lowest;
    
    int i;
    for (i = 0; i < 100; i++)
    {
        if (freq_notas[i] != 0)
        {
            lowest = i;
            break;
        }
    }
    
    return lowest;
}

// Função que imprime o sumário estatístico dos valores do array 3d fornecido
int summary_statistics(int*** arr, int R, int C, int A)
{
    int i, j, k;
    
    // Matriz para guardar frequências de notas em nível de cidade

    int*** cidade_freq = (int***)calloc(R, sizeof(int**));
 
    if (cidade_freq == NULL)
    {
        exit(0);
    }
 
    for (i = 0; i < R; i++)
    {
        cidade_freq[i] = (int**)calloc(C, sizeof(int*));
 
        if (cidade_freq[i] == NULL)
        {
            exit(0);
        }
 
        for (j = 0; j < C; j++)
        {
            cidade_freq[i][j] = (int*)calloc(101, sizeof(int));
            if (cidade_freq[i][j] == NULL)
            {
                exit(0);
            }
        }
    }

    // Matriz para guardar frequências de notas em nível de região

    int* regiao_freq[R];
    for (i = 0; i < R; i++)
        regiao_freq[i] = (int*)calloc(101, sizeof(int));
    
    // Matriz para guardar frequências de notas em nível de país

    int pais_freq[101] = {0};

    // Matriz para guardar resultados em nível de cidade

    float*** cidade_stats = (float***)malloc(R * sizeof(float**));
 
    if (cidade_stats == NULL)
    {
        exit(0);
    }
 
    for (i = 0; i < R; i++)
    {
        cidade_stats[i] = (float**)malloc(C * sizeof(float*));
 
        if (cidade_stats[i] == NULL)
        {
            exit(0);
        }
 
        for (j = 0; j < C; j++)
        {
            cidade_stats[i][j] = (float*)malloc(5 * sizeof(float));
            if (cidade_stats[i][j] == NULL)
            {
                exit(0);
            }
        }
    }

    // Matriz para guardar resultados em nível de região
    
    float* regiao_stats[R];
    for (i = 0; i < R; i++)
        regiao_stats[i] = (float*)malloc(5 * sizeof(float));

    // Vetor para guardar resultados em nível de país
    
    float pais_stats[5] = {0};

    /*
        Calcula as medidas estatísticas a partir daqui
    */
    
    // Começa a considerar o tempo de resposta

    double wtime = omp_get_wtime();

    // Conta frequências das notas em níveis de cidade, região e país

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            for (k = 0; k < A; k++) // Frequência em nível de cidade
            {
                cidade_freq[i][j][arr[i][j][k]]++;
            }

            for (k = 0; k < 101; k++) // Região
            {
                regiao_freq[i][k] += cidade_freq[i][j][k];
            }
        }

        for (k = 0; k < 101; k++) // País
        {
            pais_freq[k] += regiao_freq[i][k];
        }
    }

    // Sumário estatístico em nível de cidade

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            // Valor mínimo
            cidade_stats[i][j][0] = min(cidade_freq[i][j]);
            // Valor máximo
            cidade_stats[i][j][1] = max(cidade_freq[i][j]);
            // Mediana
            cidade_stats[i][j][2] = median(cidade_freq[i][j]);
            // Média
            cidade_stats[i][j][3] = mean(cidade_freq[i][j]);
            // Desvio Padrão
            cidade_stats[i][j][4] = std(cidade_freq[i][j], cidade_stats[i][j][3]);
        }
    }

    // Sumário estatístico em nível de região

    for (i = 0; i < R; i++)
    {
        // Valor mínimo
        regiao_stats[i][0] = min(regiao_freq[i]);
        // Valor máximo
        regiao_stats[i][1] = max(regiao_freq[i]);
        // Mediana
        regiao_stats[i][2] = median(regiao_freq[i]);
        // Média
        regiao_stats[i][3] = mean(regiao_freq[i]);
        // Desvio Padrão
        regiao_stats[i][4] = std(regiao_freq[i], regiao_stats[i][3]);
    }

    // Sumário estatístico em nível de país

    pais_stats[0] = min(pais_freq);
    pais_stats[1] = max(pais_freq);
    pais_stats[2] = median(pais_freq);
    pais_stats[3] = mean(pais_freq);
    pais_stats[4] = std(pais_freq, pais_stats[3]);

    // Melhor regiao

    int melhor_regiao;
    float melhor_regiao_media = 0;

    for (i = 0; i < R; i++)
    {
        if (regiao_stats[i][3] > melhor_regiao_media)
        {
            melhor_regiao_media = regiao_stats[i][3];
            melhor_regiao = i;
        }
    }

    // Melhor cidade

    int melhor_cidade_regiao, melhor_cidade;
    float melhor_cidade_media = 0;

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            if (cidade_stats[i][j][3] > melhor_cidade_media)
            {
                melhor_cidade_media = cidade_stats[i][j][3];
                melhor_cidade_regiao = i;
                melhor_cidade = j;
            }
        }
    }

    // Tempo de resposta

    wtime = omp_get_wtime() - wtime;

    /*
        Termina as operações de sumarização estatística
    */

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            printf("Reg %d - Cid %d: menor: %d, maior: %d, mediana: %.2f, média: %.2f e DP: %.2f\n",
                    i, j, (int) cidade_stats[i][j][0], (int) cidade_stats[i][j][1], cidade_stats[i][j][2], cidade_stats[i][j][3], cidade_stats[i][j][4]);
        }
        printf("\n");
    }

    for (i = 0; i < R; i++)
    {
        printf("Reg %d: menor: %d, maior: %d, mediana: %.2f, média: %.2f e DP: %.2f\n",
            i, (int) regiao_stats[i][0], (int) regiao_stats[i][1], regiao_stats[i][2], regiao_stats[i][3], regiao_stats[i][4]);
    }

    printf("\n");

    printf("Brasil: menor: %d, maior: %d, mediana: %.2f, média: %.2f e DP: %.2f\n\n", (int) pais_stats[0], (int) pais_stats[1], pais_stats[2], pais_stats[3], pais_stats[4]);

    printf("Melhor região: Região %d\n", melhor_regiao);

    printf("Melhor cidade: Região %d, Cidade %d\n\n", melhor_cidade_regiao, melhor_cidade);

    printf("Tempo de resposta sem considerar E/S, em segundos: %.6fs\n", wtime);

    // Limpa alocações de memória feitas

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++) {
            free(cidade_stats[i][j]);
        }
        free(cidade_stats[i]);
    }

    free(cidade_stats);

    for (i = 0; i < R; i++)
        free(regiao_stats[i]);

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++) {
            free(cidade_freq[i][j]);
        }
        free(cidade_freq[i]);
    }

    free(cidade_freq);

    for (i = 0; i < R; i++)
        free(regiao_freq[i]);
}

// Gera array 3d baseado no número de Regiões, Cidades e Alunos, com valores aleatórios
int*** generate_random(int R, int C, int A)
{
    int*** arr = (int***)malloc(R * sizeof(int**));
    int i, j, k;
 
    if (arr == NULL)
    {
        exit(0);
    }
 
    for (i = 0; i < R; i++)
    {
        arr[i] = (int**)malloc(C * sizeof(int*));
 
        if (arr[i] == NULL)
        {
            exit(0);
        }
 
        for (j = 0; j < C; j++)
        {
            arr[i][j] = (int*)malloc(A * sizeof(int));
            if (arr[i][j] == NULL)
            {
                exit(0);
            }
        }
    }
 
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            for (int k = 0; k < A; k++) {
                arr[i][j][k] = rand() % 101;
            }
        }
    }
 
    // Imprime números gerados
    // for (i = 0; i < R; i++)
    // {
    //     for (j = 0; j < C; j++)
    //     {
    //         for (k = 0; k < A; k++) {
    //             printf("%d ", arr[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
 
    return arr;
}

int main(int argc, char *argv[])
{
    int i, j, R, C, A, SEED;
    char buf[MAX];

    for (i = 0; fgets(buf, MAX, stdin); i++)
    {
        int val = atoi(buf);

        switch (i){
            case 0:
                R = val;
                break;
            case 1:
                C = val;
                break;
            case 2:
                A = val;
                break;
            case 3:
                SEED = val;
                break;
        }
    }

    //printf("Regiões: %d, Cidades: %d, Alunos: %d, SEED: %d\n", R, C, A, SEED);

    srand(SEED);

    int*** arr = generate_random(R, C, A);

    summary_statistics(arr, R, C, A);

    // Limpa matriz 3D com os valores aleatórios

    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }

    free(arr);

    return 0;
}