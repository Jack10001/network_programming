#include<stdio.h>
#include<unistd.h>

int main(int argc,char*argv[])
{
  pid_t pid=fork();

  if(pid==0)
  {
    printf("It's child process:\n");
  }
  else
  {
    printf("chile pid:%d\n",pid);
    sleep(30);
  }

  if(pid==0)
    printf("end chile process!");
  else
    printf("end parent process1");
  return 0;
}
