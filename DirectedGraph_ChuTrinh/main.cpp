#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

/*Bài Toán : Đầu vào là danh sách cạnh của đồ thị CÓ HƯỚNG (có thể có đỉnh đứng 1 mình)
             Đầu ra là thong tin canh: tree/forward, back,     egde
*/
//ASCII : 'A' = 65

const int MAX_DEGREE = 100;
vector<char> adj[MAX_DEGREE];                //Mang vector chua hang xom cua cac dinh
int V = MAX_DEGREE;                  //So dinh
int E;                               //So canh
int preArr[100] = {};
int postArr[100] = {};              //Khoi tao cac gia tri bang 0
static int c = 1;

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
    //Duyet cac hang xom cua u, neu chua ghe tham thi DFSUtil no
    for(int i = 0; i < adj[u].size(); i++)
    {
        if(visited[adj[u][i]] == false)             //Neu hang xom chua ghe tham
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


void checkEdge()
{
    bool is = false;
    for (int u = 0; u < V; u++)
    {
        for(int v = 0; v < adj[u].size(); v++)
        {
            if(preArr[u] > preArr[adj[u][v]] && postArr[u] < postArr[adj[u][v]])
            {   cout << (char)(u + 65) << "-" << (char)(adj[u][v] + 65) << ": ";
                cout << "Back Edge" << endl;
                is = true;
            }

        }
    }

    if (is == false)
        cout << "Khong co Back Edge" << endl;
}

void checkChuTrinh()
{
    for (int u = 0; u < V; u ++)
        for (int i = 0; i < adj[u].size(); i++)
            {
                if (preArr[u] > preArr[adj[u][i]] && postArr[u] < postArr[adj[u][i]])
                {
                    cout << "Co chu trinh" << endl;
                    return;
                }
            }
    cout << "Khong co chu trinh" <<endl;
}
int main()
{

    addEdge();
    DFS();
    checkEdge();
    checkChuTrinh();
    return 0;
}
