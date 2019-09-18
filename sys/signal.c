/* signal.c - signal */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * signal  --  signal a semaphore, releasing one waiting process
 *------------------------------------------------------------------------
 */
SYSCALL signal(int sem)
{
	if(flag_11!=0){
	start_clock = ctr1000;}
	STATWORD ps;    
	register struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) 
	{
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[16] = (track_obj[currpid].time_taken[16] + (ctr1000 - start_clock));
			track_obj[currpid].freq[16]++;
		}

		return(SYSERR);
	}
	if ((sptr->semcnt++) < 0)
		ready(getfirst(sptr->sqhead), RESCHYES);
	restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[16] = (track_obj[currpid].time_taken[16] + (ctr1000 - start_clock));
		track_obj[currpid].freq[16]++;
	}

	return(OK);
}
