/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{
	if(flag_11 !=0){
	start_clock = ctr1000;}
	STATWORD ps;    
	WORD	msg;

	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[7] = (track_obj[currpid].time_taken[7] + (ctr1000 - start_clock));
		track_obj[currpid].freq[7]++;
	}

	return(msg);
}
