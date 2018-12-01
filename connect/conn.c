#include "conn.h"

int __connection_net(char * ipaddr,int port)
{
    int sock_fd;
    struct sockaddr_in serv_addr;
    char message[30] = {0};
    int rcv_len;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1){
    	return -1;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ipaddr);// server's IP addr
    serv_addr.sin_port = htons((port));//port

    if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
	return -2;
    }

    close(sock_fd);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
}

