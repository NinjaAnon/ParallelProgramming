#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

void findPrefixSum(int *A, int n) {

    int i, h, j;

    int rows = (int) (log2(n));
    rows = rows + 1;
    int **B = (int **) malloc(rows * sizeof (int *));
    int **C = (int **) malloc(rows * sizeof (int *));

    for (i = 0; i < rows; i++) {
        B[i] = (int *) malloc((n + 1) * sizeof (int));
        C[i] = (int *) malloc((n + 1) * sizeof (int));
    }
#pragma omp parallel for schedule(static,4)
    for (i = 1; i < n + 1; i++) {
        B[0][i] = A[i];

    }



    for (h = 1; h <= ((int) (log2(n)) + 1); h++) {
        int t = n / (int) pow(2, h);

#pragma omp parallel for schedule(static,4)
        for (j = 1; j <= t; j++) {
            B[h][j] = B[h - 1][(2 * j) - 1] + B[h - 1][(2 * j)];
        }


    }

    for (h = ((int) log2(n) + 1); h >= 0; h--) {
        int t = n / (int) pow(2, h);


#pragma omp parallel for
        for (j = 1; j <= t; j++) {
            if ((j % 2) == 0) {
                C[h][j] = C[h + 1][j / 2];
            } else if (j == 1) {
                C[h][1] = B[h][1];
            } else {
                C[h][j] = C[h + 1][(j - 1) / 2] + B[h][j];
            }
        }

    }


    for (i = 1; i <= n; i++) {
        printf("\nPrefix sum till %d-th element is %d \n ", i, C[0][i]);
    }

}

void main() {
    int n, h, i;
    double start_t, end_t;
    struct timeval tv;
    printf("Enter value of n. Please note n=2^x where x is any positive integer\n");
    scanf("%d", &n);
    int *A = (int *) malloc((n + 1) * sizeof (int));

    omp_set_num_threads(2);
    for (i = 1; i < n + 1; i++) {
        A[i]=rand()%100;

    }
    printf("Original Array\n");
    for (i = 1; i < n + 1; i++) {
        printf("%d\t",A[i]);

    }
    gettimeofday(&tv, 0);
    start_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    findPrefixSum(A, n);
    gettimeofday(&tv, 0);
    end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    end_t = end_t - start_t;

    printf("Time taken: %f ", end_t);

}
