#include<stdio.h>
#include<stdlib.h>
#include <omp.h>

void findVectorMatrixMultiplication(int ** matrix, int *vector, int num_rows, int num_columns) {
    int j, i;
    int * product = (int*) calloc((num_rows), sizeof (int));
#pragma omp parallel shared(vector, matrix)
    {
#pragma omp for schedule(static , 8)
        for (j = 0; j < num_rows; j++) {
            int result = 0;
            for (i = 0; i < num_columns; i++) {
                result += vector[i] * matrix[j][i];
            }
            product[j] = result;
        }
    }

    printf("\n\nResult\n\n");

    for (j = 0; j < num_rows; j++)
        printf("%d\t", product[j]);

}

main() {
    int **matrix;
    int *vector;
    int i, j, n, num_rows, num_columns;

    double timeofday;
    omp_set_num_threads(2);

    printf("\nPlease enter the Order of the First matrix\n");
    scanf("%d %d", &num_rows, &num_columns);

    matrix = (int**) malloc(num_rows * sizeof (int*));

    for (i = 0; i < num_rows; i++)
        matrix[i] = (int*) malloc(num_columns * sizeof (int));

    vector = (int*) malloc((num_columns) * sizeof (int));

    //Taking input for matrix
    for (i = 0; i < num_rows; i++)
        for (j = 0; j < num_columns; j++) {
            printf("Enter value for (%d ,%d) -th element of matrix", i, j);
            scanf("%d", &matrix[i][j]);
        }
    //Taking Input for vector
    for (i = 0; i < num_columns; i++) {
        printf("Enter value for %d-th element of vector", i);
        scanf("%d", &vector[i]);
    }
    findVectorMatrixMultiplication(matrix, vector, num_rows, num_columns);

}






