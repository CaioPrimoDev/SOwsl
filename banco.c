#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 5
#define OPS_PER_THREAD 1000

double saldo = 1000.0;            // Conta bancária global
long successful_ops = 0;          // Contador de operações bem-sucedidas
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *transaction(void *arg) {
    for (int i = 0; i < OPS_PER_THREAD; i++) {
        // Gera valor aleatório entre 0.00 e 9.99
        double num = (rand() % 1000) / 100.0;
        int type = rand() % 2;  // 0 = saque, 1 = depósito

        pthread_mutex_lock(&mutex);
        if (type == 0) {
            // SAQUE: só executa se houver saldo suficiente
            if (saldo >= num) {
                saldo -= num;
                successful_ops++;
            }
        } else {
            // DEPÓSITO: sempre aceito
            saldo += num;
            successful_ops++;
        }
        pthread_mutex_unlock(&mutex);

        // Pequeno atraso para simular processamento
        usleep(100);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Inicializa gerador de números aleatórios
    srand(time(NULL));

    // Cria threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, transaction, NULL) != 0) {
            perror("Erro ao criar thread");
            exit(EXIT_FAILURE);
        }
    }

    // Aguarda término das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Exibe resultados finais
    printf("Saldo final: %.2f\n", saldo);
    printf("Operações bem-sucedidas: %ld\n", successful_ops);

    // Destrói mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

