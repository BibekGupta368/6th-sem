#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdbool.h>

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0 ){
        close(sockfd);
        printf("socket binding failed....\n");
        return 1;
    }
    if(listen(sockfd,3)<0){
        close(sockfd);
        printf("listen()failed....\n");
        return 1;
    }
    struct sockaddr_in client_addr;
    int client_len=sizeof(client_addr);
    int client_sockfd=accept(sockfd,(struct sockaddr*)&client_addr,&client_len);
    bool check;
    do{
        check=true;
        char buf[100];
        int rbytes=recv(client_sockfd,&buf,100,0);
        if(strcmp(buf,"exit")==0){
            check=false;
        }
        else{
            printf("rbytes:%d\n",rbytes);
            printf("Message from client:%s\n",buf);
            char msg[100]= "Hello from server";
            int sbytes=send(client_sockfd,&msg,sizeof(msg),0);
        }

    }while(check);
    printf("Socket closing....\n");
    close(sockfd);
    return 0;
}