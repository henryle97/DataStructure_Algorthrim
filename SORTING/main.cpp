#include <iostream>

#define max 100
using namespace std;


void printArr(int arr[], int sizeArr)
{

    for (int i = 0; i < sizeArr; i++)
        cout << arr[i] << " ";
}

// SWAP

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
/* Insertion Sort
 + Solution: Tai phan tu thu i sau khi insert sort, du lieu tu arr[0] -> arr[i-1] da duoc sap xep
 + Phu hop voi day da gan duoc sap xep
 + O(n^2)
*/
void insertSort(int arr[], int sizeArr)
{
    int i, j, last;
    for (i = 1; i < sizeArr; i++)
    {
        last = arr[i];
        j = i;
        while (j > 0 && arr[j-1] > last)
        {
            arr[j] = arr[j-1];
            j = j-1;
        }
        arr[j] = last;
    }   //end for
    printArr(arr,sizeArr);
}

/* BUBBLE SORT
- Day phan tu lon nhat xuong cuoi day
- Kem hieu qua nhat
*/
void bubbleSort(int arr[], int sizeArr)
{
    int i,j;
    bool swapped;
    for (i = 0; i < sizeArr-1; i++){
        // Last i element are already in place
        swapped = false;
        for (j = 0; j < sizeArr-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        // Neu ko co su trao doi nao thi co nghia day da sap xep xong -> Break
        if (swapped == false)
            break;
    }
    printArr(arr, sizeArr);
}

/* MERGE SORT
- Dua tren chia de tri: Chia nho day thanh cac day con den khi con 1 phan tu-> merger de quy
- O(NlogN)
- Sap xep duoc tren bo nho ngoai: Bai toan sap xep file 10GB voi bo nho cho 1GB
*/

// Ham tron 2 day con da duoc sap xep -> 1 day con sap xep
void mergeA(int A[], int first, int mid, int last)
{
    int tempArr[max];
    int first1 = first; int last1 = mid;
    int first2 = mid+1; int last2 = last;

    int index = first1;

    // Merge 2 day con: So sanh cac phan tu dau day roi dua vao tempArr, neu 1 day het thi dua all day con lai
    // vao day tempArr
    for (; first1 <= last1 && first2 <= last2; index++)
    {
        if (A[first1] < A[first2])
        {
            tempArr[index] = A[first1];
            first1++;
        }
        else {
            tempArr[index] = A[first2];
            first2++;
        }
    }
    // Sao chep not
    for (; first1 <= last1;first1++, index++)
        tempArr[index] = A[first1];
    for (; first2 <= last2; first2++, index++)
        tempArr[index] = A[first2];

    // Sao tra mang ket qua
    for (index = first; index <= last; index++)
        A[index] = tempArr[index];
}
void mergeSort(int A[], int first, int last)
{
    if (first < last)
    {
        // chia thanh 2 day con
        int mid = (first+last) / 2;

        // sap xep day con trai A[first...mid]
        mergeSort(A, first, mid);
        mergeSort(A, mid+1, last);

        //Tron 2 day
        mergeA(A,first, mid, last);
    }
}
//Print
void mergeSortPrint(int A[], int sizeArr)
{
    printArr(A, sizeArr);
    mergeSort(A, 0, sizeArr-1);
    cout << "Merge Sort Ordered: ";
    printArr(A, sizeArr);

}



int main()
{
    int arr[max];
    int sizeArr;
    cout << "Nhap so phan tu: ";
    cin >> sizeArr;
    for (int i = 0; i < sizeArr; i++)
        arr[i] = rand()%1000;
    cout << "\t\t\tMENU"<<endl;
    cout << "1. Insertion Sort" <<endl;
    cout << "2. Bubble Sort" <<endl;
    cout << "3. Merge Sort" <<endl;
    cout << "4. Quick Sort" <<endl;

    int choose;
    cout << "Moi ban chon kieu sap xep: ";
    cin >> choose;
    switch (choose){
    case 1: insertSort(arr, sizeArr);
            break;
    case 2: bubbleSort(arr, sizeArr);
            break;
    case 3: mergeSortPrint(arr, sizeArr);
            break;
    }
    return 0;
}
