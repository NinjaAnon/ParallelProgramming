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
    double *original_matrix;
    int i, k, num_rows, num_columns, id, no_threads;
    double time;
    omp_set_num_threads(2);

    printf("\nEnter the Order of the First matrix...\n");
    scanf("%d %d", &num_rows, &num_columns);


    original_matrix = (double*) malloc((num_rows * num_columns) * sizeof (double));



    //Taking Input for Matrix 
    for (i = 0; i < num_rows * num_columns; i++) {
        printf("Enter the value of %d-th element", i);
        scanf("%lf", &original_matrix[i]);
    }

    printf("Original Matrix\n\n");
    for (i = 0; i < num_columns; i++) {
        for (k = 0; k < num_rows; k++)
            printf("%lf \t", original_matrix[k + i * num_rows]);
        printf("\n");
    }


    findTranspose(num_rows, num_columns, original_matrix);
}






