#include <iostream>
#include <omp.h>

using namespace std;
int main()
{
	double sum = 0.0;
	int k;
	double factor;
	int thread_count = 5;
	int n = 101;
	int n1 = 0;
	#pragma omp parallel for num_threads(thread_count)\
	default(none) reduction(+:sum) private(k,factor) shared(n,n1)
	for (k = 0;k<n;k++){
		if(k%2 == 0)
			factor = 1.0;
		else
			factor = -1.0;
		sum+=k;
		n1+=k;
	}
	cout<<sum<<" "<<n1<<endl;
	
	
	return 0;
}