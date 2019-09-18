/* sleep100.c - sleep100 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * sleep100  --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep100(int n)
{
	if(flag_11 != 0){
	start_clock = ctr1000;}
	STATWORD ps;    

	if (n < 0  || clkruns==0)
	{
	        return(SYSERR);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[20] = (track_obj[currpid].time_taken[20] + (ctr1000 - start_clock));
			track_obj[currpid].freq[20]++;
		}

	}
	disable(ps);
	if (n == 0) {		/* sleep100(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*10);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if(flag_11 != 0)
	{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[20] = (track_obj[currpid].time_taken[20] + (ctr1000 - start_clock));
			track_obj[currpid].freq[20]++;
	}

	return(OK);
}
