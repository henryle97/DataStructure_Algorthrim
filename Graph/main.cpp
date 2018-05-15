#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

/* Y tuong :
- Duyet DFS , gap dinh da tham thi copy stack hien tai roi in ra -> 1 chu trinh
- Neu k DFS duoc nua thi day dinh top ra khoi stack va danh dau chua tham.
*/

class Graph
{
    int V;
    list<int> *adj;
    vector<bool> visited;           // Dam bao duyet tat cac cac thanh phan lien thong
    vector<bool> checked;           // Danh dau
    vector<pair<int,int>> backEdge;
    stack<int> myStack;
    unordered_map<int, unordered_set<int>> hashTable;


public:
    Graph(int V);
    void addEdge(int u, int v);
    void readFile(string filePath);
    void explore(int u);
    void DFS();
    void printStack(stack<int> s, int v);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    for(int i = 0; i < V; i++)
    {visited.push_back(false);
        checked.push_back(false);}
}

void Graph::printStack(stack<int> s, int v)
{
    //unordered_set<int> cycle;
    while(s.top() != v)           //Dung khi gap backedge
    {
        cout << s.top() << "<--";
        //int top = s.top();
        //cycle.insert(top);
        s.pop();
    }
    cout << s.top();

    /*cycle.insert(v);

    if (hashTable.find(cycle) != hashTable.end())
    {
        int i = 0;
        unordered_set<int>::iterator it;
        for (it = cycle.begin(); it != cycle.end(); it++)
            cout << *it << "--";
        cout << endl;
        hashTable[cycle] = 0;
    }*/

}
void Graph::explore(int u)
{
    checked[u] = true;
    visited[u] = true;
    myStack.push(u);

    list<int>::iterator i;
    for(i = adj[u].begin(); i != adj[u].end(); i++)
        if (checked[*i] == false)
        {
            checked[*i] = true;
            explore(*i);
        }
        else {      // gap dinh da tham

            printStack(myStack, *i);
            cout <<endl;
        }

    // Neu k DFS duoc nua
    int top = myStack.top();
    myStack.pop();
    checked[top] = false;
}
void Graph::DFS(){

    for(int u = 0; u < V; u++)
    {
        if (visited[u] == false)
            explore(u);
    }
}



void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::readFile(string filePath)
{
    ifstream file(filePath);

    if(file.fail())
    {
        cout << "Can't open file!"<<endl;
        return;
    }
    file >> V;
    int u, v;
    while (file >> u >> v)
    {
        addEdge(u, v);
    }
}
int main()
{
    string filePath = "graph.txt";
    ifstream file(filePath);

    if (!file.fail()) {

        int soDinh;
        file >> soDinh;
        Graph g(soDinh);

        int u, v;
        while (file >> u >> v) {
            g.addEdge(u, v);
        }

        g.DFS();


        return 0;
    } else {
        cout << "Can't open file!" << endl;
        return -1;
    }
}
