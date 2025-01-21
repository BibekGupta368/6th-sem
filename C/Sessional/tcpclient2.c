#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdbool.h>
#define SIZE 100

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0 ){
        close(sockfd);
        printf("socket connection failed....\n");
        return 1;
    }
    char buf[100];
    char msg[SIZE];
    bool check;
    do{
        check=true;
       printf("Enter your message\n");
       scanf("%s",msg);
       if(strcmp(msg,"exit")==0){
            check=false;
            printf("false\n");   
        }
        int sbytes=send(sockfd,&msg,sizeof(msg),0);
        printf("sbytes:%d\n",sbytes);
        int rbytes=recv(sockfd,&buf,100,0);
        printf("Message from server:%s\n",buf);   

    }while(check);
    close(sockfd);
    return 0;
}