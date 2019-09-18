/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
	if(flag_11 !=0){
	start_clock = ctr1000;}
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/

	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) 
	{
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[9] = (track_obj[currpid].time_taken[9] + (ctr1000 - start_clock));
			track_obj[currpid].freq[9]++;
		}

		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[9] = (track_obj[currpid].time_taken[9] + (ctr1000 - start_clock));
		track_obj[currpid].freq[9]++;
	}

	return(prio);
}
