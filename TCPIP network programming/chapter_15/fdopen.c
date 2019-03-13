#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc,char*argv[])
{
  int fd;
  FILE *fp;
 fd=open("news.dat",O_WRONLY|O_CREAT|O_TRUNC);
 if(fd==-1)
   printf("file can not be opened");
 fp= fdopen(fd,"w");
 if(fp==NULL)
   printf("can't be changed");
 fputs("C programming is very intersfd\n",fp);
 fclose(fp);
 return 0;
}
