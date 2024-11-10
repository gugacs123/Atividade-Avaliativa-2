#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t barrier;

void *task(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d: executando a primeira parte...\n", id);
    sleep(1);

    pthread_barrier_wait(&barrier);
    printf("Thread %d: passou pela barreira!\n", id);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int ids[5] = {1, 2, 3, 4, 5};

    pthread_barrier_init(&barrier, NULL, 5);

    for (int i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, task, &ids[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);

    pthread_barrier_destroy(&barrier);
    return 0;
}
