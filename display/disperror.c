#include "disperror.h"

void print_error(int errorcode)
{
        if(errorcode > 1000)
        {

        }
        else
        {
                if(errorcode == 1)
                {
                        print_sw(1,PUTERR,"you should as root to run it\n");
                }
        }
}
