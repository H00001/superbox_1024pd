#define __ddos_copy_right__
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);
int __connection_net(char * ipaddr,int port);
