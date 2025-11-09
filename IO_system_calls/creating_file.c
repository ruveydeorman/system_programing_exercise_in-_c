#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
int main(){ 
  int fd = ("text.txt",0640);
  if(fd == -1){
    fprintf(stderr,"error:%s\n",strerror(errno));
    return 1;
  }
  printf("file is created succesfully..\n");
  close(fd);
    return 0;
}
