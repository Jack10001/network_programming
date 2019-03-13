#include<stdio.h>
#include<unistd.h>

#define maxsize 1024
int main(int argc,char*argv[])
{
  int fds[2];
  pid_t pid;
  char str[maxsize];
  char buf[maxsize]="how are you";
  pipe(fds);

  pid=fork();
  if(pid==0)
  {
    read(fds[1],str,maxsize);
    puts("read:");
    puts(buf);
  }
  else
  {
    puts("write:");
    puts(buf);
    write(fds[0],buf,sizeof(buf));
  }
}
