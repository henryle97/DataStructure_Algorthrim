#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

/* Bai 1*/
using namespace std;

vector <string> words;            // All words in file
vector <int> edge[6000];            // Edges List


/* Xay dung do thi VO HUONG*/

// Doc file roi dua cac tu vao 1 vector
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


// Function to check hai tu co khac nhau dung mot ky tu hay ko ?
bool checkWords(string w1, string w2)
{
    int d = 0;
    for (int i = 0; i < w1.size(); i++)
    {
            if (w1[i] != w2[i])
            d++;
    }
    if (d == 1)
        return true;
    else
        return false;
}

// Xac dinh cac canh cua do thi
void addEdge()
{
    int n = words.size();
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
        {
            /* Neu 2 tu khac 1 ky tu thi them canh */
            if (checkWords(words[i], words[j]))
            {
                edge[i].push_back(j);
                edge[j].push_back(i);
            }
        }
}

/* Dem so thanh phan liên thông (bằng DFS) */
// Duyet tat ca hang xom cua u
void explore(int u, vector <bool> &visited)
{
    visited[u] = true;
    for (int i = 0; i < edge[u].size(); i++)
    {
        if (visited[edge[u][i]] == false)
            explore(edge[u][i], visited);
    }
}

int DFS()
{
    int n =  words.size();
    vector <bool> visited(n, false);
    int soLienThong = 0;

    for (int u = 0; u < n; u++)
    {
        if (visited[u] == false)
        {
            soLienThong++;
            explore(u, visited);
        }
    }
    return soLienThong;
}


// So Lien Thong
int soLienThong()
{
    return DFS();
}


/* Duong di ngan nhat tu u den v */
/* NX: Đây là đồ thị vô hướng không có trọng số (unweight graph)
    + Solution: use a modified version of BFS in which we keep storing the
        predecessor of a given vertex while doing the BFS.
    + O(V+E)
*/

// Duyet BFS de tim path ngan nhat
bool shortestPathWithBFS(int srcIndex, int dstIndex, vector <int> &prev)
{
    int n = words.size();

    queue <int> travel;
    vector <bool> visited(n, false);
    int u = srcIndex;
    travel.push(u);          //Nhet dinh goc vao
    while (!travel.empty())
    {
        visited[u] = true;
        u = travel.front();
        travel.pop();
        for (int i = 0; i < edge[u].size(); i++)
        {

            if (visited[edge[u][i]] == false)
            {
                visited[edge[u][i]] = true;
                travel.push(edge[u][i]);
                prev[edge[u][i]] = u;
            }
            // Neu dinh do la destination
            if (edge[u][i] == dstIndex)
                return true;
        }
    }
    return false;
}

// Shortest Path
void printShortPath(string src, string dst)
{
    int n = words.size();
    vector <int> prev(n, -1);           // Vector luu predecessor
    vector <int> path;
    int srcIndex, dstIndex;

    // Tim index cua src va dst trong words
    for (int i = 0; i < words.size(); i++)
    {
        int d = 0;
        if (src == words[i])
            {srcIndex = i;
            d++;}
        if (dst == words[i])
            {dstIndex = i;
            d++;}
        if (d == 2)
            break;
    }
    bool check = shortestPathWithBFS(srcIndex, dstIndex, prev);
    if (check == false)
    {
        cout << "Ko co duong di giua hai tu nay" <<endl;
        return;
    }

    cout << "Duong di giua 2 tu nay la: ";
    path.push_back(dstIndex);
    int temp = dstIndex;
    // Lan ve truoc cac dinh da duyet tao thanh duong di can tim
    while (prev[temp] != -1)
    {
        path.push_back(prev[temp]);
        temp = prev[temp];
    }
    for (int i = path.size()-1; i >= 0; i--)
    {
        cout << words[path[i]];
        if (i != 0)
            cout << " -> ";
    }
}

int main()
{
    string filePath = "sgb-words.txt";
    readFile(filePath);
    addEdge();
    cout << "So thanh phan lien thong la " << soLienThong() <<endl;

    string u, v;
    cout << "Nhap 2 tu:" <<endl;
    cin >> u >> v;
    printShortPath(u, v);

    return 0;
}
