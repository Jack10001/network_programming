#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

//并发服务器端
//creat socket
//信号注册函数，父进程根据操作系统触发的信号处理函数消除僵尸进程

#define BUFSIZE 1024
//信号处理函数
void remove_child(int sig)
{
  pid_t id;
  int state;
  id=waitpid(-1,&state,WNOHANG);
  if(WIFEXITED(state))
  {
    printf("remove process id :%d\n",id);
    printf("child process finel value:%d\n",WEXITSTATUS(state));
  }
}

void error_handling(char* message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}

int main(int argc,char *argv[])
{
  socklen_t clnt_size;
  int server_sock,client_sock;
  struct sockaddr_in client_addr,server_addr;
  int read_size;
  pid_t pid;
  struct sigaction act;
  int state;
  char buf[BUFSIZE];
  if(argc!=2)
  {
    printf("参数错误");
    exit(1);
  }
  //初始化sigaction
  act.sa_handler=remove_child;
  sigemptyset(&act.sa_mask);
  act.sa_flags=0;

 state= sigaction(SIGCHLD,&act,0);
 if(state==-1)
 {
   error_handling("sigaction error!");
 }

 server_sock=socket(PF_INET,SOCK_STREAM,0);
 memset(&server_addr,0,sizeof(server_addr));
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 server_addr.sin_port=htons(atoi(argv[1]));

 if(bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
   error_handling("bind error");
 if(listen(server_sock,5)==-1)
   error_handling("listen error");
 //parent process
// clnt_size=sizeof(client_addr);
// client_sock=accept(client_sock,(struct sockaddr*)&client_addr,&clnt_size);
 while(1)
 {
  clnt_size=sizeof(client_addr);
  client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&clnt_size);
  if(client_sock==-1)
    continue;
  else
    printf("connecting..client socket:%d\n",client_sock);
  pid=fork();
  //子进程处理相关发送事宜
  if(pid==-1)
  {
    close(client_sock);
    continue;
  }
  if(pid==0)
  {
    close(server_sock);
    while((read_size=read(client_sock,buf,BUFSIZE))!=0)
      write(client_sock,buf,read_size);
    close(client_sock);
    puts("child disconnected\n");
    return 0;

  }
  else
    close(client_sock);

 }
 close(server_sock);
  return 0;
}
