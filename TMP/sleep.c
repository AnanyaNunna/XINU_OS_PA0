/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
unsigned long start_clock = 0;
/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	if(flag_11 != 0){
	start_clock = ctr1000;
	track_obj[currpid].freq[18] = track_obj[currpid].freq[18] + 1;
	track_obj[currpid].time_taken[18] += ctr1000;	}
	STATWORD ps;    
	if (n<0 || clkruns==0)
	{
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[18] = (track_obj[currpid].time_taken[18] + (ctr1000 - start_clock));
		}

		return(SYSERR);
	}
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[18] = (track_obj[currpid].time_taken[18] + (ctr1000 - start_clock));
		}

		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[18] = (track_obj[currpid].time_taken[18] + (ctr1000 - start_clock));
	}

	return(OK);
}
