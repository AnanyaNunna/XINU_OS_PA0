/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	if(flag_11 != 0){
	start_clock = ctr1000;
	}
	if(flag_11 != 0)
	{
    		track_obj[currpid].act = 1;
    		track_obj[currpid].time_taken[2] = (track_obj[currpid].time_taken[2] + (ctr1000 - start_clock));
    		track_obj[currpid].freq[2]++;
	}

	return(currpid);
}
