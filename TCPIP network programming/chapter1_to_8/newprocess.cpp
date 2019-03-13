#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc, char *argv[])
{/* C program forking a separate process */
int pid;
/* fork another process */
pid=fork();
if (pid<0) { /* error occurred */
    fprintf(stderr, "Fork failed");
    exit(1)
    }
else if (pid==0) { /* child process */
            exec("/bin/ls", "ls", NULL);
            }
       else { /* parent process */
             /* parent process will wait for the child to complete */
           wait(NULL);
           printf("Child Complete");
           exit(0);
          }
}
