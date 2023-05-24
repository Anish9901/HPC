#include <iostream>
#include <omp.h>
using namespace std;
int main(){
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        cout << "hello world!!"<< ID << "\n";
    }
    return 0;
}