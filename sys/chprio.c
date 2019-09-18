/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{
	if(flag_11 != 0)
	{
		start_clock = ctr1000;
	}
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) 
	{
		restore(ps);
		if(flag_11 != 0)
                {
                        track_obj[currpid].act = 1;
                        track_obj[currpid].time_taken[1] = (track_obj[currpid].time_taken[1] + (ctr1000 - start_clock));
                        track_obj[currpid].freq[1]++;
                }
		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);
	if(flag_11 != 0)
        {
		track_obj[currpid].act = 1;
                track_obj[currpid].time_taken[1] = (track_obj[currpid].time_taken[1] + (ctr1000 - start_clock));
                track_obj[currpid].freq[1]++;
	}
	return(newprio);
}
