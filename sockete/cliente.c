#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in servidor;
    char mensagem[2000];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = inet_addr("172.16.20.97");
    servidor.sin_port = htons(8888);

    connect(sock, (struct sockaddr *)&servidor, sizeof(servidor));

    while (1) {
        printf("Você: ");
        fgets(mensagem, sizeof(mensagem), stdin);
        send(sock, mensagem, strlen(mensagem), 0);
        memset(mensagem, 0, sizeof(mensagem));
        recv(sock, mensagem, sizeof(mensagem), 0);
        printf("Servidor: %s", mensagem);
    }

    close(sock);
    return 0;
}
