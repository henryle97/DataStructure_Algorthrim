#include <iostream>

// BT Chia qua
#define MAX 100
using namespace std;

int Apple[MAX];
int n;
int sum;

void Input()
{

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> Apple[i];
}
bool Check()
{   if (n == 1 )
        return false;
    for (int i = 0; i < n;i++)
        sum += Apple[i];
    if ((sum/2) % 100 == 0)
        return true;
    else
        return false;
}
int main()
{
    Input();
    if (Check())
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
