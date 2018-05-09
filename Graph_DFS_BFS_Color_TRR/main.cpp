#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <windows.h>

using namespace std;

const int MAX_VERTEX = 100;         //So dinh max
vector<int> adj[MAX_VERTEX];        //Adjacency List: Danh sach ke
stack<int> vColoring;               //Stack chua cac dinh da sap thu tu hop ly de thuc hien thuat toan tham lam
vector<int> color;
vector<string> colorList;




//Function to add a edge in a undirected graph
void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

//Depth First Search - Graph Traversal (DFS - Duyet theo chieu sau)
/*
- Bat dau tai root
- Ung dung stack
UNG DUNG:
Xác định các thành phần liên thông của đồ thị
Sắp xếp tô-pô cho đồ thị
Xác định các thành phần liên thông mạnh của đồ thị có hướng
Kiểm tra một đồ thị có phải là đồ thị phẳng hay không

*/
void DFSUtil(int u, vector<int> adj[], vector<bool> &visited)
{
    visited[u] = true;          // Danh dau dinh u da ghe tham
    cout << u << " ";
    for (int i = 0; i < adj[u].size(); i++)     //Duyet cac hang xom cua dinh u
        if (visited[adj[u][i]] == false)
            DFSUtil(adj[u][i], adj, visited);
}
//This function does DFSUtil() for all unvisited vertices
void DFS(vector<int> adj[], int V)
{
    vector<bool> visited(V, false);     //Khoi tao visited tat ca cac dinh la false (chua ghe tham)
    for (int u = 0; u < V; u++)
        if (visited[u] == false)
            DFSUtil(u, adj, visited);
}

//Breadth First Search (Duyet theo chieu rong - BFS)
/*
- Dung Queue - FIFO
*/
void BFS(int u, int V)
{
    //Danh dau cac dinh la not visited
    vector<bool> visited(V, false);
    queue<int> store;

    //Danh dau node hien tai da visited va enqueue it
    visited[u] = true;
    store.push(u);

    while (!store.empty())
    {
        //Dequeue a vertex from queue and print it
        u = store.front();
        cout << u << " ";
        vColoring.push(u);   //Nhet u vao stack thu tu cac dinh to mau ( V(n) )
        store.pop();        //Bo dinh o dau queue ra khoi queue

        //Duyet cac hang xom cua dinh u: danh dau true va nhet het vao queue
        for ( int i = 0; i < adj[u].size(); i++)
        {
            if (visited[adj[u][i]] == false)
            {
                visited[adj[u][i]] = true;
                store.push(adj[u][i]);
            }
        }
    }
}

//Max of color = max of degree + 1
int maxDegree(int V)
{
    int max = 0;
    int degree;
    for (int i = 0; i < V; i++)
    {
        degree = adj[i].size();
        if (degree > max)
            max = degree;
    }
    return max;             //Tra lai max degree
}

//To mau
/*
- Duyet do thi theo BFS roi dua vao stack (duyet truoc vao truoc)
- Duyet lan luot cac dinh trong stack
 + Ban dau mau cua dinh bang 1
 + Duyet cac hang xom cua dinh do: neu da co mau do thi color++
 + Tiep tuc kiem tra voi mau moi, cho den khi nao k co hang xom co mau do thi dung
*/
void graphColoring(int V) {
    //Gan all color = 0 (chua to mau) ;
    color.assign(V, 0);
    int u;                                  // Vertex duyet
    int tempColor;                          //Mau tam thoi cua dinh
    int offColor;                            //Mau chinh thuc cua dinh (official)

    while (!vColoring.empty())              //Trong khi stack chua rong
    {
        u = vColoring.top();
        vColoring.pop();                    //Stack doesn't return the value removed from the stack
        tempColor = 1;
        do {
            offColor = tempColor;
            for (int i = 0; i < adj[u].size(); i++)
                if (color[adj[u][i]] == tempColor)
                {
                    tempColor++;
                    break;
                }
        } while (offColor != tempColor);
        color.at(u) = offColor;                 //Gan mau offColor cho dinh u
    }

}
//Function to print the adjacency list represented of graph
void printGraph(vector<int> adj[], int V)
{
    for (int v = 0; v < V; v++)
    {
        cout << "\n Adjacency list of vertex " << v << "\n head";
        for (auto x : adj[v])
            cout << "-> " << x;
    }
}
int main()
{

    /*int V = 5;      // 5 vertex
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    */
    int V, edge;
    int u, v;
    cout << "Nhap so dinh va so canh: ";
    cin >> V >> edge;
    for (int i = 0; i < edge; i++)
    {
        cin >> u >> v;
        addEdge(adj, u, v);
    }
    cout << "Duyet theo DFS" <<endl;
    DFS(adj, V);
    cout <<endl;
    cout << "Duyet theo BFS" <<endl;
    BFS(0, V);
    cout<<"\n";

    //To mau
    graphColoring(V);

    for (int i = 0; i < V; i++)
    {
        system("Color 0A");
        cout << "Dinh " << i << " co mau " << color[i]<<endl;
    }

    return 0;
}
