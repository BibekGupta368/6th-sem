#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;

    // Create Socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Socket creation failed...\n");
        return 1;
    }

    // memset(&server_addr, 0, sizeof(server_addr));
    // memset(&client_addr, 0, sizeof(client_addr));


    server_addr.sin_family = AF_INET; // IPv4
    //! server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        printf("Socket binding failed...\n");
        return 1;
    }

    int len, n;

    len = sizeof(client_addr); // Length of client's address

    n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &len);
    buffer[n] = '\0';
    printf("Client: %s\n", buffer);
    const char *response ;
    sendto(sockfd, response, strlen(response), 0, (const struct sockaddr *) &client_addr, len);
    printf("Response sent to client\n");

    close(sockfd);
    return 0;
}