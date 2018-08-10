#include <iostream>
#include <time.h>
#include <unistd.h>

#ifdef _OPENMP
#include <omp.h>
#endif



void Hello(void);

using namespace std;
int main()
{
	int thread_count = 4000;
#if
	#pragma omp parallel num_threads(thread_count)
	Hello();

	return 0;
}

void Hello()
{
#ifdef _OPENMP
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
# else
	int my_rank = 0;
	int thread_count = 1;

#endif
	int a = 0;
	for(int i=0;i<thread_count;i++)
	{
		a+=i;
	}
	printf("rank = %d thread_count = %d\n",my_rank,thread_count);
}