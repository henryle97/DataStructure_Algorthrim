#include <iostream>

// a(n) = a(n-4) + a(n-3) - a(n-2) + a(n-1)

using namespace std;


int soTQ(int n)
{
    if (n <=4 )
        return n;
    else
        return soTQ(n-4) + soTQ(n-3) - soTQ(n-2) + soTQ(n-1);
}

int S(int n)
{
    if (n <= 4)
        return 10;
    else
        return S(n-1) + soTQ(n);
}
int main()
{
    int n;
    cout << "Nhap n (n >= 4) = ";
    cin >> n;
    cout << "So hang thu n la:  " << soTQ(n) <<endl;
    cout << "Tong "<< n << " so hang dau tien la: " << S(n)<<endl;
    return 0;
}
