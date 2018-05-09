#include <iostream>
#include <vector>


using namespace std;

/*  Greedy Activity Selector :
- Sap xep cac hoat dong theo thu tu tang cua time ket thuc
- Khi do hoat dong 1 la hoat dong dau tien duoc chon (j = 1)
- Voi moi hoat dong tiep theo, check xem Si > Fj thi ta chon hoat dong do
- Time O(n)
- Nhan xet: Sau moi lua chon tham, ta duoc mot bai toan co dang tuong thich voi bai toan ban dau.
Mo rong :
- Hoat dong time ngau nhien -> sort time (with quick sort) - voi O(nlogn)
- Chi ro hoat dong nao duoc chon.
*/
vector< pair<int, int> > activity;
vector<int> A;          // Activity selector

/* Voi activity sorted theo time finish in ascending order (tang dan) */
void greedyActivitySelector()
{
    int i;                  // action current
    int j;                  // newest action push

    // Lua chon tham dau tien
    A.push_back(0);         // push action 0 into A
    j = 0;                  // update action vua them vao A

    /* Voi moi hoat dong dang xet, kiem tra neu Si > Fj thi moi them vao A */
    for (int i = 1; i < activity.size(); i++)
    {
        if (activity[i].first > activity[j].second)
        {
            A.push_back(i);
            j = i;
        }
    }

}

void printActivitySelected()
{
    cout << "Co the sap xep " << A.size() << " hoat dong. " <<endl;
    for (int i = 0; i < A.size(); i++)
    {
        cout << "(" << activity[A[i]].first << "," << activity[A[i]].second << ")" <<endl;
    }
}

int main()
{
    int n;      // so hoat dong
    int a, b;       // temp time
    cout << "Nhap so hoat dong: "; cin >> n;
    cout << "Nhap time bat dau va time ket thuc:" <<endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Hoat dong " << i << ":" <<endl;
        cout << "Start Time: "; cin >> a;
        cout << "Finish Time: "; cin >> b;
        activity.push_back(make_pair(a, b));
    }
    greedyActivitySelector();

    // In ra cac hoat dong da chon
    printActivitySelected();
    return 0;
}
