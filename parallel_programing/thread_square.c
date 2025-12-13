#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void* square(void* arg){
int number = *(int*)arg;
int *sqr= malloc(sizeof(int));
*sqr= number*number;
return (void*)sqr;
}

int main(){
pthread_t t1,t2;
int n1=2,n2=4;
if(pthread_create(&t1,NULL,square,&n1)!=0){
    return 1;
}
if(pthread_create(&t2,NULL,square,&n2)!=0){
    return 1;
}
void *ret1,*ret2;
pthread_join(t1,&ret1);
pthread_join(t2,&ret2);
printf("%d\n",*(int*)ret1);
printf("%d\n",*(int*)ret2);

free(ret1);
free(ret2);




    return 0;
}