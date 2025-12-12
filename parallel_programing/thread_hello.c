#include<stdio.h>
#include<pthread.h>
#include<string.h>
void* hello(void* arg){
    char* arr= (char*)arg;
    for(int i=0;i<5;i++){
        printf("ID: %lu Hello %s\n",pthread_self(),arr);
    }
    return NULL;
}


int main(){
  pthread_t thread1,thread2;
  char ch1[]="thread1",ch2[]="thread2";
  if(pthread_create(&thread1,NULL,hello,&ch1)!=0){
    return 1;
  }
  if(pthread_create(&thread2,NULL,hello,&ch2)!=0){
    return 1;
  }
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);


    return 0;
}