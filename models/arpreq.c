#include "arpreq.h"


int __isAlive()
{
        if(system("ping -c 1 192.168.1.1")<0)
        {
        printf("error");
        return -1;
        }
        else
        {
        printf("not");
         return 1;
        }
}
int main()
{
        __isAlive();
}
