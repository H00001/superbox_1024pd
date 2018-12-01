#include<stdio.h>
#include<errno.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<ctype.h>
#include<sys/types.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<string.h>
#include<unistd.h>
#include <time.h>

 
#define FAKE_IP "10.0.11.20"//伪装IP的起始值
 
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;


static ushort chksum(ushort *data,ushort length);

static inline long myrandom(int begin,int end);
void sendsynfunc(int FakeIpHost,int sockfd,struct sockaddr_in *addr);

