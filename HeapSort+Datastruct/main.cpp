#include <iostream>

using namespace std;


//SORT TANG DAN WITH MAX_HEAP

/* HEAP:
 + Root is a[0]
 + Left child of a[i] is a[2*i + 1]
 + Right child of a[i] is a[2*i + 2]
 + |n/2|-> n: is index of leaf, so heaptify about it

 + Dac diem : -O(NlogN)
              - is a stable sort, requires a constant space for sorting a list
              - very fast and is widely used for sorting
/* function to Max-Heapify with i is current root of sub-tree
*/
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;        // index of left child of A[i]
    int r = 2*i + 2;        // index of right child of A[i]

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is large than root
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
/* function to build max-heap */
void buidMaxHeap(int arr[], int n)
{
    for (int i = n/2-1; i >= 0; i--)
        heapify(arr, n, i);
}

/* Heap Sort
    + Tao dong max-heap tu mang ban dau
    + Doi cho root (max) voi last element of array
    + Loai bo last node with giam sizeHeap--
    + Heapify with new root
    + Recursion until dong chi con 1 nut
*/
void heapSort(int arr[], int n)
{
    buidMaxHeap(arr, n);
    for (int i = n-1; i >= 0; i--)
    {
        // move current root to end
        swap(arr[0], arr[i]);

        // call max heaptify on the reduced heap
        heapify(arr, i, 0);
    }

}
/* function to print array of size n */
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}
int main()
{
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = sizeof(arr)/sizeof(arr[0]);

    heapSort(arr, n);

    cout << "Sort arr is \n";
    printArray(arr, n);
    return 0;
}
