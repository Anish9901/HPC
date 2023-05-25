#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

void bubble_sort(vector<int>& arr)
{
    bool isSorted = false;
    while(!isSorted)
    {
        isSorted = true;
        #pragma omp parallel for
        for(int i=0; i < arr.size() - 1; i += 2)
        {
            if(arr[i] > arr[i+1])
            {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        #pragma omp parallel for
        for(int i = 1; i < arr.size() - 1; i += 2)
        {
            if(arr[i] > arr[i+1])
            {
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }
    }
}

int main(){
    /* Sort an array using bubblesort*/
    /* vector<int> arr = {5,2,9,1,7,6,8,3,4}; */
    vector<int> arr = {7, 6,5,4,3,2,1};
    vector<int> res;
    double start, end;
    start = omp_get_wtime();
    bubble_sort(arr);
    end = omp_get_wtime();
    for(int i = 0; i < arr.size(); i++)
    {
        cout<< arr[i] << " ";
    }
    cout<<"\nTime:"<< end - start << "\n";
    return 0;
}