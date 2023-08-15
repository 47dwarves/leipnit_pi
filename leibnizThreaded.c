#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct
{
    int rank;
    double total;
} thread_data;

thread_data *td;

int NUM_THREADS;
long int ITERATIONS;

void *help_pi(void *arg)
{
    int thread_rank = *(int *)arg;
    double total = 0.0;
    int k = thread_rank;

    while (k < ITERATIONS)
    {
        total += pow(-1, k) / (2.0 * k + 1.0);
        k += NUM_THREADS;
    }

    td[thread_rank].total = total;
}

double calculate_pi()
{
    pthread_t *thread_ids = malloc(NUM_THREADS * sizeof(pthread_t));
    td = malloc(NUM_THREADS * sizeof(thread_data));

    int rank = 0;
    int err;

    while (rank < NUM_THREADS)
    {
        td[rank].rank = rank;

        err = pthread_create(&(thread_ids[rank]), NULL, help_pi, (void *)&(td[rank].rank));
        if (err != 0)
        {
            printf("Can't create thread. Error: %d\n", err);
            return 0.0;
        }

        rank++;
    }

    rank = 0;
    while (rank < NUM_THREADS)
    {
        pthread_join(thread_ids[rank], NULL);
        rank++;
    }

    double pi = 0.0;
    rank = 0;
    while (rank < NUM_THREADS)
    {
        pi += td[rank].total;
        rank++;
    }

    free(thread_ids);
    free(td);

    return pi * 4;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <num_threads> <iterations>\n", argv[0]);
        return 1;
    }

    NUM_THREADS = atoi(argv[1]);
    ITERATIONS = atoi(argv[2]);

    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    double pi = calculate_pi();

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Calculated Pi: %.50lf\n", pi);
    printf("Elapsed Time: %.10f seconds\n", elapsed);

    return 0;
}

