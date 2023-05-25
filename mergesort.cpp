#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;
void merge(vector<int>& arr, int left, int right, int mid)
{
    int sub1 = mid - left + 1;
    int sub2 = right - mid;
    vector<int> a1(sub1);
    vector<int> a2(sub2);
    for(int i = 0; i < sub1; i++)
    {
        a1[i] = arr[left + i];
    }
    for(int i = 0; i < sub2; i++)
    {
        a2[i] = arr[mid + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i<sub1 && j<sub2)
    {
        if(a1[i] <= a2[j])
        {
            arr[k] = a1[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = a2[j];
            j++;
            k++;
        }
        
    }
    while(i<sub1)
    {
        arr[k] = a1[i];
        k++;
        i++;
    }
    while (j<sub2)
    {
        arr[k] = a2[j];
        j++;
        k++;
    }
}

void mergesort(vector<int>& arr, int left, int right)
{
    
    if(left < right)
    {
        int mid = left + (right - left)/2;
        #pragma omp parallel
        {
            #pragma omp task
            {
                mergesort(arr, left, mid);
            }
            #pragma omp task
            {
                mergesort(arr, mid+1, right);
            }
        }
        merge(arr, left, right, mid);
    }

}


int main(){
    /* Sort an array using mergesort*/
    vector<int> arr = {5,2,9,1,7,6,8,3,4};
    mergesort(arr, 0, arr.size() - 1);
    for(int i = 0; i < arr.size(); i++)
    {
        cout<< arr[i] << " ";
    }
    cout<<"\n";
    return 0;
}