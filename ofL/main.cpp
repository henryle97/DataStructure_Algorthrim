#include <iostream>

using namespace std;


void print_bits(unsigned char *ch)
{
    for (int i = 0; i < 10; i++)
    {
        cout << ch[i];
        int a[8] = {};
        int n = 8;
        int k = 0;
        while ( n != 0)
        {
            a[k] = n % 2;
            k++;
            n = n / 2;
        }
        for (k = k-1; k >= 0; k--)
            cout <<a[k];
    }
}

int main()
{
    unsigned char ch[10];
    cout << "Hay nhap 10 phan tu vao mang:" <<endl;
    for (int i = 0; i < 1; i++)
    {
        cout << "Phan tu thu "<< i+1 << " : ";
        cin >> ch[i];
    }
    ch[1]='\0';
    print_bits(ch);
    return 0;
}
