#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>

#define SERVER_IP "127.0.0.1"
#define SIZE 1024
int main(){
    int server_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family= AF_INET;
    server_addr.sin_port = htons(7000);
    inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr);
    connect(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));

    while(1){
        printf("ruve_server>");
        char buffer[SIZE];
        fgets(buffer,sizeof(buffer),stdin);
        if(strncmp(buffer,"exit",4)==0){
            break;
        }
        int bytes_sent = send(server_sock,buffer,strlen(buffer),0);
        int bytes_received = recv(server_sock,buffer,SIZE,0);
        buffer[bytes_received] ='\0';
        printf("sunucu: %s",buffer);
    }

    close(server_sock);
    printf("bağlanti kapatildi...\n");
    return 0;


}
