#include<stdio.h>
#include<arpa/inet.h>
int main()
{
 unsigned short int h_addr=0x1234,n_;
 unsigned long int n_addr=0x12345678,h_;
 h_=ntohl(n_addr);
 n_=htons(h_addr);
 printf("%#x %#x ",h_addr,n_);
 printf("%#lx %#lx",n_addr,h_);
 printf("\n");
 char *addr1="192.168.1.2";
 char *addr2="192.256.256.2";
 unsigned long covr1=inet_addr(addr1);
 if(covr1==INADDR_NONE)
    printf("error ocuured!\n");
 else  
    printf("%#lx\n",covr1);
 unsigned long covr2=inet_addr(addr2);
 if(covr2==INADDR_NONE)
    printf("error ocuured!\n");
 else
    printf("%#lx",covr2); 
 return 0;
}
