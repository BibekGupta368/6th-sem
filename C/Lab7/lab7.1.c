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

    if(connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        close(socketfd);
        printf("Server connection failed...\n");
        return 1;
    }
    else{
        printf("Server connection successful...\n");
    }  


    while(true){
        
        char buf[100];
        char msg[100];
        printf("Enter your message: ");
        fgets(msg, 100, stdin);

        int sbytes = send(socketfd, &msg, sizeof(msg), 0);
        printf("sbytes: %d\n", sbytes);
        

        //! To-Do: Receive data from the server
        int rbytes = recv(socketfd, &buf, 100, 0);
        printf("Message from server: %s\n", buf);

        
    }
    close(socketfd);
    return 0;
}