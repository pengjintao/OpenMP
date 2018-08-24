#include <iostream>
#include <omp.h>

using namespace std;
int main()
{
    int x = 5;
    int thread_count = 2;
#pragma omp parallel num_threads(thread_count)\
    private(x)
    {
        int rank = omp_get_thread_num();
        cout<<"Thread "<<x<<" before initialization "<<endl;
        x = 2*rank;
        cout<<"Thread after initialization "<<x<<endl;
    }
    cout<<"After parallel block,x = "<<x<<endl;
}
