/* stacktrace.c - stacktrace */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

static unsigned long	*esp;
static unsigned long	*ebp;
unsigned long start_clock;
#define STKDETAIL

/*------------------------------------------------------------------------
 * stacktrace - print a stack backtrace for a process
 *------------------------------------------------------------------------
 */
SYSCALL stacktrace(int pid)
{
	if(flag_11 != 0){
	start_clock = ctr1000;}
	struct pentry	*proc = &proctab[pid];
	unsigned long	*sp, *fp;

	if (pid != 0 && isbadpid(pid))
	{
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[23] = (track_obj[currpid].time_taken[23] + (ctr1000 - start_clock));
			track_obj[currpid].freq[23]++;
		}

		return SYSERR;
	}
	if (pid == currpid) {
		asm("movl %esp,esp");
		asm("movl %ebp,ebp");
		sp = esp;
		fp = ebp;
	} else {
		sp = (unsigned long *)proc->pesp;
		fp = sp + 2; 		/* where ctxsw leaves it */
	}
	kprintf("sp %X fp %X proc->pbase %X\n", sp, fp, proc->pbase);
#ifdef STKDETAIL
	while (sp < (unsigned long *)proc->pbase) {
		for (; sp < fp; sp++)
			kprintf("DATA (%08X) %08X (%d)\n", sp, *sp, *sp);
		if (*sp == MAGIC)
			break;
		kprintf("\nFP   (%08X) %08X (%d)\n", sp, *sp, *sp);
		fp = (unsigned long *) *sp++;
		if (fp <= sp) 
		{
			kprintf("bad stack, fp (%08X) <= sp (%08X)\n", fp, sp);
			if(flag_11 != 0)
			{
				track_obj[currpid].act = 1;
				track_obj[currpid].time_taken[23] = (track_obj[currpid].time_taken[23] + (ctr1000 - start_clock));
				track_obj[currpid].freq[23]++;
			}
	
			return SYSERR;
		}
		kprintf("RET  0x%X\n", *sp);
		sp++;
	}
	kprintf("MAGIC (should be %X): %X\n", MAGIC, *sp);
	if (sp != (unsigned long *)proc->pbase) {
		kprintf("unexpected short stack\n");
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[23] = (track_obj[currpid].time_taken[23] + (ctr1000 - start_clock));
			track_obj[currpid].freq[23]++;
		}

		return SYSERR;
	}
#endif
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[23] = (track_obj[currpid].time_taken[23] + (ctr1000 - start_clock));
		track_obj[currpid].freq[23]++;
	}

	return OK;
}
