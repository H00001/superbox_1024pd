

#include "synatt.h"
#define MV 1
int synatt(int argc,char ** argv)
{
	char * __ipaddr = argv[MV+1];
	int __port = atoi(argv[MV+2]);
        return  startsynattack( __ipaddr , __port);

}
