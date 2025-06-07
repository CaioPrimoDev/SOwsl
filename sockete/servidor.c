#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd, client_sock;
    struct sockaddr_in servidor, cliente;
    char mensagem[2000];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(8888);

    bind(sockfd, (struct sockaddr *)&servidor, sizeof(servidor));
    listen(sockfd, 1);
    socklen_t c = sizeof(struct sockaddr_in);
    client_sock = accept(sockfd, (struct sockaddr *)&cliente, &c);

    while (1) {
        memset(mensagem, 0, sizeof(mensagem));
        recv(client_sock, mensagem, sizeof(mensagem), 0);
        printf("Cliente: %s", mensagem);
        printf("Você: ");
        fgets(mensagem, sizeof(mensagem), stdin);
        send(client_sock, mensagem, strlen(mensagem), 0);
    }

    close(sockfd);
    return 0;
}
