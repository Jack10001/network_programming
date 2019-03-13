#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void *sum_main(void *arg);

int sum=0;
int main(int argc,char*argv[])
{
  void **sum1;
  void **sum2;//在线程中为其申请空间，在main函数中进行free
  pthread_t t_id1,t_id2;
  int range1[]={1,5};
  int range2[]={6,10};
  if(pthread_create(&t_id1,NULL,sum_main,(void*)range1)!=0)
  {
    printf("pthread_create error");
    return -1;
  }
  if(pthread_create(&t_id2,NULL,sum_main,(void *)range2)!=0)
  {
    printf("pthread_create2 error");
    return -1;
  }
   
  if(pthread_join(t_id1,NULL)!=0)
  {
    printf("pthread_join1 error");
    return -1;
  }

  if(pthread_join(t_id2,NULL)!=0)
  {
    printf("pthread_join2 error");
    return -1;
  }
  
 // printf("sum1=%d\n",(int*)&sum1);
 // printf("sum2=%d\n",(int*)&sum2);
  printf("sum=%d",sum);
 // free(sum1);
 // free(sum2);
  return 0;
}

void *sum_main(void *arg)
{
  int start=((int *)arg)[0];
  int end=((int *)arg)[1];
 // int **status;
  while(start<=end)
  {
    sum=sum+start;
    start++;
  }
 // &status=sum;
  //return (void*)&status;
  return NULL;
}
