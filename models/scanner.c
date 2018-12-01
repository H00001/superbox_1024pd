#include"scanner.h"
#define MV 1
int scan(int argc,char ** argv)
{
	if(fork()!=0){
                __do_sm(argv[MV+1] ,atoi(argv[MV+2]),atoi(argv[MV+2])+ (atoi(argv[MV+3])-atoi(argv[MV+2]))/2);
		return 0;
        }
        else
        {
                __do_sm(argv[MV+1],atoi(argv[MV+2])+ (atoi(argv[MV+3])-atoi(argv[MV+2]))/2,atoi(argv[MV+3]));
		return 0;
        }
}




void __do_sm(char * ip,int sta,int end)
{
        int res;
        for(int i = sta;i<=end;i++)
        {
	
                printf("%s:",ip);
                res = __connection_net(ip,i);
                if(res ==0)
                {
                        printf("port:%d is open __OPEN__\n",i);
                }
                else
                {
                        printf("port:%d is not open __CLOS__\n",i);

                }
        }

}

