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
    double start_t, end_t;
    struct timeval tv;

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
            matrix[i][j]=rand()%100;
        }
    printf("Matrix Generated : \n");
    for (i = 0; i < num_rows; i++)
{
        for (j = 0; j < num_columns; j++) {
            printf("%d\t",matrix[i][j]);
        }printf("\n");}
    //Taking Input for vector
    for (i = 0; i < num_columns; i++) {
        vector[i]=rand()%100;
    }
   
   printf("Vector Generated :");
   for (i = 0; i < num_columns; i++) {
        printf("%d \t",vector[i]);
    }
    
    gettimeofday(&tv, 0);
    start_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    findVectorMatrixMultiplication(matrix, vector, num_rows, num_columns);
    gettimeofday(&tv, 0);
    end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    end_t = end_t - start_t;
    printf("Time taken: %f ", end_t);
}






