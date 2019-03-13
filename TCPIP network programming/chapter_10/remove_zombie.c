#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>

//信号注册函数消除僵尸进程，将wait函数打包并设置为操作系统处理子进程的信号，子进程通过exit或者return将参数传递给父进程


//信号处理函数,交由操作系统进行管理
void child_pro(int sig)
{
  int status;
  pid_t id=waitpid(-1,&status,WNOHANG);
  if(WIFEXITED(status))
  {
    printf("removed proc id:%d\n",id);
    printf("child send :%d\n",WEXITSTATUS(status));
  }

}

int main(int argc,char*argv[])
{
  pid_t pid;
  int i;
  struct sigaction act;

  act.sa_handler=child_pro;
  sigemptyset(&act.sa_mask);
  act.sa_flags=0;

  sigaction(SIGCHLD,&act,0);//子进程终止，便触发信号处理函数，移除子进程

  pid=fork();

  if(pid==0)
  {
    puts("HI1 I'm child process \n");
    sleep(10);
    return 12;
  }
  else
  {
    printf("child proc id:%d\n",pid);
    pid=fork();
    if(pid==0)
    {
      puts("HI!i am second child process\n");
      sleep(10);
      exit(24);
    }
    else
    {
      printf("second child proc id:%d\n",pid);

      for(i=0;i<5;i++)
      {
        puts("wait....");
        sleep(5);
      }
    }
  }

  return 0;
}
