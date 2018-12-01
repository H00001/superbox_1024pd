
#include "disp_title.h"

void print_title()
{
	printf("************************************************************\n");
	printf("*                welcome to use the c tools                *\n");
	printf("*        the software was developed by dosdrtt             *\n");
	printf("*                 the last version 3.2.15                  *\n"); 
        printf("* github address:https://github.com/H00001/superbox_1024pd *\n"); 
        printf("*        my email address is lnpj.office@gmail.com         *\n"); 
	printf("************************************************************\n");

}
void print_sw(int isput,puttype __sw,char * __message)
{
    if(isput){
    if(__sw==NOPUT)
    {
        
    }
    else if(__sw==PUTERR)
    {
        fputs(__message, stderr);
    }
    else if(__sw==PUTSTD)
    {
        fputs(__message, stdout);
    }

    }
}
void print_version()
{
	int fd;
	int __save;
	char buffer[1024]={0};
	fd = open("./help/version_info",O_RDONLY);
	do{
		__save = read(fd, buffer, 1024);
	        print_sw(1,PUTSTD,buffer);	
	}
	while(__save==1024);
      	close(fd);

}
void print_help()
{
	printf("i am help\n");
}
