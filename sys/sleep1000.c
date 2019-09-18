/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
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
			track_obj[currpid].time_taken[21] = (track_obj[currpid].time_taken[21] + (ctr1000 - start_clock));
			track_obj[currpid].freq[21]++;
		}

	}
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[21] = (track_obj[currpid].time_taken[21] + (ctr1000 - start_clock));
		track_obj[currpid].freq[21]++;
	}

	return(OK);
}
