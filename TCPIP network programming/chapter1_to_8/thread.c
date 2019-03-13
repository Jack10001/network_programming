#include<pthread.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int value=0;
void *runner(void *param);
int main(int argc,char ** argv)
{
    int pid;
    pthread_t tid;
    pthread_attr_t attr;

    pid=fork();

    if(pid==0)
    {
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,runner,NULL);
        pthread_join(tid,NULL);
        printf("child:value=%d",value);

    }
    else if(pid>0)
    {
        wait(NULL);
        printf("parent:value=%d",value);
    }

}

void *runner(void *param)
{
    value=5;
    pthread_exit(0);
    }
