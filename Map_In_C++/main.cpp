#include <iostream>
#include <map>
#include <iterator>

using namespace std;

int main()
{
    map <int, int> map1;

    // Insert elements in random order
    map1.insert(pair <int, int> (1, 40));
    map1.insert(pair <int, int> (2, 30));
    map1.insert(pair <int, int> (3, 60));

    // Printing map map1
    map <int, int> :: iterator itr;         //Con tro dac biet duyet cac cau truc Collection
    cout << "\n The map map1 is: \n";
    cout << "\tKEY\tELEMENT\n";
    for(itr = map1.begin(); itr != map1.end(); ++itr)
    {
        cout << "\t" << itr->first
             << "\t" << itr->second <<"\n";
    }
    cout << endl;

    // Asigning the elements from map1 to map2
    map <int, int> map2(map1.begin(), map1.end());
    cout << "\n The map map2 is: \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = map2.begin(); itr != map2.end(); ++itr)
    {
        cout << "\t" << itr->first
             << "\t" << itr->second <<endl;
    }
    cout << endl;

    // Remove elements up to element with key = 3 in map1
    map1.erase(map1.begin(), map1.find(3));
    cout << "\n map1 after removal of elements less than key = 3: \n";
    cout << "The map map1 is: \n";
    cout << "\tKEY\tELEMENT\n";
    for(itr = map1.begin(); itr != map1.end(); ++itr)
    {
        cout << "\t" << itr->first
             << "\t" << itr->second <<"\n";
    }
    cout << endl;

    // Remove all element with key = 2
    map2.erase(2);
    cout << "map2.erase(2): 2 removed ";
    cout << "\n The map map2 is: \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = map2.begin(); itr != map2.end(); ++itr)
    {
        cout << "\t" << itr->first
             << "\t" << itr->second <<endl;
    }
    cout << endl;
    return 0;
}
