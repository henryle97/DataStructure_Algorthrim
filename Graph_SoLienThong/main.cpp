#include <iostream>
#include <vector>


using namespace std;

/*Bài Toán : Đầu vào là danh sách cạnh của đồ thị VÔ HƯỚNG (có thể có đỉnh đứng 1 mình)
             Đầu ra là số thành phần liên thông
*/

const int MAX_DEGREE = 100;
vector<char> adj[MAX_DEGREE];                //Mang vector chua hang xom cua cac dinh


void explore(int u, vector<bool> &visited);

//Add Edges
void addEdge()
{
    int u = -2, v = -2;
    do {
        cin >> u >> v;
        if (-1 == v || u == -1 && v == -1)
            continue;
        else {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    } while (u != -1 || v != -1);

}

//Depth Find Search
int DFS(int nVertex)
{
    vector<bool> visited;
    int soLienThong = 0;
    //Danh dau cac dinh unvisited
    visited.assign(nVertex, false);

    //Duyet tat cac cac dinh
    for (int u = 0; u < nVertex; u++)
    {
        if (visited[u] == false)
        {
            soLienThong++;                          //Gap dinh dau tien chua visited
            cout <<endl;
            visited[u] = true;
            explore(u, visited);
        }
    }
    return soLienThong;
}
//Visit mo rong cac hang xom cua u
void explore(int u, vector<bool> &visited)
{
    //Danh dau u da ghe tham
    visited[u] = true;
    cout << u << " ";

    //Duyet cac hang xom cua u, neu chua ghe tham thi DFSUtil no
    /*
    for(int i = 0; i < adj[u].size(); i++)
    {
        if(visited[adj[u][i]] == false)
            explore(adj[u][i], visited);
    }
    */
    for (auto i = adj[u].begin(); i != adj[u].end(); i++)
        if (visited[*i] == false)
            explore(*i, visited);
}

//Tinh so thanh phan lien thong bang duyet sau
int connectComponent(int nVertex)
{
    return DFS(nVertex);
}
int main()
{
    int nVertex;                                //So dinh
    int nDegree;                                //
    int u = -1, v = -1;                                   //Bien tam thoi luu dinh nhap vao

    //Buoc nhap DS canh
    cout << "Nhap so dinh cua do thi n =  ";
    cin >> nVertex;
    cout << "Nhap danh sach canh (dinh phai chua 0, bat dau tu 0 -> n-1, \n -voi dinh dung mot minh thi nhap dinh thu 2 la bang -1 \n -ket thuc nhap ca 2 dinh bang -1): " <<endl;
    addEdge();

    //Tinh so thanh phan lien thong
    int connected = connectComponent(nVertex);
    cout << "\nSo thanh phan lien thong la " << connected;

    //In ra cac thanh phan lien thong


    return 0;
}
