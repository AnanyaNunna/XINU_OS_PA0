/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <proc.h>
unsigned long start_clock;
extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
	if(flag_11 !=0){
	start_clock = ctr1000;}
    /* long	now; */

	/* FIXME -- no getutim */
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[4] = (track_obj[currpid].time_taken[4] + (ctr1000 - start_clock));
		track_obj[currpid].freq[4]++;
	}
    return OK;
}
