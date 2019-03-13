#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define maxsize 1024
int main(int argc,char * argv[])
{
    //客户端：创建套接子 ，调用connect函数连接，read/write, close
    int servSock;
    int str_len;
   // const int maxsize=1024;
    struct sockaddr_in servAddr;
    char message[maxsize];

    if(argc!=3)
        exit(1);

    servSock=socket(PF_INET,SOCK_STREAM,0);

    if(servSock==-1)
        printf("creat sockat error\n");

    memset(&servAddr,0,sizeof(servAddr));

    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(argv[1]);
    servAddr.sin_port=htons(atoi(argv[2]));

    if(connect(servSock,(struct sockaddr*)&servAddr,sizeof(servAddr))==-1)
    {
        printf("connect error\n");
        exit(0);
    }
    else
        printf("connecting.....\n");
    while(1)
    {
        fputs("input message(Q to quit)\n",stdout);
        fgets(message,maxsize,stdin);

        if(!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
            break;

        write(servSock,message,strlen(message));
        str_len=read(servSock,message,maxsize-1);
        message[str_len]=0;
        printf("message from server :%s",message);

    }
    close(servSock);
    return 0;
}







