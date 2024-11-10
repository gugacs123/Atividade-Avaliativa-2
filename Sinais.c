#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig) {
    printf("Thread recebeu sinal %d\n", sig);
}

void* thread_func(void* arg) {
    signal(SIGUSR1, signal_handler);
    printf("Esperando sinal...\n");
    pause();
    printf("Sinal recebido!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    sleep(1);
    printf("Enviando sinal para a thread\n");
    pthread_kill(thread, SIGUSR1);

    pthread_join(thread, NULL);
    return 0;
}
