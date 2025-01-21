#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;


    if(bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        close(socketfd);
        printf("Socket binding failed...\n");
        return 1;
    }
    else{
        printf("Socket binding successful...\n");
    }    

    if(listen(socketfd, 5) < 0){
        close(socketfd);
        printf("listen() failed...\n");
        return 1;
    }
    else{
        printf("Server is listening for connnections...\n");
    }
    

    while(true){
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        int client_sockfd = accept(socketfd, (struct sockaddr *) &client_addr, &client_len);
        
        if(client_sockfd < 0){
            printf("Client couldn't connect...\n");
            continue;
        }
        printf("Connection accepted from client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        int childpid = fork();
        if(childpid == 0){
    
            while(true){
                char buf[100];
    
                int rbytes = recv(client_sockfd, &buf, 100, 0);
                
                printf("rbytes: %d\n", rbytes);
                printf("Message from client: %s\n", buf);

                char msg[100] = "Hello from Server";
                int sbytes = send(client_sockfd, &msg, sizeof(msg), 0);
            }
        }


 
    }
}