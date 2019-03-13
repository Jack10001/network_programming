#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
/*int pthread_creat(
 * pthread_t * restrict thread, const pthread_arrt_t * register attr,
 * void*(*strat_routine)(void *),void *restrict arg);
 * thread : 保存新创建的线程ID的变量地址值，
 * attr : 用于传递线程属性的参数，传递NULL ，创建默认属性的线程
 * start_routine : 相当于线程的main函数，在单独的执行流中执行的函数地址值（函数指针）
 * arg : 通过第三个参数传递调用函数时包含传递参数信息的变量地址值
 *
int pthread_join(pthread_t thread,void ** status)
->成功时返回0，失败时返回其他值
thread  :  线程号ID 
status  :  线程main函数的返回值的指针变量地址值
 * */

//不掉用SLEEP函数，通过pthread_join函数检测线程执行是否结束

void * thread_main(void * arg);

int main(int argc,char* argv[])
{
  pthread_t t_id;
  int thread_parm=4;
  void * th_ret;//该值是在thread_main内部动态的分配内存空间的
//线程的作用是共用数据区和堆区，而每个线程拥有单独的栈区
  if(pthread_create(&t_id,NULL,thread_main,(void *)&thread_parm)!=0)
  {
    puts("pthread_creat error");
    return -1;
  }
  if(pthread_join(t_id,&th_ret)!=0)
  {
     puts("pthread_join error");
     return -1;
  }
  printf("t_id:%ld\n",t_id);
  puts("end of main");
  
  
printf("message from thread:%s",(char*)th_ret);
   free(th_ret); 
 return 0;
}

 
void * thread_main(void * arg)
{
  int cnt=*((int *)arg);
  int i;
   char *msg=(char *)malloc(sizeof(char)*50);
   strcpy(msg,"hello, the thread is over\n");
  for(i=0;i<cnt;i++)
  {
    sleep(1);
    puts("it's thread");
  }
  return (void *)msg;
}
