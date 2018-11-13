#include <iostream>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <thread>


using namespace std;

int main()
{
	int size = 20000;
	int * vec = new int[size];
	timespec start,end;


	for(int i = 0;i<size;i++)
	{
		vec[i] = size-i;
	}
	int thread_count = 8;
	int i = 0;
	int tmp = 0;
	int phase;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	#pragma omp parallel  num_threads(thread_count)\
			default(none) shared(vec,size) private(i,tmp,phase)
	for(phase = 0;phase < size;phase++)
	{
		if(phase %2 ==0)
		{
			#pragma omp for
			for(i = 1;i<size;i+=2)
			{
				if(vec[i-1] > vec[i]){
					tmp = vec[i-1];
					vec[i-1] = vec[i];
					vec[i] = tmp;
				}
			}
		}else{
			#pragma omp for
			for(i = 1;i<size-1;i+=2)
			{
				if(vec[i] > vec[i+1])
				{
					tmp = vec[i];
					vec[i] = vec[i+1];
					vec[i+1] = vec[i];
				}
			}
		}
	}



	return 0;
}