#include <stdio.h>
#include <stdlib.h>

/* Operation types
 * 
 * 0 - default
 * 1 - loop interchange
 * 2 - loop unrolling
 */

int **createMatrix(int size);
void populateMatrix(int **matrix, int size);
void freeMatrix(int **matrix, int rows);

int** defaultMultiplication(int **matrix1, int **matrix2, int size);
int** interchange();
int** unrolling();

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf ("Too few arguments\n"); 
        return EXIT_FAILURE;
    }

    int operationType = atoi(argv[1]);
    int matrixSize = atoi(argv[2]);

    int **matrix1 = createMatrix(matrixSize);
    int **matrix2 = createMatrix(matrixSize);
    int **result;

    populateMatrix(matrix1, matrixSize);
    populateMatrix(matrix2, matrixSize);

    switch (operationType) {
        case 0:
            result = defaultMultiplication(matrix1, matrix2, matrixSize);
            break;
        case 1:
            result = interchange(matrix1, matrix2, matrixSize);
            break;
        case 2:
            result = unrolling(matrix1, matrix2, matrixSize);
            break;
        default:
            printf("Invalid operation type\n");
            break;
    }
    
    freeMatrix(matrix1, matrixSize);
    freeMatrix(matrix2, matrixSize);
    freeMatrix(result, matrixSize);

    return EXIT_SUCCESS;
}

int** defaultMultiplication(int **matrix1, int **matrix2, int size) {
    int **result = createMatrix(size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];

    return result;
 }

int** interchange(int **matrix1, int **matrix2, int size) {
    int **result = createMatrix(size);

    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++)
            for (int j = 0; j < size; j++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];

    return result;
}

int** unrolling(int **matrix1, int **matrix2, int size) {
    int **result = createMatrix(size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k += 2){
                result[i][j] += matrix1[i][k]   * matrix2[k][j];
                result[i][j] += matrix1[i][k+1] * matrix2[k+1][j];
            }

    return result;
}

int **createMatrix(int size) {
    int **matrix = malloc(size * sizeof(int *));
    
    for (int i = 0; i < size; i++)
        matrix[i] = malloc(size * sizeof(int));

    return matrix;
}

void populateMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand();

}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    
    free(matrix);
}
