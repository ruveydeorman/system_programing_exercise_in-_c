
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/un.h>
#include<string.h>
#include<stdio.h>
int main(){
    int sock=socket(AF_UNIX,SOCK_STREAM,0);
    struct sockaddr_un local;
    memset(&local,0,sizeof(local));
    local.sun_family=AF_UNIX;
    strcpy(local.sun_path,"/tmp/s.sock");
    unlink(local.sun_path);
    bind(sock,(struct sockaddr*)&local,sizeof(local));

    listen(sock,10);
    while(1){
        int client_fd = accept(sock,NULL,NULL);
        char buffer[256];
        ssize_t bytes_read = read(client_fd,buffer,sizeof(buffer)-1);
        int num1 ,num2;
        char operator;
        double result=0.0;
        char message[256];
        if(sscanf(buffer,"%d%c%d",&num1,&operator,&num2)!=3){
            char *errmessage = "geçersiz format";
            write(client_fd, errmessage,strlen(errmessage));
        }else{
            switch(operator){
                case '+': result= num1+num2;break;
                case '-': result = num1-num2;break;
                case '/' : 
                    if(num2 == 0) {
                        char *error = "Hata: Sifira bolme!";
                        write(client_fd, error, strlen(error));
                        break; 
                    }
                    result = (double)num1 / num2;  
                     break;
                case '*': result = num1* num2;
                break;
                default :
                    printf("geçersiz operator.\n");
                    break;
                    
            }
           
        }
        sprintf(message,"%.2lf",result);
        write(client_fd,message,strlen(message));
        close(client_fd);
       
    }
    close(sock);
    unlink(local.sun_path);
    return 0;
}
