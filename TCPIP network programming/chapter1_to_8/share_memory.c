#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/wait.h>

#define MAX_SEQ 10

struct shared
{
  long fib_seq[MAX_SEQ];
  int seq_size;
};
typedef struct shared shared_data;

int main(int argc,char **argv)
{
   int size=0;
   int i=-1;
   while(argv[2][++i]!='\0')
	   size=size*10+(int)argv[2][i]-(int)'0';
   if(size<0 || size>MAX_SEQ)
   {
	printf("wrong arguement");
	return -1;
   }
   int segment_id;
   shared_data *shared_memory;
   segment_id=shmget(IPC_PRIVATE,sizeof(shared_data),S_IRUSR|S_IWUSR);
   shared_memory=(shared_data*)shmat(segment_id,NULL,0);

   shared_memory->seq_size=size;

   pid_t pid;
   pid=fork();

   if(pid<0)
   {
	printf("failed to creat child process");
	return -1;
   }
   else if(pid==0)
   {
	long preNum=0;
	long behNum=1;
	long temp;
	for(int i=0;i<shared_memory->seq_size;++i)
	{
		shared_memory->fib_seq[i]=behNum;
		temp=preNum+behNum;
		preNum=behNum;
		behNum=temp;
	}
	shmdt(shared_memory);
   }
   else if(pid>0)
   {
	   wait(NULL);
	   printf("fibonacci: ");
	   for(int i=0;i<shared_memory->seq_size;++i)
		   printf("%ld",shared_memory->fib_seq[i]);
	   printf("\n");

	   shmdt(shared_memory);
	   shmctl(segment_id,IPC_RMID,NULL);

   }
   return 0;
}
