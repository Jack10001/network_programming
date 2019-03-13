#include<unistd.h>

#include<stdlib.h>

#include<stdio.h>

#include<sys/socket.h>

#include<arpa/inet.h>

#include<string.h>

#include<sys/select.h>

#include<fcntl.h>

#include<time.h>

#include<signal.h>



void errorHandling(const char* message);

void urgHandler(int signo);//信号处理函数，收到紧急信息时，操作系统产生SIGURG信号，并调用注册的信号处理函数



int sockClient;

int main(int argc, char* argv[])

{

    if(argc!=2){

        printf("Usage: %s <port> \n", argv[0]);

        exit(1);

    }



    struct sigaction act;

    memset(&act, 0, sizeof(act));


    act.sa_handler = urgHandler;

    sigemptyset(&act.sa_mask);

    act.sa_flags = 0;



    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;

    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;

    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    servAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sockServ, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        errorHandling("bind() error!");
    }
    if(listen(sockServ, 5) == -1){
        errorHandling("listen() error!");
    }

   struct sockaddr_in client_addr;
   socklen_t client_sock=sizeof(client_addr);
  
    sockClient = accept(sockServ, (struct sockaddr*)&client_addr, &client_sock);

    if(sockClient == -1){
        errorHandling("accept() error!");
    }
    else{
        fcntl(sockClient,F_SETOWN, getpid());//当前进程对SIGURG信号进行处理
        /*
         *
         * 文件描述符recv_sock指向的套接字引发的SIGURG信号处理进程
         * 变为将getpid函数返回值用作ID的进程
         *
         * */
        sigaction(SIGURG, &act, 0);//紧急信号进行注册，操作系统调用信号处理函数
        puts("New client connected...");
    }
    char buf[32];
    while(1){
        int readLen = recv(sockClient, buf, sizeof(buf),0);
        if(readLen == -1) {
            puts("readLen == -1");
            continue;
        }
        else if(readLen == 0){
            puts("Client disconnected...");
            close(sockClient);
            break;
        }
        else 
        {
            buf[readLen] = 0;
            puts(buf);

        }

    }



    close(sockServ);

    return 0;

}



void errorHandling(const char* message)

{

    fputs(message, stderr);

    fputc('\n', stderr);

    exit(1);

}



void urgHandler(int signo)

{

    char buf[32];

    if(signo == SIGURG){

        int readLen = recv(sockClient, buf, sizeof(buf)-1, MSG_OOB);
        if(readLen==-1)
        {
            puts("urgHandler() readLen == -1");
            return;
        }
        if(readLen == 0){
            puts("urgHandler() readLen == 0");
        }
        else{
            buf[readLen] = 0;
            printf("usagr message:%s",buf);
        }

       

    }

}
