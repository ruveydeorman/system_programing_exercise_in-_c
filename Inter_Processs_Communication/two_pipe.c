#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
int main(){
   int fds1[2];
   int fds2[2];
   pipe(fds1);
   pipe(fds2);
   if(!fork()){
    
    close(fds1[1]);//parent yazacak child okuyacak
    close(fds2[0]); //child yazacak parent okuyacak 
    char buff[1024];
    size_t readed;
    if((readed=read(fds1[0],buff,sizeof(buff)-1))>0){
        buff[readed]='\0';
        printf("message received from the parent:%s\n",buff);
    }
    //parenta mesaj gönder
    char *reply = "hello parent!";
    write(fds2[1],reply,strlen(reply)); //stdouta göndermeden mesaj gönderdik.

    //boruları kapatıyoruz
    close(fds1[0]); //okuma yaptık ve kapattık 
    close(fds2[1]); // yazma yaptık ve kapattık
    exit(0);
   }
   close(fds1[0]); //yazma yapılacak okumayı kapat
   close(fds2[1]); //okuma yapılıcak yazmayı kapat
    
   //childa mesaj gönder
   char *send ="hello child!";
   write(fds1[1],send,strlen(send));
   char buffer[1024];
   size_t bytes_read;
   if((bytes_read=read(fds2[0],buffer,sizeof(buffer)-1))>0){
        buffer[bytes_read]='\0'; //son elemanı null yapmayı unutma
        printf("message received from child:%s\n",buffer);
   }
   close(fds1[1]);
   close(fds2[0]);
   wait(NULL);

} 
