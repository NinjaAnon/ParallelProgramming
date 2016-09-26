#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>

void findSumOfArray(int * array, int array_size) {
    int i;
    struct timeval tv;
    double start_t, end_t;
    gettimeofday(&tv, 0);
    start_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    int * temp_array = (int *) malloc(sizeof (double)*array_size);
#pragma omp parallel
    {
        int check = array_size;
        while (check / 2 > 0) {
#pragma omp for
            for (i = 0; i < array_size; i++) {
                temp_array[i] = array[2 * i] + array[2 * i + 1];
            }

#pragma omp for
            for (i = 0; i < array_size / 2; i++) {
                array[i] = temp_array[i];
            }
            check = check / 2;
        }
    }
    gettimeofday(&tv, 0);
    end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    printf("Time taken : %lf and Sum of all element is %d \n", end_t - start_t, array[0]);
}

main(int argc, char **argv) {
    int *array, sum;
    struct timeval tv;
    double start_t, end_t;
    int array_size, i, j, noOfThreads;
    omp_set_num_threads(2);
    printf("Enter the size(n) of array. Please note n=2^x where x is any positive integer\n");
    scanf("%d", &array_size);
    noOfThreads = 2;
    array = (int *) malloc(sizeof (double)*array_size);

    for (j = 0; j < array_size; j++) {
        printf("Enter value for %d-th element", j);
        scanf("%d", &array[j]);
    }

    findSumOfArray(array, array_size);






}
