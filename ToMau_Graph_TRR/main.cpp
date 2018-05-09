#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

const int MAX_VERTEX = 100;         //So dinh max
vector<int> adj[MAX_VERTEX];        //Adjacency List: Danh sach ke
queue<int> store;
stack<int> vColoring;               //Stack chua cac dinh da sap thu tu hop ly de thuc hien thuat toan tham lam
vector<int> color;                  // Luu mau cua cac dinh



/* THUAT TOAN:
- Duyet do thi theo BFS bat dau tai 1 dinh co bac <= max(bac cac dinh)-1  --> Thu tu de thuc hien thuat toan tham lam
- Duyet lan luot cac dinh trong stack
 + Ban dau mau cua dinh bang 1
 + Duyet cac hang xom cua dinh do: neu da co mau do thi color++
 + Tiep tuc kiem tra voi mau moi, cho den khi nao k co hang xom co mau do thi dung
*/

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

//Breadth First Search (Duyet theo chieu rong - BFS)
void BFS(int u, int V)
{
    //Danh dau cac dinh la not visited
    vector<bool> visited(V, false);

    //Danh dau node hien tai da visited va enqueue no
    visited[u] = true;
    store.push(u);

    while (!store.empty())
    {
        //Dequeue a vertex from queue and print it
        u = store.front();
        vColoring.push(u);   //Dua u vao stack thu tu cac dinh to mau
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

//To mau
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

        //Thuc hien chon mau den khi nao ko trung voi mau hang xom
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

void writeFile(string filePath)
{
    ofstream fileOuput(filePath);

    if (fileOuput.fail())
    {
        cout << "Cannot open file !" <<endl;
        return;
    }

    fileOuput << "graph dothi" <<endl <<endl;
    fileOuput << "{" <<endl;
    for (int i = 0; i < color.size(); i++)
    {
        switch (color[i])
        {
    case 1:
        fileOuput <<"\t"<< i+1 << " [fillcolor=red, style=filled];"<<endl;
        break;
    case 2:
        fileOuput <<"\t"<< i+1 << " [fillcolor=green, style=filled];"<<endl;
        break;
    case 3:
        fileOuput <<"\t"<< i+1 << " [fillcolor=yellow, style=filled];"<<endl;
        break;
    case 4:
        fileOuput <<"\t"<< i+1 << " [fillcolor=pink, style=filled];"<<endl;
        break;
    case 5:
        fileOuput <<"\t"<< i+1 << " [fillcolor=black, style=filled];"<<endl;
        break;
    case 6:
        fileOuput <<"\t"<< i+1 << " [fillcolor=blue, style=filled];"<<endl;
        break;
    case 7:
        fileOuput <<"\t"<< i+1 << " [fillcolor=violet, style=filled];"<<endl;
        break;
    case 8:
        fileOuput <<"\t"<< i+1 << " [fillcolor=orange, style=filled];"<<endl;
        break;
    case 9:
        fileOuput <<"\t"<< i+1 << " [fillcolor=purple, style=filled];"<<endl;
        break;
    case 10:
        fileOuput <<"\t"<< i+1 << " [fillcolor=white, style=filled];"<<endl;
        break;
    default:
        break;
        }
    }       //End switch

    //Doc danh sach canh ghi vao dothitomau.txt
    ifstream fileInput("graph.txt");
    if (fileInput.fail())
    {
        cout << "Can't open file!!!" <<endl;
        return;
    }
    int a, b;
    fileInput>> a >> b;         //Doc dong dau va bo qua
    while (fileInput >> a >> b)
    {
        fileOuput << "\t" << a << "--" << b << ";" <<endl;
    }

    fileOuput << "}";
}

void readFile(string filePath, int &V)
{
    ifstream fileInput(filePath);
    if (fileInput.fail())
    {
        cout << "Error in open file!"<<endl;
        return;
    }

    int u, v;

    fileInput >> u >> v;
    V = u;
    while (fileInput >> u >> v)
    {
            adj[u-1].push_back(v-1);
            adj[v-1].push_back(u-1);

    }
}
int main()
{
    int V, edge;
    string filePathIn = "graph.txt";
    //Doc so dinh, so canh, danh sach canh ghi vao vector adj[]
    readFile(filePathIn, V);

    //To mau
    int start;
    int max = maxDegree(V);
    for (int i = 0; i < V; i++)
    {
        if (adj[i].size() <= max-1)
        {
            start = i;
            break;
        }
    }

    BFS(start, V);
    graphColoring(V);

    //Xuat ket qua ra file
    string filePathOut = "dothitomau.dot";
    writeFile(filePathOut);

    return 0;
}
