#include<stdio.h>

unsigned long *ebp,*esp;
void printtos()
{	
	asm("mov %ebp, ebp");
	
	printf("\nvoid printtos()\n");
	printf("Before[0x%08x]: 0x%08x\n", ebp + 2, *(ebp + 2));
	printf("After[0x%08x]: 0x%08x\n", ebp, *ebp);
	
	asm("mov %esp, esp");
	int i;
	//The most recent values are present above the esp(stack pointer)
	//the stack starts from the high address, so to reach the recently
	//pushed elements we need to move higher up in the address.
	for(i=1; i<=4; i++)
	{
		printf("\telement[0x%08x] values is 0x%08x\n",(esp+i),*(esp+i));
	}
}
