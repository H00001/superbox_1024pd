
#include "disp_title.h"

void print_title()
{
	printf("********************************************\n");
	printf("*      welcome to the c tools  **          *\n");
	printf("*      develop by dosdrtt      **          *\n");
	printf("*      last version 3.2.14     **          *\n"); 
	printf("********************************************\n");

}
void print_version()
{
	int fd;
	int __save;
	char buffer[1024]={0};
	fd = open("./help/version_info",O_RDONLY);
	do{
		__save = read(fd, buffer, 1024);
		printf("%s",buffer);
	}
	while(__save==1024);
      	close(fd);

}
void print_help()
{
	printf("i am help\n");
}
