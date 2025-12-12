#include<stdio.h>
#include<pthread.h>

void* print_number(void* arg){
    int num=*(int*)arg;
    printf("gönderilen sayi = %d\n",num);
    return NULL;

}
int main(){
   pthread_t thread1,thread2;
   int num1=5,num2=10;
   //ilk threadi oluştur
   if(pthread_create(&thread1,NULL,print_number,&num1)!=0){
    fprintf(stderr,"thread1 not created\n");
    return 1;
   }
   if(pthread_create(&thread2,NULL,print_number,&num2)!=0){
    fprintf(stderr,"thread2 not created.\n");
    return 1;
   }
   pthread_join(thread1,NULL);
   pthread_join(thread2,NULL);
   


    return 0;
}
