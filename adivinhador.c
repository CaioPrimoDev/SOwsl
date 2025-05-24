#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#define SHM_NAME "/mem_numero"
#define SIZE sizeof(int)

int main() {
    int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    int* ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    int numero_correto = *ptr;
    int tentativa;

    printf("Tente adivinhar o numero entre 1 e 100:\n");
    do {
        printf("Digite sua tentativa: ");
        scanf("%d", &tentativa);

        if (tentativa < numero_correto) {
            printf("Muito baixo. Tente novamente.\n");
        } else if (tentativa > numero_correto) {
            printf("Muito alto. Tente novamente.\n");
        } else {
            printf("Parabens! Voce acertou!\n");
        }
    } while (tentativa != numero_correto);

    munmap(ptr, SIZE);
    close(fd);

    return 0;
}
