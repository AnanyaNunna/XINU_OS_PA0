/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{
	if(flag_11 !=0){
	start_clock = ctr1000;}
	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) 
	{
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[11] = (track_obj[currpid].time_taken[11] + (ctr1000 - start_clock));
			track_obj[currpid].freq[11]++;
		}

		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[11] = (track_obj[currpid].time_taken[11] + (ctr1000 - start_clock));
		track_obj[currpid].freq[11]++;
	}

	return(OK);
}
