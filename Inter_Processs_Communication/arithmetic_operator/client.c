#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/un.h>
#include<string.h>
#include<stdio.h>

int main(int argc,char*argv[]){
    int client_sock = socket(AF_UNIX,SOCK_STREAM,0);
    struct sockaddr_un address;
    memset(&address,0,sizeof(address));
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path,"/tmp/s.sock");
    connect(client_sock,(struct sockaddr*)&address,sizeof(address));
    write(client_sock,argv[1],strlen(argv[1]));
    char readed_message[256];
    int readed_bytes =read(client_sock,readed_message,sizeof(readed_message));
    printf("sonuc: %s\n",readed_message);
    


    close(client_sock);
    return 0;

}
