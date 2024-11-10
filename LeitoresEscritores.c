#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reader_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int reader_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;
    pthread_mutex_lock(&reader_count_mutex);
    reader_count++;
    if (reader_count == 1)
        pthread_mutex_lock(&resource_mutex);
    pthread_mutex_unlock(&reader_count_mutex);

    printf("Leitor %d lendo...\n", id);
    sleep(1); 

    pthread_mutex_lock(&reader_count_mutex);
    reader_count--;
    if (reader_count == 0)
        pthread_mutex_unlock(&resource_mutex);
    pthread_mutex_unlock(&reader_count_mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    pthread_mutex_lock(&resource_mutex);

    printf("Escritor %d escrevendo...\n", id);
    sleep(1); 

    pthread_mutex_unlock(&resource_mutex);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], NULL, writer, &ids[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);

    return 0;
}
