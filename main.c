#include"stdafx.h" 
#include"struct.h"
#define DEBUG 1
#define PROCESSVAL 2 
void do_sm(char * ip,int sta,int end);
void inint_fdt(struct mapping * __fdt);
int main(int argc,char ** argv)
{
	print_title();
	print_sw(DEBUG,PUTSTD,"yad elbieert a si 4201!!!\n");
	print_sw(DEBUG,PUTSTD,"yad elbieert a si 4201!!!\n");
	print_sw(DEBUG,PUTSTD,"yad elbieert a si 4201!!!\n");
	struct mapping __fdt[20];
	inint_fdt(__fdt);
	signal(SIGINT,Ctrl_C);
	if(argc==2&&(!strcmp(argv[1],"-h"))||argc==1)
	{
		print_help();
	}
	else if(argc==2&&(!strcmp(argv[1],"-v")))
	{
		print_version();
	}
	else
	{
		if(argc>=3){	
			int __pos = -1;
			for (int i = 0;i<20;i++)
			{
				if(__fdt[i].key!=NULL&&!strcmp(__fdt[i].key,argv[1]))
				{
					__pos = i;
				}
				else if(__fdt[i].key==NULL)
				{
					break;
				}

			}
			
			if(__pos!=-1)
			{
				__fdt[__pos].val(argc,argv);
			}
			
		}
	}

}
void inint_fdt(struct mapping * __fdt)
{
	__fdt[0].key="portsm";
	__fdt[0].val=scan;
	__fdt[1].key="syn";
	__fdt[1].val=synatt;
	for (int i = 2;i<20;i++)
	{
		__fdt[i].key = NULL;
	}

}
