#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
//使用两个管道实现两个进程之间的双向通信
#define maxsize 1024

void error_handling(char* message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
int main(int argc,char*argv[])
{
  int fds1[2];
  int fds2[2];
  pid_t pid;
  int flag=0;
  char buf[maxsize];
  char str1[maxsize];
  char str2[maxsize];
  pipe(fds1);
  pipe(fds2);
  pid=fork();
  if(pid<0)
    error_handling("fork error");
  else if(pid==0)
  {
    while(1)
    {
      printf("1 for read,0 for write:\n");
      scanf("%d",&flag);
      if(flag==0)
      {
      fgets(str1,maxsize,stdin);
      if(!strcmp("q\n",str1)||!strcmp("Q\n",str1))
      {
        write(fds1[1],"over!!!",10);
        break;
      }
      else
      {
        write(fds1[1],str1,sizeof(str1)+1);
      }
     }
      else
      {
        printf("message from parent process:\n");
        read(fds2[0],buf,maxsize);
        printf("%s\n",buf);
      }
    }
  }
  else
  {
   while(1)
   {
     printf("1 for read,0 for write:\n");
     scanf("%d",&flag);
     if(flag==0)
     {
       fgets(str2,maxsize,stdin);
       if(!strcmp("q\n",str2)||!strcmp("Q\n",str2))
       {
         write(fds2[1],"over2!",10);
         break;
       }
       else
       {
         write(fds2[1],str2,sizeof(str2)+1);
       }
     }
     else
     {
       printf("messaeg from child:\n");
       read(fds1[0],buf,maxsize);
       printf("%s",buf);

     }

  
   }
  }
  return 0;
}


