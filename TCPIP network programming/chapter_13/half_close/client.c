#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFSIZE 30

int main(int argc,char*argv[])
{
  //创建socket,connect
  int client_sock;
  char BUF[BUFSIZE];
  struct sockaddr_in server_addr;
  FILE *fp;
  int read_size;
 if(argc!=3)
 {
   printf("参数错误!!");
     exit(0);
 }
 fp=fopen("recv.c","wb");

  client_sock=socket(PF_INET,SOCK_STREAM,0);
  if(client_sock==-1)
  {
    printf("creat socket failed");
    exit(0);
  }

  memset(&server_addr,0,sizeof(server_addr));
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=inet_addr(argv[1]);
  server_addr.sin_port=htons(atoi(argv[2]));
//connect
 if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
 {
   printf("连接错误\n");
   exit(0);
 }

  while((read_size=read(client_sock,BUF,BUFSIZE))!=0)
  //  fwrite(ARRAY, sizeof(TYPE), N_MEMBERS, FILE)
  //  size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
    fwrite((void *)BUF,1,read_size,fp);
  printf("messaeg has received\n");
  write(client_sock,"thank you",10);

 fclose(fp);
 close(client_sock);
  return 0;
}
