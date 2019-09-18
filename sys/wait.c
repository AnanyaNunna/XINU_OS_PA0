/* wait.c - wait */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{
	if(flag_11 != 0){
	start_clock = ctr1000;}
	STATWORD ps;    
	struct	sentry	*sptr;
	struct	pentry	*pptr;

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) 
	{
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[26] = (track_obj[currpid].time_taken[26] + (ctr1000 - start_clock));
			track_obj[currpid].freq[26]++;
		}
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[26] = (track_obj[currpid].time_taken[26] + (ctr1000 - start_clock));
			track_obj[currpid].freq[26]++;
		}

		return pptr->pwaitret;
	}
	restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[26] = (track_obj[currpid].time_taken[26] + (ctr1000 - start_clock));
		track_obj[currpid].freq[26]++;
	}

	return(OK);
}
