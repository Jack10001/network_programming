#include<unistd.h>
#include<stdio.h>
int main()
{
  int i=0;
  printf("i son/pa ppid pid fpid\n");
  for(i=0;i<3;i++)
  {
    fork();
    printf("hello wprld\n");
  }
  printf(" +\n");
 // return 0;
}

