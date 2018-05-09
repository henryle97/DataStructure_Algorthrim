#include <iostream>
#include <map>

using namespace std;

int main()
{
    map <int, string> Map;
    Map.insert(pair <int, string>(0, "hi"));
    Map[1] = "ga";
    //map <int, string>::iterator it;
    auto it = Map.find(0);    cout << *it.first;
    return 0;
}
