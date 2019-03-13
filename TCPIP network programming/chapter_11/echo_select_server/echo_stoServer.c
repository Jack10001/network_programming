#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/time.h>

#define BUF_SIZE 256

//并发服务器的实现模型：IO复用实现服务器端的高并发处理

void errorHandling(const char *message);
int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
    }
    int i;
    int fd_num,result;
   fd_set reads,cpy_read;
    int clntSock;
    char buf[BUF_SIZE];
    struct timeval timeout;
    struct sockaddr_in servAddr,clntAddr;

    int sockServ=socket(PF_INET,SOCK_STREAM,0);

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sockServ, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        errorHandling("bind() error!");
    }

    if(listen(sockServ, 5) != 0){
        errorHandling("listen() error!");
    }

    FD_ZERO(&reads);
    FD_SET(sockServ,&reads);//将套接字对应位置1,服务器端套接字的状态发生变化
   
    fd_num=sockServ;//最大的监视对象文件描述符的数量

    while(1)
    {
      cpy_read=reads;

     // timeout.tv_sec=5;
     // timeout.tv_usec=0;

      result=select(fd_num+1,&cpy_read,0,0,0);
  
      if(result==-1)
        break;
      else if(result==0)
      {
        errorHandling("select time-out!");
        continue;
      }
      else
      {
        //判断那些位发生了变化
        for(i=0;i<fd_num+1;i++)
        {
          printf("i:%d\n",i);
          if(FD_ISSET(i,&cpy_read))
          {
            printf("ready i:%d\n",i);
            if(i == sockServ)//connect accept
            {
              socklen_t clnt_size=sizeof(clntAddr);
              clntSock=accept(sockServ,(struct sockaddr*)&clntAddr,&clnt_size);
              FD_SET(clntSock,&reads);
              if(fd_num<clntSock)
                fd_num=clntSock;
              printf("connect client:%d\n",clntSock);
            }
            else//read messaeg
            {
               int strlen=read(i,buf,BUF_SIZE);
               if(strlen==0)
               {
                 FD_CLR(i,&reads);
                 close(i);
                 printf("close socket:%d\n",i);
               }
               else
               {
                 write(i,buf,sizeof(buf));
               }

            }

          }
        }
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


