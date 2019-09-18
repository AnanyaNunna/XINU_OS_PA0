/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	if(flag_11 != 0){
	start_clock = ctr1000;
	}
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) 
	{
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[3] = (track_obj[currpid].time_taken[3] + (ctr1000 - start_clock));
			track_obj[currpid].freq[3]++;
		}
		return(SYSERR);
	}
	restore(ps);
	if(flag_11 != 0)
        {
                track_obj[currpid].act = 1;
                track_obj[currpid].time_taken[3] = (track_obj[currpid].time_taken[3] + (ctr1000 - start_clock));
        	track_obj[currpid].freq[3]++;
        }

	return(pptr->pprio);
}
