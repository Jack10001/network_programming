#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>
#include<semaphore>
void fibonacci(int count);
int main(int argc, char *argv[])
{/* C program forking a separate process */
	int pid;
	int num;
	/* fork another process */
        //printf("enter num:\n");
	//scanf("%d",&num);
	pid=fork();
	if (pid<0) { /* error occurred */
           fprintf(stderr, "Fork failed");
           exit(1);
	   }
	else if (pid==0) { /* child process */
	  printf("child process:\n");
	  printf("enter num:\n");
	  scanf("%d",&num);
	  fibonacci(num);
         // execl("/bin/ls", "ls", NULL);
	  }
	else { /* parent process */
	/* parent process will wait for the child to complete */
	//fibonacci(num);
         wait(NULL);
	 printf("Child Complete,it's parent process\n");

	// fibonacci(num);
         exit(0);
 
}
  printf("\n\n");
}

void fibonacci(int count)
{
   int f0=0;
   int f1=1;
   int f=0;
   int i=1;
   if(count<0)
   {
	printf("count <0!\n");
	exit(0);
   }
   while(i<=count)
  {
      f=f0+f1;
      f0=f1;
      f1=f;
      printf("%d ",f);
      i=i+1;
    
   }
printf("\n\n");
}
