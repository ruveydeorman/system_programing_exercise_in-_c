#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    int fds[2];
    pid_t pid;

    if( pipe(fds)==-1){
        perror("pipes");
        exit(EXIT_FAILURE);
    }
    pid=fork();
    if(pid==-1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid==0){
        close(fds[0]); //sadece yazma işlemi yapılacağı için okuma ucunu kapatırız.
        dup2(fds[1],1);//stdcout u borunun yazma ucuna yönlendir.
        close(fds[1]);  //yazma ucunu kapatırız çünkü artık stdout ile erişiriz
        execlp("ls","ls",NULL); // ls normalde stdout'a (ekran) yazı yapar. Ancak biz stdout'u borunun yazma ucuna yönlendirdiğimiz için, ls programının çıktısı ekrana değil, boruya yazılır. Ebeveyn süreç de borunun okuma ucundan bu çıktıyı okuyabilir.
    }
    if(pid){
        close(fds[1]);  //borunun yazma ucu kapatılır
        char buffer[1024];  //veriyi okumak için
        ssize_t bytes_read;  //read fonksiyonundan okunan veri boyutunu almak içn
        while((bytes_read=read(fds[0],buffer,sizeof(buffer)-1))>0){ 
            buffer[bytes_read]='\0'; //son karakteri null yaparız
            printf("child process output: %s\n ",buffer); //ekrana yazdırırız
        } 
        close(fds[0]); //okuma ucu kapatılır
        wait(NULL);
    }

} 
