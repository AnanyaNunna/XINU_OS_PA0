/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	if(flag_11 != 0){
	start_clock = ctr1000;}
	short	*nxtdev;

	if (isbadpid(pid))
	{
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[13] = (track_obj[currpid].time_taken[13] + (ctr1000 - start_clock));
			track_obj[currpid].freq[13]++;
		}
		return(SYSERR);
	}
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[13] = (track_obj[currpid].time_taken[13] + (ctr1000 - start_clock));
		track_obj[currpid].freq[13]++;
	}
	return(OK);
}
