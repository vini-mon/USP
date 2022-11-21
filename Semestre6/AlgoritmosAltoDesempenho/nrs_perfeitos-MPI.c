/*

Encontrar os nrs perfeitos <= n em MPI, usando apenas primitivas coleticas para comm

*/

#include <stdio.h>
#include "mpi.h"

#define MAX 100

int main( int argc, char *argv[] ){

    int my_rank; /* Identificador do processo */
    int proc_n; /* Número de processos */
    int root = 0; /* Processo raiz */
    

    MPI_Init(&argc , & argv);    

    return 0;

}