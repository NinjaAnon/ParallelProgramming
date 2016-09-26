
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <time.h>

void findRoot(int * successor, int k, int N) {

    int i;

    double start_t, end_t;

    struct timeval tv;
    int * successor_next = (int *) malloc(N * sizeof (int));


    while (1) {


        printf("Enter the node whose parent you want to find.Enter -1 to exit ");
        scanf("%d", &k);
        if (k == -1)
            break;


        gettimeofday(&tv, 0);
        start_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;



        while (1) {


#pragma omp parallel for schedule(static,8)
            for (i = 0; i < N; i++) {
                successor_next[i] = successor[successor[i]];
            }

            if (successor[k] == successor_next[k])
                break;
#pragma omp parallel for schedule(static,8)
            for (i = 0; i < N; i++) {
                successor[i] = successor_next[i];
            }

        }
        gettimeofday(&tv, 0);
        end_t = (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
        end_t = end_t - start_t;
        printf("The root of this element is %d  ", successor[k]);
        printf("Time taken: %f ", end_t);

    }

}

void main() {
    int i, k, N, num_threads;


    printf("Enter the number of nodes");
    scanf("%d", &N);

    omp_set_num_threads(2);
    num_threads = omp_get_num_threads();
    printf("Number of threads running are %d", num_threads);



    int * successor = (int *) malloc(N * sizeof (int));

    for (i = 0; i < N; i++) {
        printf("Enter the parent pointer value for %d-th node", i);
        scanf("%d", &successor[i]);

    }

    findRoot(successor, k, N);




}
