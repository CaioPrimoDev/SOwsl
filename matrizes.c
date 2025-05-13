#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Definindo o número de linhas e colunas
#define M 3 // Número de linhas de A e C
#define N 3 // Número de colunas de A e linhas de B
#define P 3 // Número de colunas de B e C

// Matrizes globais
int A[M][N];
int B[N][P];
int C[M][P];

// Função para calcular o elemento C[i][j]
void *multiplicacao_elemento(void *arg) {
    int i = ((int *)arg)[0];
    int j = ((int *)arg)[1];
    int soma = 0;

    // Calculando o valor de C[i][j]
    for (int k = 0; k < N; k++) {
        soma += A[i][k] * B[k][j];
    }
    C[i][j] = soma;

    return NULL;
}

// Função para inicializar as matrizes A e B
void inicializar_matrizes() {
    // Inicializando matriz A (exemplo)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j + 1; // Preenchendo com valores para testes
        }
    }

    // Inicializando matriz B (exemplo)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = i + j + 1; // Preenchendo com valores para testes
        }
    }
}

// Função para exibir uma matriz
void exibir_matriz(int matriz[M][P]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    pthread_t threads[M][P];

    // Inicializar as matrizes A e B
    inicializar_matrizes();

    // Criar uma thread para cada elemento de C
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            int *indices = malloc(2 * sizeof(int)); // Aloca memória para os índices
            indices[0] = i;
            indices[1] = j;

            // Criando a thread para calcular C[i][j]
            pthread_create(&threads[i][j], NULL, multiplicacao_elemento, (void *)indices);
        }
    }

    // Esperar que todas as threads terminem
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Exibir a matriz C
    printf("Matriz A:\n");
    exibir_matriz(A);
    printf("\nMatriz B:\n");
    exibir_matriz(B);
    printf("\nMatriz C (Produto de A e B):\n");
    exibir_matriz(C);

    return 0;
}

