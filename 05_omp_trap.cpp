#include <iostream>
#include <omp.h>

using namespace std;

void Trap(double a,double b,int n,double *global_result_p)
{
    double h,x,my_result;
    double local_a,local_b;
    int i,local_n;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    h = (b-a)/n;
    local_n = n/thread_count;
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    my_result = 1;
    for(i = 1;i<=local_n - 1;i++)
    {
        x = local_a + i*h;
        my_result += 1;
    }

#pragma omp critical
    *global_result_p += my_result;

}
int main(int argc,char **argv)
{
    double global_result = 0.0;
    double a,b;
    int n;
    int thread_count = 8;

    a = 1.0;b = 8.0;
    n = 8000;
#pragma omp parallel num_threads(thread_count)
    Trap(a,b,n,&global_result);

    cout<<global_result<<endl;
    return 0;
}
