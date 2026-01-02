#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/un.h>
#include<string.h>

int main(){
    int sock = socket(AF_UNIX,SOCK_STREAM,0);
    int client_fd;
    struct sockaddr_un local;
    memset(&local,0,sizeof(local));
    local.sun_family=AF_UNIX;
    strcpy(local.sun_path,"/tmp/arg.sock");
    unlink(local.sun_path);
    if(bind(sock,(struct sockaddr*)&local,sizeof(local))==-1){
        perror("bind");
        close(sock);
        exit(EXIT_FAILURE);
    }
    listen(sock,10);
    while(1){
        client_fd = accept(sock,NULL,NULL);
        if(client_fd==-1){
            perror("accept");
            continue;
        }
        printf("sunucu : istemci bağlantisi kabul edildi..\n");
        while(1){
        char buffer[256];
        ssize_t read_byte = read(client_fd,buffer,sizeof(buffer)-1);
        if(read_byte>0){
            buffer[read_byte]='\0';
            printf("sunucu:istemciden alinan mesaj:%s\n",buffer);
        }
        close(client_fd);
    }
    }

    
    close(sock);
    unlink(local.sun_path);
}
