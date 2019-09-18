#include<stdio.h>
#include<proc.h>
#define p proctab

unsigned long *esp;
void printprocstks(int priority)
{
	int i;
	for(i=0;i<NPROC;i++)
	{
		if(p[i].pstate!=PRFREE)
		{
			if(p[i].pprio>priority)
			{
				printf("Process [proc %s]\n",p[i].pname);
				printf("\tpid: %d\n",i);
				printf("\tpriority : %d\n",p[i].pprio);
				printf("\tbase: 0x%08x\n",p[i].pbase);
				printf("\tlimit: 0x%08x\n",p[i].plimit);
				printf("\tlen: %d\n",p[i].pstklen);
				if(p[i].pstate != PRCURR)
				{	
					printf("\tpointer: 0x%08x\n",p[i].pesp);
				}
				else
				{
				//for current process, the stack pointer will be the at esp(top of the stack pointer)
					asm("mov %esp, esp");
					printf("\tpointer: 0x%08x\n",esp);	
				}
		
			}
		}
	}
} 			

