#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    const char *str1 = (const char *)a;
    const char *str2 = (const char *)b;

    int len_diff = strlen(str1) - strlen(str2);
    if (len_diff != 0) {
        return len_diff;
    }

    return strcmp(str1, str2);
}

int main()
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        printf("Socket creation failed...\n");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        close(socketfd);
        printf("Socket binding failed...\n");
        return 1;
    }

    if (listen(socketfd, 3) < 0) {
        close(socketfd);
        printf("listen() failed..\n");
        return 1;
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sockfd = accept(socketfd, (struct sockaddr*) &client_addr, &client_len);
    if (client_sockfd < 0) {
        close(socketfd);
        printf("accept() failed...\n");
        return 1;
    }

    bool check;
    do {
        check = true;
        char buff[100];
        int rbytes = recv(client_sockfd, buff, sizeof(buff), 0);
        if (rbytes <= 0) {
            break;
        }
        buff[rbytes] = '\0';

        if (strcmp(buff, "exit") == 0) {
            check = false;
        } else {
            printf("rbytes: %d\n", rbytes);
            printf("Message from client: %s\n", buff);

            char msg[100] = "Hello from server";
            qsort(buff, strlen(buff), sizeof(char), compare);

            int sbytes = send(client_sockfd, buff, strlen(buff), 0);
            if (sbytes <= 0) {
                printf("send() failed...\n");
                break;
            }
        }
    } while (check);

    printf("Socket closing...\n");
    close(client_sockfd);
    close(socketfd);
    return 0;
}