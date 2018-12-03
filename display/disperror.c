#include "disperror.h"

void print_error(int __isoutput__, int errorcode)
{
        if(errorcode > 1000)
        {

        }
        else
        {
                print_sw(__isoutput__,PUTERR,strerror(errorcode));

        }
}
