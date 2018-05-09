#include <iostream>
#include <algorithm>
using namespace std;
/*
1. Sort all the edges in non-decreasing order of their weight.
2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle is not formed, include this edge. Else, discard it.
3. Repeat step#2 until there are (V-1) edges in the spanning tree.
*/
typedef struct {
    int src, dest, weight;
} Edge;

// A structure to represent a graph
class Graph {
    int V, E;
    Edge *edge;
    int *parent;
    int *Rank;
    Edge *result;
public:
    Graph(int V, int E);

    void addEdge(int x, int y, int weight, int i);
    // Funticon to find the subset of a element x
    int Find(int x);

    void makeSet(int x);
    // Function to do union two subsets which have root x and y
    void Union(int x, int y);

    void kruskalsMST();
};

Graph::Graph(int V, int E)
{
    this->V = V;
    this->E = E;
    edge = new Edge[E];
    parent = new int[V];
    Rank = new int [V];
    result = new Edge[V-1];         // Cay bao trum co V-1 canh
}

void Graph::addEdge(int x, int y, int weight, int i)
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

void Graph::Union(int u, int v)
{
    //int u = Find(x);
    //int v = Find(y);

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

int cmp(const void *x, const void *y)
{
    Edge *x1 = (Edge *)x;
    Edge *y1 = (Edge *)y;

    return x1->weight > y1->weight;
}
void Graph::kruskalsMST()
{

    qsort(edge, E, sizeof(edge[0]), cmp);
    int e = 0;
    int i = 0;

    while (e < V-1)
    {
        // Lay ra canh co weight lon nhat
        Edge nextEdge= edge[i++];

        int x = Find(nextEdge.src);
        int y = Find(nextEdge.dest);

        // Neu canh them vao ko tao thanh chu trinh
        if (x != y)
        {
            result[e++] = nextEdge;
            Union(x, y);
        }

        // Else chuyen sang canh tiep theo
    }   //end while

    // Print MST
    for (int i = 0; i < V-1; i++)
        cout <<result[i].src << "--" <<result[i].dest << "=" << result[i].weight<<endl;
}
int main()
{
    /* Let us create following weighted graph
             10
        0--------1
        |  \     |
       6|   5\   |15
        |      \ |
        2--------3
            4       */
    Graph g(4, 5);
    g.addEdge(0, 1, 10, 0);
    g.addEdge(1, 3, 15, 1);
    g.addEdge(0, 2, 6, 2);
    g.addEdge(2, 3, 4, 3);
    g.addEdge(0, 3, 5, 5);
    for (int i = 0; i < 4; i++)
        g.makeSet(i);
    g.kruskalsMST();
    return 0;
}
