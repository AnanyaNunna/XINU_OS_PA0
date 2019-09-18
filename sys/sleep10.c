/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep10(int n)
{
	if(flag_11 != 0){
	start_clock = ctr1000;}
	STATWORD ps;    
	if (n < 0  || clkruns==0)
	{
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[19] = (track_obj[currpid].time_taken[19] + (ctr1000 - start_clock));
			track_obj[currpid].freq[19]++;
		}

		return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[19] = (track_obj[currpid].time_taken[19] + (ctr1000 - start_clock));
		track_obj[currpid].freq[19]++;
	}

	return(OK);
}
