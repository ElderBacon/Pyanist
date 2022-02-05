#include <cstdio>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int socketInit(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("socket error\n");
        exit(1);
    }
    printf("socket success\n");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // INADDR_ANY: 接受来自所有端口的连接

    if (bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        printf("bind error\n");
        exit(1);
    }
    printf("bind success\n");

    if (listen(sock, 5) == -1) {
        printf("listen error\n");
        exit(1);
    }
    printf("listen success\n");

    return sock;
}

//接收客户端请求
int socketAccept(int sock) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sock = accept(sock, (struct sockaddr *) &client_addr, &client_addr_size);
    if (client_sock == -1) {
        printf("accept error\n");
        exit(1);
    }
    printf("accept success\n");

    return client_sock;
}

int socketSend(int sock, const char *buf, int len) {
    int n = send(sock, buf, len, 0);
    if (n == -1) {
        printf("send error\n");
        exit(1);
    }
    printf("send success\n");

    return n;
}

int socketRecv(int sock, char *buf, int len) {
    int n = recv(sock, buf, len, 0);
    if (n == -1) {
        printf("recv error\n");
        exit(1);
    }
    printf("recv success\n");

    return n;
}

int socketClose(int sock) {
    close(sock);
    printf("close success\n");

    return 0;
}
