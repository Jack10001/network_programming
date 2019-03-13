#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>

void error_handling(char *message);

int main(int argc,char*argv[])
{
  int recv_len,send_len;
  int state;
  socklen_t len;
  int sock;

  sock=socket(PF_INET,SOCK_STREAM,0);
  if(sock==-1)
    error_handling("creat socket error!\n");

  len=sizeof(send_len);
  state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&send_len,&len);
  if(state)
    error_handling("send_buf error!");
  
  len=sizeof(recv_len);
  state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void *)&recv_len,&len);
  if(state)
    error_handling("recv_buf error!");
  
  printf("send buf size:%d\n",send_len);
  printf("recv buf size:%d\n",recv_len);
  return 0;
}

void error_handling(char * message)  
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);

}
