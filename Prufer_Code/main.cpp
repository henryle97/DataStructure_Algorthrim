#include <iostream>
#include <string.h>
#include <limits>

using namespace std;

//Cau truc cho canh
typedef struct {
    int node1;
    int node2;
} DG;     //Degree

void creatDegreeList(DG *degree, int *level, int size)
{
    for (int i = 0; i < size; i++)    //n-1 canh
    {
        cin >> degree[i].node1 >> degree[i].node2;
        level[degree[i].node1] += 1;
        level[degree[i].node2] += 1;
    }

}

int level1(int *level, int n)
{
    int node;                       //Tim node bac 1 nho nhat khac 0
    for (int i=1; i < n; i++)
    {
        if (level[i] == 1)
            {
                node = i;
                return node;
            }

    }
    return 0;
}

void deleteArr(DG **degree, int size, int position)
{
    for (int k=position; k < size-1; k++)
    {
        *(degree[k]) = *(degree[k + 1]);
    }

}
void prufer(DG *degree, int *level, int *code, int n, int count)
{
    int node;
    int m = 0;                      //bien dem cho mang code
    while (count > 1)
    {
        //Tim node bac 1 nho nhat
        node = level1(level, n);
        if (node == 0)
            return;
        //Dua no vao array code[]
        code[m] = node;
        m++;

        //Giam bac hang xom va xoa canh do
        for (int i=0; i < count; i++)
        {
            if (degree[i].node1 == node)
            {
                level[degree[i].node2]--;       //giam bac hang xom di 1
                //deleteArr(&degree, count, i);   //xoa canh tai vi tri i;
                /*for (int k=i; k < count-1; k++)
                {
                    degree[k] = degree[k + 1];
                }
                count--;
                break;
                */
                level[degree[i].node1]--;
            }
            else if (degree[i].node2 == node)
            {
                level[degree[i].node1]--;       //giam bac hang xom di 1
                //deleteArr(&degree, count, i);   //xoa canh tai vi tri i;
                /*for (int k=i; k < count-1; k++)
                {
                    degree[k] = degree[k + 1];
                }
                count--;
                break;*/
                level[degree[i].node2]--;
            }
        }
    }
}

void printList(int *code, int size)
{
    for (int d = 0; d < size; d++)
        cout << code[d] << " ";
}
int main()
{
    int n;
    do {
        cout << "Nhap so dinh dan nhan: ";      //Tree n dinh ung voi n-1 canh
        cin >> n;
    } while (n <= 2);

    int count = n-1;                          // So canh, chuong trinh dung khi count = 1
    DG *degree = new DG[n-1];               //mang quan ly cac canh
    int *level = new int[n];                //mang quan ly bac cua dinh, default = 0
    int *code = new int[n-2];               //Ma prufer dai n-2

    creatDegreeList(degree, level, n-1);
    prufer(degree, level, code, n, count);
    printList(code, n-2);
    //printList(level, n);
    return 0;
}
