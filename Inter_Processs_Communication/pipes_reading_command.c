#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
int main(){
   int fds[2];
   pipe(fds);
   if(!fork()){
        close(fds[0]);
        dup2(fds[1],1);
        close(fds[1]);
        execlp("ps","ps","aux",NULL);
   }
   close(fds[1]);
   char buff[4096];
   int read_byte;
   if((read_byte=(read(fds[0],buff,sizeof(buff)-1)))>0){
    buff[read_byte]='\0';
    printf("%s\n",buff);
   }
   return 0;
} 
