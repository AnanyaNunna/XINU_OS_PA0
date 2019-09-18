/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include "printsegaddress.c"
#include "printtos.c"
#include "printprocstks.c"
#include "printsyscallsummary.c"

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */

extern void printtos1();

extern void printtos();
extern void printsegaddress();
extern void printprocstks(int);
extern long zfunction(long pam);
extern void syscallsummary_start();
extern void syscallsummary_stop ();
extern void printsyscallsummary();

int prX;
void halt();

prch(c)
char c;
{
	int i;
	sleep(5);	
}

int main()
{	
	printf("\n\nHello World, Xinu lives\n\n");
        
	unsigned long passed_value = 0xaabbccdd;
	
	printf("---------1.) zfunction()-------\n\n");
        printf("The output of the assemly file is: %x\n",zfunction(passed_value));
	
	printsegaddress();
	
	printtos();

	printprocstks(0);
	

	resume(prX = create(prch,2000,20,"proc X",1,'A'));
	syscallsummary_start();
	sleep(10);
	syscallsummary_stop();
	printsyscallsummary();
	return 0;
}
