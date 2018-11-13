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
	int thread_count = 2;
	int i = 0;
	int tmp = 0;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	for(int phase = 0;phase < size;phase++)
	{
		std::thread::id tid = std::this_thread::get_id();
		cout<<"main:"<<tid<<endl;
		if(phase %2 ==0)
		{
			#pragma omp parallel for num_threads(thread_count)\
			default(none) shared(vec,size) private(i,tmp)
			for(i = 1;i<size;i+=2)
			{
				if(vec[i-1] > vec[i]){
					tmp = vec[i-1];
					vec[i-1] = vec[i];
					vec[i] = tmp;
				}
			}
		}else{
			#pragma omp parallel for num_threads(thread_count)\
			default(none) shared(vec,size) private(i,tmp)
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