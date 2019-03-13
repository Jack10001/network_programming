#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
/*int pthread_creat(
 * pthread_t * restrict thread, const pthread_arrt_t * register attr,
 * void*(*strat_routine)(void *),void *restrict arg);
 * thread : 保存新创建的线程ID的变量地址值，
 * attr : 用于传递线程属性的参数，传递NULL ，创建默认属性的线程
 * start_routine : 相当于线程的main函数，在单独的执行流中执行的函数地址值（函数指针）
 * arg : 通过第三个参数传递调用函数时包含传递参数信息的变量地址值
 *
 * */



void * thread_main(void * arg);

int main(int argc,char* argv[])
{
  pthread_t t_id;
  int thread_parm=4;

  if(pthread_create(&t_id,NULL,thread_main,(void *)&thread_parm)!=0)
  {
    puts("pthread_creat error");
    return -1;
  }
  sleep(2);
  puts("end of main");
  return 0;
}

void * thread_main(void * arg)
{
  int cnt=*((int *)arg);
  int i;
  for(i=0;i<cnt;i++)
  {
    sleep(1);
    puts("it's thread");
  }
  return NULL;
}
