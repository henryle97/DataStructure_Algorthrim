#include <iostream>

using namespace std;

/* This function takes last element as pivot, places the pivot
    element at its correct position in sorted array,
    and places all smaller (smaller than pivot) to left of
    pivot and all greater elements to right of pivot
*/

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];          // pivot (chot)
    int i = low;              // index of smaller element
    for (int j = low; j <= high-1; j++)
    {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot)
        {
            swap(arr[i], arr[j]);       // swap(greater, smaller)
            i++;                     // increment to index of greater next
        }
    }
    swap(arr[i], arr[high]);        //swap (greatetFirst, pivot)
    return i;                   // return index of pivot after arrange
}

/* The main function that implement QS
    arr[] --> Array to be sorted,
    low --> Starting index,
    high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now at right place */
        int pi = partition(arr, low, high);

        // Separately sort element before
        // partition and after partition
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
int main()
{
    int arr[] = {4,5,9,12,13,17,27,21};
    int n = sizeof(arr)/sizeof(arr[0]);

    quickSort(arr, 0, n-1);
    cout << "Sorted Array: ";
    printArray(arr, n);
    return 0;
}
