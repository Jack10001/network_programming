#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>

int main(int argc,char*argv[])
{
  int opt_;
  int state;
  int sock;
  socklen_t opt_len;
  sock=socket(PF_INET,SOCK_STREAM,0);
  opt_len=sizeof(opt_);
  state=getsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void *)&opt_,&opt_len);
  printf("opt_ :%d",opt_);
  return 0;
}
