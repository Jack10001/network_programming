#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define maxsize 1024

int main(int argc,char*argv[])
{
  pid_t pid;
  int fds1[2];
  int fds2[2];
  char buf[maxsize];
  char str1[]="How are you";
  char str2[]="hello";
  pipe(fds1);
  pipe(fds2);
  pid=fork();
  if(pid<0)
  {
    printf("fork error");
    exit(1);
  }
  if(pid==0)
  {
    read(fds1[0],buf,maxsize);
    printf("messaeg from parent:%s",buf);
    write(fds2[1],str2,sizeof(str2)+1);

  }
  else if(pid>0)
  {
    write(fds1[1],str1,sizeof(str1)+1);
    read(fds2[0],buf,maxsize);
    printf("message from child:%s",buf);

  }
  return 0;
}
