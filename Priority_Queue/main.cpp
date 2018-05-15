#include <iostream>
#include <queue>

using namespace std;
/* Priority Queue */

//Sử dụng class so sánh tự định nghĩa : priority_queue<int, vector<int>, cmp> pq;
struct cmp {
    bool operator () (int a, int b){
        return a < b;
    }
};

// Priority_Queue with Struct
struct Thing {
    int a;
    char b;

    bool operator < (const Thing &o) const {
        return a < o.a;         // Dãy giảm dần.
    }
};

struct people {
    int age, salary;
};


struct compare {
    bool operator () (const people &a, const people &b)
    {
        if (a.salary == b.salary)
            return a.age > b.age;
        else
            return a.salary > b.salary;
    }
};
int main() {
    int arr[] = {4,3,7,8,1};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Creat priority_queue : Su dung phep toan mac định là less
    priority_queue<int> pq1;
    for (int i = 0; i < n; i++)
        pq1.push(arr[i]);

    // Print pq (Mac dinh thu tu giam dan)
    cout << "pq1 : ";
    while(!pq1.empty())
    {
        cout << pq1.top() << " ";
        pq1.pop();
    }

    // Sử dụng phép toán greater (Nhỏ nhất được ưu tiên)
    priority_queue<int, vector<int>, greater<int> > pq2;

    //Add element
    for (int i = 0; i < n; i++)
        pq2.push(arr[i]);

    cout << "\npq2 : ";
    while(!pq2.empty())
    {
        cout << pq2.top() << " ";
        pq2.pop();
    }

    // Sử dụng class so sánh ( a < b thì dãy giảm dần)
    priority_queue<int, vector<int>, cmp > pq3;

    //Add element
    for (int i = 0; i < n; i++)
        pq3.push(arr[i]);

    cout << "\npq3 : ";
    while(!pq3.empty())
    {
        cout << pq3.top() << " ";
        pq3.pop();
    }

    priority_queue<Thing> pqThing;
    pqThing.push(Thing {5, 'H'});
    pqThing.push(Thing {3, 'B'});
    pqThing.push(Thing{7, 'C'});
    cout << "\npqThing : ";
    while(!pqThing.empty())
    {
        cout << pqThing.top().a << " ";
        pqThing.pop();
    }

    priority_queue<people,vector<people>,compare> pq;
    people person1,person2,person3;
    person1.salary=100;
    person1.age = 50;
    person2.salary=80;
    person2.age = 40;
    person3.salary = 100;
    person3.age=40;


    pq.push(person1);
    pq.push(person2);
    pq.push(person3);
    cout << endl;
    cout << "People " <<endl;
    while(!pq.empty())
    {
        people r = pq.top();
        pq.pop();
        cout<<r.salary<<" "<<r.age<<endl;
    }
    return 0;
}