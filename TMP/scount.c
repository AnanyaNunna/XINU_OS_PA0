/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <proc.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
	if(flag_11 != 0){
	start_clock = ctr1000;}
	extern	struct	sentry	semaph[];

	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
	{
		if(flag_11 != 0)
		{
			track_obj[currpid].act = 1;
			track_obj[currpid].time_taken[10] = (track_obj[currpid].time_taken[10] + (ctr1000 - start_clock));
			track_obj[currpid].freq[10]++;
		}
		return(SYSERR);
	}
	
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[10] = (track_obj[currpid].time_taken[10] + (ctr1000 - start_clock));
		track_obj[currpid].freq[10]++;
	}
	return(semaph[sem].semcnt);
}
