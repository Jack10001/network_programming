#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define BUFSIZE 32

int main(int argc,char *argv[])
{
 //创建socket, bind,listen,accept,read/write
 int client_sock,server_sock;
 int read_size;
 struct sockaddr_in client_addr,server_addr;
 FILE *fp;
 char BUF[BUFSIZE];
 socklen_t cln_size;
 if(argc!=2)
 {
   printf("usage:%s<port>\n",argv[0]);
   exit(0);
 }
 fp=fopen("hello.c","rb");
 server_sock=socket(PF_INET,SOCK_STREAM,0);
if(server_sock==-1)
{
  printf("creat socket failed !");
  exit(0);
}

 memset(&server_addr,0,sizeof(server_addr));
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 server_addr.sin_port=htons(atoi(argv[1]));

 //bind
 if(bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
  printf("bind error");
  exit(0);
}

listen(server_sock,5);
cln_size=sizeof(client_addr);

client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&cln_size);
while(1)
{
  //size_t fread(void *buf, size_t size, size_t count, FILE *fp);
  read_size=fread((void*)BUF,1,BUFSIZE,fp);
  if(read_size<BUFSIZE)
  {
    write(client_sock,BUF,read_size);
    break;//读完了文件的最后内容
  }
  else
  {
    write(client_sock,BUF,BUFSIZE);
  }
}

 shutdown(client_sock,SHUT_WR);
// shutdown(server_sock,SHUT_RD);
 read(client_sock,BUF,BUFSIZE);
 printf("message from client:%s\n",BUF);
close(server_sock);
fclose(fp);
close(client_sock);
 return 0;
}
