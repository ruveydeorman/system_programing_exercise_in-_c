#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
int main(){
    int server_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family= AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(7000);
    bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(server_sock,10);
    while(1){
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&client_len);
        printf("yeni bağlanti: %s : %d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        int pid = fork();
        if(pid == 0){
            char buffer[1064];
            close(server_sock);
            int bytes_received;
            while((bytes_received = recv(client_sock,buffer,sizeof(buffer),0))>0){
                send(client_sock,buffer,bytes_received,0);
            }
            close(client_sock);
            exit(0);
        }else{
            close(client_sock);
            waitpid(-1,NULL,WNOHANG);
        }
}
    close(server_sock);
    return 0;
}
