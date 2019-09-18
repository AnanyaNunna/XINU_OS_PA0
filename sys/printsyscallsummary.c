#include<stdio.h>
#include<proc.h>

int flag_11;
char proc_name[27][20]={"freemem","chprio","getpid","getprio","gettime","kill","receive","recvclr","recvtim","resume","scount","sdelete","send","setdev","setnok","screate","signal","signaln","sleep","sleep10","sleep100","sleep1000","sreset","stacktrace","suspend","unsleep","wait"};


//create the object here and define it as extern in the proc.h so it can be used in all the files.
struct proc_track track_obj[NPROC];

void syscallsummary_start()
{
	//reset the array
	int i,pID;
	for(pID=0;pID<30;pID++)
	{
		for(i=0;i<27;i++)
		{
			track_obj[pID].time_taken[i] = 0;
			track_obj[pID].freq[i] = 0;
			track_obj[pID].act = 0;
		}
	}
	flag_11 = 1;
}

void syscallsummary_stop()
{
	flag_11 = 0;
}

void printsyscallsummary()
{
	printf("\nvoid printsyscallsummary()\n");
	int pID,j;
	for(pID=0;pID<NPROC;pID++)
	{
		if(track_obj[pID].act==1)
		{
			printf("Process[pid:%d]\n",pID); 
			for(j=0;j<27;j++)
			{
				if(track_obj[pID].freq[j]!=0){
				printf("\tSyscall: %s, count: %d, average execution time:%lu\n",proc_name[j],\
					track_obj[pID].freq[j],(track_obj[pID].time_taken[j]/track_obj[pID].freq[j]));}
			}
		}
	}
}
