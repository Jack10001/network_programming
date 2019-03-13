#include<signal.h>
#include<stdio.h>
#include<unistd.h>

//信号处理函数
void timeout(int sig)
{
  if(sig==SIGALRM)
    puts("time out!\n");
  alarm(2);
}

void keypress(int sig)
{
  if(sig==SIGINT)
    puts("ctrl+c!\n");
}

int main(int argc,char*argv[])
{
  int i;
  //注册信号处理函数:wq
  signal(SIGALRM,timeout);
  signal(SIGINT,keypress);

  alarm(2);

  for(int i=0;i<100;i++)
  {
    puts("wait...\n");
    sleep(100);
  }
 return 0;
}
