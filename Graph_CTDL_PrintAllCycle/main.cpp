#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Graph
{
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int u, int v);
    void readFile(string filePath);
    void explore(int u);
    void DFS();

}
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void explore(int u, int &e, vector<bool> &visited, list<int> &List)
{
    list<int>::iterator i;
    for(i = adj[u].begin(); i != adj[u].end(); i++)
    if (visited[*i] == false)
    {
        visited[*i] = true;
        explore(*i, visited, List);
    }
}
void DFS()
{
    vector<bool> visited(V, false);
    list<int> List;
    for(int u = 0; u < V; u++)
    {
        s = u;
        e = -1;
        if (visited[u] == false)
            explore(u, e, visited);
    }
}
void addEdge(int u, int v);
{
    adj[]
}
int main()
{
    string filePath = "graph.txt";
    readFile(filePath);



    return 0;
}
