#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#define maxsize 1024

int main(int argc,char *argv[])
{
    //socket，bind , listen, accept, read/write,close
    struct sockaddr_in servAddr;
    struct sockaddr_in cliAddr;
   
   int servSock;
    int cliSock;

    char message[maxsize];
    int str_len,i;

    if(argc!=2)
        exit(1);

    servSock=socket(PF_INET,SOCK_STREAM,0);

    if(servSock==-1)
        printf("creat  socket error");

    memset(&servAddr,0,sizeof(servAddr));

    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(atoi(argv[1]));

    if(bind(servSock,(struct sockaddr*)&servAddr,sizeof(servAddr))==-1)
         printf("bind error");

    if(listen(servSock,5)==-1)
        printf("listen error");

    socklen_t  clt_addr_size=sizeof(cliAddr);
    cliSock=accept(servSock,(struct sockaddr*)&cliAddr,&clt_addr_size);
    if(cliSock==-1)
       printf("accept error");
    //利用标准IO函数完成SOCKET通信，标准IO函数带有缓冲功能，能够提高性能
    FILE* client_fp_read=fdopen(cliSock,"r");
    FILE* client_fp_write=fdopen(cliSock,"w");
    while(!feof(client_fp_read))
    {
      fgets(message,maxsize,client_fp_read);

      fputs(message,client_fp_write);
       fflush(client_fp_write);
    }

  fclose(client_fp_read);
  fclose(client_fp_write);
  return 0;

}

