#include<stdio.h>
#include<stdlib.h>
#include <omp.h>

void findTranspose(int num_rows, int num_columns, double * original_matrix) {
    int i, n, dim, k;
    dim = num_rows*num_columns;
    double * transposed_matrix = (double*) malloc((num_rows * num_columns) * sizeof (double));

#pragma omp parallel for private(n)
    for (n = 0; n < dim; n++) {

        int i = n / num_columns;
        int j = n % num_columns;
        transposed_matrix[j * num_rows + i] = original_matrix[n];
    }

    printf("Transposed Matrix\n\n");
    for (i = 0; i < num_columns; i++) {
        for (k = 0; k < num_rows; k++)
            printf("%lf \t", transposed_matrix[k + i * num_rows]);
        printf("\n");
    }



}

void main() {
    double start_t, end_t;
    struct timeval tv;
    double *original_matrix;
    int i, k, num_rows, num_columns, id, no_threads;
    double time;
    omp_set_num_threads(2);

    printf("\nEnter Order of the Square Matrix...\n");
    scanf("%d", &num_rows);
    
    num_columns=num_rows;

    original_matrix = (double*) malloc((num_rows * num_columns) * sizeof (double));



    //Taking Input for Matrix 
    for (i = 0; i < num_rows * num_columns; i++) {
        original_matrix[i]=rand()%100;
    }

    printf("Original Matrix\n\n");
    for (i = 0; i < num_columns; i++) {
        for (k = 0; k < num_rows; k++)
            printf("%lf \t", original_matrix[k + i * num_rows]);
        printf("\n");
    }

    gettimeofday(&tv, 0);
    start_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    findTranspose(num_rows, num_columns, original_matrix);
    gettimeofday(&tv, 0);
    end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    end_t = end_t - start_t;
    printf("Time taken: %f ", end_t);

}






