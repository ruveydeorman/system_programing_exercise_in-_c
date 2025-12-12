#include<stdio.h>
#include<pthread.h>
 typedef struct {
      int begin;
      int end;
      int sum;
  } data;

void* summation(void* arg1){
    data* d= (data*)arg1;
    d->sum=0;
    for(int i= d->begin;i<=d->end;i++){
      d->sum +=i;
    }
    
}



int main(){
  
  data sec1={1,500,0};
  data sec2={501,1000,0};
  pthread_t t1,t2;
  if(pthread_create(&t1,NULL,summation,&sec1)!=0){
    return 1;
  }
  if(pthread_create(&t2,NULL,summation,&sec2)!=0){
    return 1;
  }
  
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  printf("first sumamtion(1 to 500):%d\n",sec1.sum);
  printf("second sumamtion(501 to 1000):%d\n",sec2.sum);
  printf("general sumamtion(1 to 1000):%d\n",sec1.sum+sec2.sum);
    return 0;
}