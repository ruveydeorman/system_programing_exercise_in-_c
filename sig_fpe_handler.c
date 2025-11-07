#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void sig_fpe_handler(int sig){
    printf("floating point error!...\n");
    exit(1);
}
int main(){
    signal(SIGFPE,&sig_fpe_handler);
    int a = 10, b = 0;
    printf("%d",a/b);
    return 0;
}