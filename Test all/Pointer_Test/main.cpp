#include <iostream>

using namespace std;

//Ham tinh giai thua: long double : 8 byte
long double recursion(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n * recursion(n - 1);
}

int main()
{
    int n;
    cin >> n;
    cout << "n! = " << recursion(n);
    return 0;
}
