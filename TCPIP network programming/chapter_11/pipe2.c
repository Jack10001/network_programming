#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define maxsize 1024
int main(int argc,char* argv[])
{
  pid_t pid;
  int state;
  char str1[]="hello";
  char str2[]="hello too";
  char buf[maxsize];
  int fds[2];
  state=pipe(fds);
  if(state==-1)
    puts("error!");
  pid=fork();
  if(pid<0)
  {
    puts("fork error");
    exit(0);
  }
  else if(pid==0)
  {
    write(fds[1],str1,sizeof(str1)+1);
    sleep(2);
    read(fds[0],buf,maxsize);
    printf("from parent process:%s\n",buf);

  }
  else
  {
    read(fds[0],buf,maxsize);
    printf("from child process :%s",buf);
    write(fds[1],str2,sizeof(str2)+1);
   sleep(5);

  }
  return 0;
}
