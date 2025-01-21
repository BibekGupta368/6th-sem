#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#define SIZE 100

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Socket creation failed...\n");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        printf("Server connection failed...\n");
        return 1;
    }

    char buf[SIZE];
    bool check;
    int size;
    char arr[SIZE];
    do {
        check = true;
        printf("Enter the size of array (max %d): ", SIZE);
        scanf("%d", &size);
        if (size <= 0 || size > SIZE) {
            printf("Invalid size.\n");
            continue;
        }

        printf("Enter the elements:\n");
        for (int i = 0; i < size; i++) {
            scanf(" %c", &arr[i]);
        }
        arr[size] = '\0';

        int sbytes = send(sockfd, arr, size, 0);
        if (sbytes < 0) {
            printf("send() failed...\n");
            break;
        }
        printf("sbytes: %d\n", sbytes);

        int rbytes = recv(sockfd, buf, SIZE, 0);
        if (rbytes <= 0) {
            printf("recv() failed or server closed connection...\n");
            break;
        }
        buf[rbytes] = '\0';
        printf("Message from server: %s\n", buf);

        printf("Type 'exit' to end or press Enter to continue: ");
        scanf(" %[^\n]", buf);
        if (strcmp(buf, "exit") == 0) {
            check = false;
        }
    } while (check);

    close(sockfd);
    printf("Connection closed.\n");
    return 0;
}