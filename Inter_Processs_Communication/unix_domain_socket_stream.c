#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/un.h>
#include<string.h>

int main(){
 int sock = socket(AF_UNIX, SOCK_STREAM,0);  //dinleme socketi yalnızca gelen bağlantıları dinler ve bi adrese bağlarız
 if(sock==-1){
    perror("socket");
    exit(EXIT_FAILURE);
 }
 struct sockaddr_un local;
 local.sun_family=AF_UNIX;
 strcpy(local.sun_path,"/tmp/mysocket.sock");
 unlink(local.sun_path);  //eğer önceden oluşturulmuşsa sileriz
 if(bind(sock,(struct sockaddr*)&local,sizeof(local))==-1){  //bağlama kısmında hata veririse socketi kapat
    perror("bind");
    close(sock);
    exit(EXIT_FAILURE);
 }
 if(listen(sock,5)==-1){  // gelecek olan bağlantıları dinle
    perror("listen");
    close(sock);
    unlink(local.sun_path);
    exit(EXIT_FAILURE);
 }
 
 printf("sunucu %s adresini dinliyor..\n",local.sun_path);

pid_t pid = fork();  //çocuk süreç server parent process client gibi davranıcak ve arasındaki iletişimi sağlamak için unix domain socketlerini kullanıcaz bağımsız processler arasında da yapabiliriz


if(pid == -1){
    perror("fork");
    close(sock);
    unlink(local.sun_path);
    exit(EXIT_FAILURE);
}
if(pid == 0){  //child process server 
    int client_fd = accept(sock,NULL,NULL);  //accept fonksionu ile sock soketine bağlanırız ve bu fonksiyon bir fd döndürrü bu fd üzerinden veri alışverişi yaparız 
    if(client_fd==-1){
        perror("accept");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("sunucu: istemci bağlandi\n");

    char buffer[256];
    ssize_t bytesread = read(client_fd,buffer,sizeof(buffer)-1);  //read fonksiyonu ile accept kısmında client_fd ye atadığımız fd üzerinden okuma yaparız istemciden gelen mesağı okuruz ve bu fonksiyon okunan byte sayısını döndürür
    if(bytesread == -1){
        perror("read");
    }else{
        buffer[bytesread]='\0';
        printf("istemciden gelen %s\n",buffer);


        //yanıt gönder
        const char* response = "hello client";   
        write(client_fd,response,strlen(response));  //yine client_fd üzerinden sunucuya mesaj göndeririz 
        printf("sunucu: yanit gönderildi.\n");
    }
    close(client_fd);  //işimiz bittiğinde sock ve client_fd kapatırız  sun_pathi de sileriz
    close(sock);
    unlink(local.sun_path);
    exit(EXIT_SUCCESS);  //başarılı çıkış

}
sleep(1);
  
        int client_sock = socket(AF_UNIX, SOCK_STREAM, 0);  //bir istemci soketi oluştururuz bu soketi dinleme soketine bağalrız 
        if(client_sock == -1) {
            perror("istemci socket");
            exit(EXIT_FAILURE);
        }
if(connect(client_sock,(struct sockaddr*)&local,sizeof(local))==-1){  
    perror("connect");
    close(client_sock);
    exit(EXIT_FAILURE);
}
printf("istemci: sunucuya bğlandik.\n");
const char* message ="hello server";
write(client_sock,message,strlen(message));  //mesajı client_socka yazarız strlen() ile null karakter hariç stringin uzunlugunu alır.çalışma zamanında hesaplanır
printf("istemci: mesaj gönderildi\n");

char buff[256];
ssize_t bytes_read=read(client_sock,buff,sizeof(buff)-1);  //read fonksiyonunda sizeof() ile buff ın bellekte kapladığı byte sayısını alırız.derleme zamanında belirlenir
buff[bytes_read]='\0';
printf("istemci: sunucudan gelen :%s\n",buff);
close(sock);
return 0;

}
