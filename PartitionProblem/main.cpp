#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 100
/* Bai 9 */

using namespace std;


void printSets(int arr[],int n, vector<int> set1, vector<bool> check)
{
    cout << "Set 1: ";
    for(int i = 0; i < set1.size(); i++)
        cout << set1[i] << " ";

    cout <<endl;
    cout << "Set 2: ";
    for (int i = 0; i < n; i++)
        if (check[i] == false)
            cout << arr[i] << " ";
}
bool findSets(int arr[], int n, vector<int> &set1, vector<bool> &check, int subSum, int target, int pos)
{
    // Neu da duyet het mang
        if (subSum == target)
        {
            printSets(arr,n, set1, check);
            return true;
        }
        if (pos > n)
            return false;

    // Them phan tu hien tai vao set1
    set1.push_back(arr[pos]);
    check[pos] = true;

    bool res = findSets(arr, n, set1, check, subSum+arr[pos], target, pos+1);

    // Neu res = true thi return
    if (res)
        return res;

    // Neu khong thi lay phan tu hien tai tu set1 add vao set2
    set1.pop_back();
    check[pos] = false;

    return findSets(arr, n, set1, check, subSum, target, pos+1);

}

bool isPartition(int arr[], int n)
{
    //Caculate sum of element
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += arr[i];

    if (sum %2 != 0)
        return false;

    vector <int> set1;
    vector <bool> check(n, false);      // dung de check phan tu nao da duoc them vao set1

    return findSets(arr, n, set1, check, 0, sum/2, 0);
}
int main()
{
    int n;
    int arr[MAX];
    cout << "Nhap so luong phan tu: ";
    cin >> n;

    cout << "Nhap cac phan tu cua mang: " <<endl;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    //qsort(arr, n, sizeof(arr[0]), cmp);
    if (!isPartition(arr, n))
        cout << "Khong chia duoc";

    return 0;
}
