/*function:服务器端接受客户端的连接请求，并向所有连接的客户端转发某个客户端发来的信息，功能类似于QQ群的聊天功能
* author:
 * date:
 * 目的：多线程服务器端实现高并发处理请求
 * */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<pthread.h>

#define MAX_CLIENT 256
#define BUF_SIZE 1024

void error_handling(char *message);
void * deal_client(void *arg);//服务器端通过创建新的线程来处理新的客户端的连接请求
void send_msg(char * message,int strlen);

int client_socks[MAX_CLIENT];//全局变量，通过互斥锁进行访问
int cur_client=0;//当前连接的客户端的数量

pthread_mutex_t mutex;

int main(int argc,char *argv[])
{
  int client_sock,server_sock;
  struct sockaddr_in client_addr,server_addr;
  char buf[BUF_SIZE];
  pthread_t th_id;
  if(argc!=2)
    error_handling("parm error");
  if(pthread_mutex_init(&mutex,NULL)!=0)
    error_handling("thread mutex init error");

  server_sock=socket(PF_INET,SOCK_STREAM,0);
  if(server_sock==-1)
    error_handling("creat socket error");
  memset(&server_addr,0,sizeof(server_addr));
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  server_addr.sin_port=htons(atoi(argv[1]));

  if(bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
    error_handling("bind error");
  if(listen(server_sock,5)==-1)
    error_handling("listen error");

  while(1)
  {
    socklen_t client_sock_len=sizeof(client_addr);
    client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&client_sock_len);
    if(client_sock==-1)
      error_handling("accept error");

    pthread_mutex_lock(&mutex);
    client_socks[cur_client++]=client_sock;
    pthread_mutex_unlock(&mutex);

    pthread_create(&th_id,NULL,deal_client,(void *)&client_sock);
    pthread_detach(th_id);//销毁线程，非阻塞方式
    printf("connected client : %s \n",inet_ntoa(client_addr.sin_addr));

  }
  close(server_sock);
  pthread_mutex_destroy(&mutex);
  return 0;
}

void error_handling(char * message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(0);
}

void * deal_client(void *arg)
{
  char message[BUF_SIZE];
  int client_sock=*((int *)arg);
  int strlen_;
  while((strlen_=read(client_sock,message,BUF_SIZE))!=0)
  { // message[strlen]=0;
    printf("len:%d,message from client :%d--- %s\n",strlen_,client_sock,message);
    send_msg(message,strlen_);
  }
  //处理断开连接的客户端,从client_socks中移除,client_socks中的所有数据都要前移
  pthread_mutex_lock(&mutex);
  for(int i=0;i<cur_client;i++)
  {
    if(client_sock==client_socks[i])
    {
      while(i++<cur_client-1)
        client_socks[i]=client_socks[i+1];
      break;
    }
  }
  cur_client--;
  pthread_mutex_unlock(&mutex);
  close(client_sock);
  return NULL;

}

void send_msg(char *message,int strlen_)
{
   pthread_mutex_lock(&mutex);
   for(int i=0;i<cur_client;i++)
     write(client_socks[i],message,strlen_);
  pthread_mutex_unlock(&mutex);
}
