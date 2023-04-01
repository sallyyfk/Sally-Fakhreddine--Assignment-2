#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 4
#define NUM_THREADS 4

int A[SIZE][SIZE];
int B[SIZE][SIZE];
int C[SIZE][SIZE];

int step_i = 0;

void* multi(void* arg){
    int i = step_i++;
    for (int j = 0; j < SIZE; j++)
        for (int k = 0; k < SIZE; k++)
            C[i][j] += A[i][k] * B[k][j];
    pthread_exit(NULL);
}

int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    printf("Matrix A:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", B[i][j]);
        printf("\n");
    }

    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, multi, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    gettimeofday(&end, NULL);
    double time = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    printf("\nMatrix C:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    printf("\nExecution time: %f seconds\n", time);
    return 0;
}
