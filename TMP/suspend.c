/* suspend.c - suspend */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 *  suspend  --  suspend a process, placing it in hibernation
 *------------------------------------------------------------------------
 */
SYSCALL	suspend(int pid)
{
	if(flag_11 != 0){
	start_clock = ctr1000;}
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority returned		*/

	disable(ps);
	if (isbadpid(pid) || pid==NULLPROC ||
	 ((pptr= &proctab[pid])->pstate!=PRCURR && pptr->pstate!=PRREADY)) 
	{
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[24] = (track_obj[currpid].time_taken[24] + (ctr1000 - start_clock));
			track_obj[currpid].freq[24]++;
		}

		return(SYSERR);
	}
	if (pptr->pstate == PRREADY) {
		pptr->pstate = PRSUSP;
		dequeue(pid);
	}
	else {
		pptr->pstate = PRSUSP;
		resched();
	}
	prio = pptr->pprio;
	restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[24] = (track_obj[currpid].time_taken[24] + (ctr1000 - start_clock));
		track_obj[currpid].freq[24]++;
	}

	return(prio);
}
