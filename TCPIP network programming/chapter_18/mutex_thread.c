/*
 * 创建100个线程，奇数线程对全局变量进行inc，偶线程对全局变量进行dec,使用互斥量
 * */
#include<pthread.h>
#include<stdio.h>
#include<string.h>

#define MAXSIZE 100

void * main_dec(void *arg);
void *main_inc(void *arg);

long long num=0;
pthread_mutex_t mutex;
int main(int argc,char*argv[])
{
  pthread_t t_id[MAXSIZE];

  int i;
  //创建互斥锁
  if(pthread_mutex_init(&mutex,NULL)!=0)
    printf("mutext creat error");
  //创建100个线程
  for(i=0;i<MAXSIZE;i++)
  {
    if(i%2)
      pthread_create(&t_id[i],NULL,main_dec,NULL);
    else
      pthread_create(&t_id[i],NULL,main_inc,NULL);
  }
 //对100个线程的结束时间进行把空
  for(i=0;i<MAXSIZE;i++)
    pthread_join(t_id[i],NULL);
  printf("num=%lld",num);

  pthread_mutex_destroy(&mutex);
  return 0;
}

void *main_dec(void *arg)
{
  int i=0;

  //对临界区进行加锁，防止其他线程访问临界区资源
  pthread_mutex_lock(&mutex);

  for(int i=0;i<50000;i++)
    num-=i;
  //允许其他线程访问临界区资源
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *main_inc(void *arg)
{
  int i;
  pthread_mutex_lock(&mutex);
  for(int i=0;i<50000;i++)
    num+=i;
  pthread_mutex_unlock(&mutex);
  return NULL;
}
