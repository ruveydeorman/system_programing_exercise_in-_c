#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/un.h>
#include<string.h>

int main(int argc,char *argv[]){

    if(argc < 2){
        fprintf(stderr,"kullanimi:%s\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    int client_sock = socket(AF_UNIX,SOCK_STREAM,0);
    struct sockaddr_un addr;
    memset(&addr,0,sizeof(addr));
    addr.sun_family=AF_UNIX;
    strcpy(addr.sun_path,"/tmp/arg.sock");
    if(connect(client_sock,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("connect");
        close(client_sock);
        exit(EXIT_FAILURE);
    }
    write(client_sock,argv[1],strlen(argv[1]));
    close(client_sock);
    return 0;
}
