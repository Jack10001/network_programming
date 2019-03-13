#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>

#define MAXSIZE 256
//使用io复用，select函数 
//
int main(int argc,char*argv[])
{
  fd_set set;
  fd_set temps;
  int result;
  int strlen;
  struct timeval timeout;
  char buf[MAXSIZE];

  FD_ZERO(&set);
  FD_SET(0,&set);//fd0:standard input,fd1:standard output, fd2:standard stderr

  while(1)
  {
    temps=set;//调用SELECT函数后，除发生变化的文件描述符对应外，剩下的所有位将初始化为0
    timeout.tv_sec=5;
    timeout.tv_usec=0;
    result=select(1,&temps,0,0,&timeout);
    if(result==-1)
    {
      printf("select error!");
    }
    else if(result==0)
    {
      puts("time-out");
    }
    else
    {
      if(FD_ISSET(0,&temps))
      {
      strlen=read(0,buf,MAXSIZE);//从标准输入设备输入字符并通过seletc函数选择IO端口进行复用
      buf[strlen]=0;
      printf("message from concole:%s\n",buf);
    }
    }
  }


  return 0;
}
