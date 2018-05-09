#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

vector <string> words;          // Store string from file
vector <int> edge[6000];        // Store edge between two string
vector <int> G2[6000];          // Do thi nguoc

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

// Function de check 4 chu cuoi cua w1 co trong w2 ko
bool checkWords(string w1, string w2)
{
    int d = 0;
    for (int i = 4; i >= 1; i--)
    {

        for (int j = 0; j < w2.size(); j++)
        {
            if (w1[i] == w2[j])
            {
                d++;
                break;      //thoat for (j)
            }
        }
    }
    if (d == 4 )
        return true;
    else
        return false;
}

void addEdge()
{
    int n = words.size();
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
        {
            if (checkWords(words[i], words[j]))
                edge[i].push_back(j);
            if (checkWords(words[j], words[i]))
                edge[j].push_back(i);
        }
}

// Error
int countCung()
{
    int d = 0;
    int n = words.size();
    for (int i = 0; i < n; i++)
    {
        d += edge[i].size();
    }
    return d;
}

/* Tim thanh phan lien thong manh
    - Chay DFS tren do thi nguoc G2 cua G: dinh nao ko con ghe tham nua se nhet vao stack (top stack la dinh co post lon nhat)
    - Chay thuat toan tim thanh phan lien thong cho G2 (tuong tu nhu do thi vo huong), xu ly cac dinh theo
    thu tu giam dan theo so post cua moi dinh.
*/

// Tao do thi nguoc G2 cua G

void convertG()
{
    for (int i = 0; i < words.size(); i++)
    {
        for (int j = 0; j < edge[i].size(); j++)
            G2[edge[i][j]].push_back(i);
    }
}


// DFS + moi dinh sau khi duyet xong (moi hang xom sau no da duoc visited) se day vao ngan xep.
void exploreG2(int u, vector <bool> &visited, stack <int> &Stack)
{
    visited[u] = true;
    for (int i = 0; i < G2[u].size(); i++)
    {
        if (visited[G2[u][i] == false])
        {
            exploreG2(G2[u][i], visited, Stack);
        }
    }

    // All vertices reaches from v are processed by now, push v
    Stack.push(u);
}

// Duyet DFS tren do thi nguoc, luu cac dinh da duyet xong vao stack
void fillOrder(stack <int> &Stack)
{
    int n = words.size();
    vector <bool> visited(n, false);

    //Tao do thi nguoc G2
    convertG();

    // Duyet DFS tren G2
    for (int u = 0; u < n; u++)
    {
        if (visited[u] == false)
        {
            exploreG2(u, visited, Stack);
        }
    }
}


// DFS tren do thi ban dau, bat dau tu dinh co post lon nhat

void exploreG(int u, vector <bool> &visited)
{
    visited[u] = true;
    for (int i = 0; i < edge[u].size(); i++)
    {
        if (visited[edge[u][i] == false])
        {
            exploreG(edge[u][i], visited);
        }
    }

}

int countLT()
{
    int n = words.size();
    vector <bool> visited(n, false);
    int LT = 0;
    int u;
    stack <int> Stack;

    fillOrder(Stack);
    while(!Stack.empty())
    {
        u = Stack.top();
        if (visited[u] == true)
        {
            Stack.pop();
            continue;       //Lay dinh tiep theo cua stack
        }
        else if (visited[u] == false)
        {
            LT++;
            exploreG(u, visited);
        }
    }

    return LT;
}

int main()
{
    string filePath = "sgb-words2.txt";
    readFile(filePath);

    addEdge();
    cout << words.size() <<endl;
    cout << countCung() <<endl;

    //cout << countLT();
    stack <int> Stack;
    fillOrder(Stack);

    return 0;
}
