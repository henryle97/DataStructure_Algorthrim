#include <iostream>

using namespace std;

void PrintRecursion(char A[], int n,int k)
{
    if (k == 0)
        return;
    else {
        if (n == 0)
            PrintRecursion(A, sizeof(A)/sizeof(char), k-1);
        else
        {
            cout << A[n-1];
            PrintRecursion(A, n-1, k);
        }
    }
}
int main()
{
    char A[]="1234";
    PrintRecursion(A, 4, 10);
    return 0;
}
