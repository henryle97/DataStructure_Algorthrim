#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <limits.h>
using namespace std;

vector <string> words;

class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // An array of adjacency lists
    int *preVertex;

    // Fills Stack with vertices (in increasing order of finishing times).
    //  The top element of stack has the maximum finishing time
    void fillOrder(int v, bool visited[], stack<int> &Stack);

    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);

    // A recuursive function to DFS and store strongly connected component
    void DFSUtilForSearch(int v, bool visited[], list <int> &List);

public:
    Graph(int V);
    void addEdge(int v, int w);

    // The main function that finds and prints strongly connected components
    int printSCCs();

    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();

    // Funtion to find position of string in words
    int findPosition(string word);

    // Function that finds and prints strongly connected components which have word
    void printSCCsOfWord(string word);

    void shortestPath(string s, string e);
};



Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    preVertex = new int[V];
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;


    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); i++)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

void Graph::DFSUtilForSearch(int v, bool visited[], list <int> &List)
{
    visited[v] = true;
    List.push_back(v);

    list <int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFSUtilForSearch(*i, visited, List);
}

Graph Graph::getTranspose()
{
    Graph temp(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            temp.adj[*i].push_back(v);
        }
    }
    return temp;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// Position of word in vector
int Graph::findPosition(string word)
{
    int key;

    vector <string>::iterator x = find(words.begin(), words.end(), word);
    if (x == words.end())
        cout << "Can't fint word in words! " <<endl;
    else
        key = x - words.begin();

    return key;
}

// Ham de quy duyet cac dinh va dua cac dinh duyet xong vao stack (post lon nhat nam top stack)
void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); i++)
        if(visited[*i] == false)
            fillOrder(*i, visited, Stack);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

// The main function that finds and prints all strongly connected
// components
int Graph::printSCCs()
{
    stack<int> Stack;

    // Create a reversed graph
    Graph gr = getTranspose();

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing time
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            gr.fillOrder(i, visited, Stack);

    // Duyet DFS tren do thi ban dau
    int LT = 0;
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            LT++;
            DFSUtil(v, visited);        // for G

        }
    }
    return LT;
}

void Graph::printSCCsOfWord(string word)
{
    stack <int> Stack;
    list <int>::iterator it;
    bool *visited = new bool[V];
    // Transpose Graph g->gr
    Graph gr = getTranspose();

    // Position of word in vector
    int key = findPosition(word);

    // Mark visited of all vertices are false
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Fill in Stack
    for (int v = 0; v < V; v++)
    {
        if (visited[v] == false)
            gr.fillOrder(v, visited, Stack);
    }

    // DFS in G
    for (int i = 0; i < V; i++)
        visited[i] = false;

    while(Stack.empty() != true)
    {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false)
        {
            list <int> List;
            DFSUtilForSearch(v, visited, List);             // Duyet DFS, luu thanh phan lien thong vao List
            it = find(List.begin(), List.end(), key);       // Check xem key co trong List ko (neu ko co thi it = List.end() )
            if ( it != List.end())
            {
                for (it = List.begin(); it != List.end(); it++)
                    cout << words[*it] << " -> ";

                return;
            }
        }
    }   // End while
}

// Find Shorstest Path in directed graph and ko co trong so
void Graph::shortestPath(string s, string e)
{
    //Find position of s and e in words
    int src = findPosition(s);          // source
    int dst = findPosition(e);          // destination

    // Distance of u through source
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
            break;
        // 'i' is used to get all adjacent vertices of a vertex
        list <int>::iterator i;
        for (i = adj[u].begin(); i!= adj[u].end(); i++)
        {
            // Get vertex label and weight of current adjacent
            int v = (*i);
            int weight = 1;

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

    // Print Path;
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
        cout << words[tmp] << " -> ";
    }
    return;

}

// Function de check 4 chu cuoi cua w1 co trong w2 ko
bool checkWords(string w1, string w2)
{
    int d = 0;
    bool checked[10];
    for (int i = w1.size()-1; i >= w1.size()-4; i--)
    {
        for (int j = 0; j < w2.size(); j++)
        {
            if (w1[i] == w2[j] && checked[j] != true)
            {
                d++;
                checked[j] = true;
                break;      //thoat for (j)
            }
        }
    }
    if (d == 4 )
        return true;
    else
        return false;
}

// Return tong so canh trong do thi
int Graph::soCung()
{
    int cung = 0;

    for (int v = 0; v < V; v++)
    {
        cung += adj[v].size();

    }

    return cung;
}


void readFile(string filePath)
{
    ifstream file(filePath);

    if (file.fail())
    {
        cout << "Can't open file !" <<endl;
        return;
    }
    string getWord;
    while (file >> getWord)
    {
            words.push_back(getWord);
    }
}
int main()
{
    // Read file then creat graph
    string filePath = "sgb-words.txt";
    readFile(filePath);

    int n = words.size();
    Graph g(n);
    cout <<"So dinh " << n <<endl;
    cout << "Dang them canh vao do thi ..." <<endl;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
        {
            if (checkWords(words[i], words[j]))
                g.addEdge(i, j);
            if (checkWords(words[j], words[i]))
                g.addEdge(j, i);
        }
    cout << "Them xong !!!" << endl;
    // MENU
    cout << "\t\tMENU\t\t" <<endl;
    cout << "1. Dem so thanh phan lien thong manh" <<endl;
    cout << "2. Nhap u, in ra cac dinh cung thanh phan lien thong voi u" <<endl;
    cout << "3. Nhap u va v, in ra duong ngan nhat tu u den v" <<endl;
    cout << "4. Thoat" <<endl;

    int choose = 0;
    string u, v;
    while (choose != 4)
    {
        cout << "Moi ban chon: "; cin >> choose;
        switch(choose)
        {
            case 1: int soLT;
                    soLT = g.printSCCs();
                    cout << "So thanh phan lien thong manh la: " << soLT <<endl;
                    break;
            case 2: cout << "Nhap u: " ; cin >> u;
                    g.printSCCsOfWord(u);
                    cout << endl;
                    break;
            case 3: cout << "Nhap u: " ; cin >> u;
                    cout << "Nhap v: " ; cin >> v;
                    cout << "Shortest Path ";
                    g.shortestPath(u, v);
                    cout << endl;
                    break;
            case 4: break;
            default:
                    cout << "Nhap sai, nhap lai " << endl;
        }
    }

    return 0;
}
