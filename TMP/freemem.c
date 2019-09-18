/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <stdio.h>
#include <proc.h>
unsigned long start_clock;
/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
SYSCALL	freemem(struct mblock *block, unsigned size)
{

	if(flag_11 != 0)
	{
		start_clock = ctr1000;
	}	

	STATWORD ps;    
	struct	mblock	*p, *q;
	unsigned top;

	if (size==0 || (unsigned)block>(unsigned)maxaddr
	    || ((unsigned)block)<((unsigned) &end))
	{
		//Store the time and frequency before it returns
		if(flag_11 != 0)
                {
                        track_obj[currpid].act = 1;
                        track_obj[currpid].time_taken[0] = (track_obj[currpid].time_taken[0] + (ctr1000 - start_clock));
                        track_obj[currpid].freq[0]++;
                }
		return(SYSERR);
	}
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);
		//Store the time and frequency before it returns
		if(flag_11 != 0)
        	{
                	track_obj[currpid].act = 1;
                	track_obj[currpid].time_taken[0] = (track_obj[currpid].time_taken[0] + (ctr1000 - start_clock));
                	track_obj[currpid].freq[0]++;
        	}	
		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);
	
	//Store the time and frequency before it returns
	if(flag_11 != 0)
	{
		track_obj[currpid].act = 1;
		track_obj[currpid].time_taken[0] = (track_obj[currpid].time_taken[0] + (ctr1000 - start_clock));
		track_obj[currpid].freq[0]++;
	}
	return(OK);
}
