#include <iostream>

using namespace std;

/*Disjoint Set for Detect Cycle in an Undirected Graph
    + find(x) : tim goc cua x
    + union(x, y) : hop 2 tap con chua x, y
    + Union-Find Algorithm
*/

// A structure to represent an edge in a graph
typedef struct {
    int src, dest;
} Edge;
// A structure to represent a graph
class Graph {
    int V, E;
    Edge *edge;
    int *parent;
    int *Rank;
public:
    Graph(int V, int E);

    void addEdge(int x, int y, int i);
    // Funticon to find the subset of a element x
    int Find(int x);

    void makeSet(int x);
    // Function to do union two subsets which have root x and y
    void Union(int x, int y);

    // Function to check whether a graph contains cycle or not
    bool isCycle();
};

Graph::Graph(int V, int E)
{
    this->V = V;
    this->E = E;
    edge = new Edge[E];
    parent = new int[V];
    Rank = new int [V];
}

void Graph::addEdge(int x, int y, int i)
{
    edge[i].src = x;
    edge[i].dest = y;
}

void Graph::makeSet(int x)
{
    parent[x] = x;
    Rank[x] = 0;
}
int Graph::Find(int x)
{
    while (parent[x] != x)
    {
        x = parent[x];
    }
    return x;
}

void Graph::Union(int x, int y)
{
    int u = Find(x);
    int v = Find(y);

    if (Rank[u] > Rank[v])
    {
        parent[v] = u;
    }
    else {
        parent[u] = v;
        if (Rank[u] == Rank [v])
            Rank[v] += 1;
    }
}

bool Graph::isCycle()
{
    for (int i = 0; i < V; i++)
        makeSet(i);

    for (int i = 0; i < E; i++)
    {
        int u = Find(edge[i].src);
        int v = Find(edge[i].dest);
        if (u == v)
            return true;    // have cycle

        Union(u, v);
    }
    return false;
}
int main()
{
     /* Let us create following graph
         0
        |  \
        |    \
        1-----2 */
    Graph g(3, 3);

    g.addEdge(0, 1, 0);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);

    // Tao ra V tap, moi tap chua i


    bool checkCycle = g.isCycle();
    if (checkCycle == true )
        cout << "Graph have a cycle" <<endl;
    else
        cout << "Graph don't have cycle" <<endl;
    return 0;
}
