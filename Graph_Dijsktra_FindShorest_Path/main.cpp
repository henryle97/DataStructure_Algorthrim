#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <stack>
#include <limits.h>


using namespace std;


// Undirected and weight graph
class Graph {
    int V;      // So dinh
    list< pair<int, int> > *adj;       // adj vertex
    int *preVertex;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int src, int dst);
    void printPath(int src, int dst);

};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list< pair<int, int> >[V];
    preVertex = new int[V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src, int dst)
{

    vector<int> dist(V, INT_MAX);       // dist(u) = dist src->u

    // Cau truc set de luu tru dist cac dinh tu be den lon khi duyet iterator begin()->end()
    set < pair<int, int> > setds;       // set se sort dua vao phan tu thu nhat cua pair

    setds.insert(make_pair(0, src));
    dist[src] = 0;

    while(!setds.empty())
    {
        // Dinh dau tien trong set la dinh co distance den src be nhat -> se k con duoc them vao lai nua
        // Dinh chon de duyet la dinh co dist min
        pair <int, int> tmp = *(setds.begin());
        setds.erase(setds.begin());

        // vertex label is stored in second of pair
        int u = tmp.second;

        if (u == dst)
            return;
        // 'i' is used to get all adjacent vertices of a vertex
        list < pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i!= adj[u].end(); i++)
        {
            // Get vertex label and weight of current adjacent
            int v = (*i).first;
            int weight = (*i).second;

            // If there is a shorter path to v through u
            if (dist[v] > dist[u] + weight)
            {
                // If dist != INT_MAX (danstore trong set) -> update vao set
                if (dist[v] != INT_MAX)
                    setds.erase(setds.find(make_pair(dist[v], v)));     // Tim vi tri chua v va xoa

                // Update dist of v
                dist[v] = dist[u] + weight;
                preVertex[v] = u;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }
}

void Graph::printPath(int src, int dst)
{
    stack <int> Path;

    Path.push(dst);
    int tmp = dst;
    while(tmp != src)
    {
        tmp = preVertex[tmp];
        Path.push(tmp);
    }

    while (!Path.empty())
    {
        tmp = Path.top();
        Path.pop();
        cout << tmp << " -> ";
    }
}
int main()
{
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 3, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 2);
    g.addEdge(2, 3, 1);

    g.shortestPath(0, 4);
    g.printPath(0, 4);
    return 0;
}
