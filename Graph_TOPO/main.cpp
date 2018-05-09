#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

/*Bài Toán : Đầu vào là danh sách cạnh của đồ thị CÓ HƯỚNG (có thể có đỉnh đứng 1 mình)

            --> Sap Topo cho mot DAG
*/
//ASCII : 'A' = 65

const int MAX_DEGREE = 100;
vector<char> adj[MAX_DEGREE];                //Mang vector chua hang xom cua cac dinh
int V = MAX_DEGREE;                  //So dinh
int E;                               //So canh
int preArr[100] = {};
int postArr[100] = {};            //Khoi tao cac gia tri bang 0
static int c = 1;
vector<bool> check(V, false);           //Danh dau da dua dinh ra thu tu Topo


//Function compare for sort in vector
bool compare(int u, int v)
{
    return u < v;
}

int convert(char x)
{
    return (int)(x - 65);
}

//Add Edges
void addEdge()
{
    char u, v;
    int edge;
    cout << "Nhap so dinh va so canh: " <<endl;
    cin >> V >> E;
    cout << "Nhap danh sach canh (Co huong): " <<endl;
    edge = E;
    do {
        cin >> u >> v;
        if (u < 'A' || u > 'Z' || v < 'A' || v > 'Z')
        {
            cout << "Nhap lai" <<endl;
            continue;
        }
        else
        {
            adj[(int)u - 65].push_back((int)v - 65);
            edge--;
        }
    } while (edge != 0);

    // Neu phai thuc hien lua chon chinh thi chon dinh theo thu tu tu dien
    for(int u = 0; u < V; u++)
    {
        sort(adj[u].begin(), adj[u].end(), compare);            //Sap xep thu tu dinh tang dan
    }
}


//Visit mo rong cac hang xom cua u
void explore(int u, vector<bool> &visited)
{
    //Danh dau u da ghe tham
    visited[u] = true;

    preArr[u] = c++;
    //Duyet hang xom cua u
    for(int i = 0; i < adj[u].size(); i++)
    {
        if(visited[adj[u][i]] == false)
        {
            explore(adj[u][i], visited);
        }
    }
    postArr[u] = c++;
}

//Depth Find Search
int DFS()
{
    vector<bool> visited(V, false);
    for(int u = 0; u < V; u++)
    {
        if(visited[u] == false)
        {
            explore(u, visited);
        }
    }
}

//Check DAG (Do thi phi chu trinh)
bool checkDAG()
{
    for (int u = 0; u < V; u++){
        for (int i = 0; i < adj[u].size(); i++)
        {
            if (preArr[u] > preArr[adj[u][i]] && postArr[u] < postArr[adj[u][i]])
                return false;
        }
    }
    return true;
}

int findIndexPostMax()
{
    int max = 0;
    int index;
    for (int i = 0; i < V; i++)
    {
        if (postArr[i] > max && check[i] != true)
        {
            max = postArr[i];
            index = i;
        }
    }
    check[index] = true;
    return index;
}
//Sap Topo
void arrangeTopo()
{
    if (checkDAG() == false)
    {
        cout << "Do thi khong phai DAG nen ko the sap thu tu Topo" << endl;
        return;
    }
    else {
        cout << "Thu tu Topo:  ";
        for (int u = 0; u < V; u++)
        {

            cout << (char)(findIndexPostMax() + 65) << " ";
        }
    }
}


int main()
{

    addEdge();
    DFS();
    arrangeTopo();
    return 0;
}
