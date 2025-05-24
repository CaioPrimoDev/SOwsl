#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#define SHM_NAME "/mem_numero"
#define SIZE sizeof(int)

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(fd, SIZE) == -1) {
        perror("ftruncate");
        close(fd);
        exit(1);
    }

    int* ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    int numero;
    do {
        printf("Digite um numero entre 1 e 100: ");
        scanf("%d", &numero);
    } while (numero < 1 || numero > 100);

    *ptr = numero;

    printf("Numero %d gravado na memoria compartilhada.\n", numero);
    printf("Pressione Enter para sair e remover a memoria...");
    getchar(); getchar();

    munmap(ptr, SIZE);
    close(fd);
    shm_unlink(SHM_NAME); // Remove a memória compartilhada

    return 0;
}
