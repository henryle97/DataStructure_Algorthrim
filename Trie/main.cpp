#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;

const int MAX = 26;

struct TrieNode {
    TrieNode *children[MAX];  // mang con tro chua 26 ky tu
    bool isEnd;                     //true neu la leaf
};

TrieNode *CreateNode(void);
void insertTrie(TrieNode *head, string key);
int printAutoGoiY(TrieNode *head, const string query);
void goiy(TrieNode *head, string iPrefix);
int isLastNode(TrieNode *pNode);

int main()
{
    TrieNode *root = CreateNode();

    //Doc file va insert vao tree
    fstream file;
    file.open("dictionary.txt");   //Tao 1 doi tuong file
    if (!file)
    {
        cout << "Failed to open file!";
        return -1;
    }
    string inputWord;
    while (!file.eof())         //Trong khi chua ket thuc file
    {
            //char temp[255];
            //file.getline(temp, 255);
            //inputWord = temp;        //Giam bo nho du thua
            getline(file, inputWord);
            insertTrie(root, inputWord);
    }
    file.close();

    //Nhap tu goi y
    string input;
    cout << "Nhap tu: ";
    cin >> input;
    //Chuyen chu hoa thanh chu thuong
    string prefix;
    for (int i = 0; i < input.size(); i++)
    {
        prefix.push_back(tolower(input[i]));
    }


    //In ra cac tu goi y
    int result = printAutoGoiY(root, prefix);
    if (result == 0)
        cout << "Khong tim thay tu nay trong tu dien ";
    else if (result == -1 )
        cout << "Khong tim thay tu khac";

    return 0;
}

//Tao node voi cac con la NULL
TrieNode *CreateNode(void)
{
    TrieNode *pNode = new TrieNode;
    pNode->isEnd = false;
    for (int i = 0; i < MAX; i++)
    {
        pNode->children[i] = NULL;
    }
    return pNode;
}

// Chen tu vao cay
/* Duyet tung ky tu cua tu can add,
, neu ky tu do chua co trong cay thi them vao
, node cua ky tu cuoi cung co isEnd = true */
void insertTrie(TrieNode *head, const string key)
{
    TrieNode *pDuyet = head;

    for (int i = 0; i < key.length(); i++)           //Duyet tung ky tu cua key
    {
        int id = (int)(key[i] - 'a');
        if (pDuyet->children[id] == NULL)                    //Neu con dang NULL thi them vao
            pDuyet->children[id] = CreateNode();

        pDuyet = pDuyet->children[id];
    }

    //Danh dau node cuoi cung la end cua 1 tu
    pDuyet->isEnd = true;
}

//Kiem tra da duyet het chua
// return 0 neu node hien tai van dang co con
// return 1 neu all con deu NULL
int isLastNode(TrieNode *pNode)
{
    for (int i = 0; i < MAX; i++)
    {
        if (pNode->children[i] != NULL)
            return 0;
    }
    return 1;                       //La node cuoi cung cua cay
}


//Ham Check va in ra cac tu goi y
int printAutoGoiY(TrieNode *head, const string query)
{
    TrieNode *pDuyet = head;

    //Kiem tra query (duyet den ky tu cuoi cung = pDuyet)
    int n = query.length();
    for (int i = 0; i < n; i++)
    {
        int id = (int)(query[i] - 'a');

        if (pDuyet->children[id] == NULL)   //Neu ko co string nay trong Trie
            return 0;

        pDuyet = pDuyet->children[id];
    }

    bool isWord = (pDuyet->isEnd == true);
    bool isLast = isLastNode(pDuyet);

    //Neu query la 1 tu va k co tu nao bat dau boi query nua thi in ra va thoat ham
    if (isWord && isLast)
    {
        cout << query <<endl;
        return -1;
    }

    if (!isLast)
    {
        string prefix = query;
        //pDuyet hien tai dang tro den ky tu cuoi cung cua query
        goiy(pDuyet, prefix);
        return 1;
    }
}


void goiy(TrieNode *head, string currPrefix)
{

    if (head->isEnd == true)             //Ket thuc 1 tu( buoc co so)
    {   cout << currPrefix ;
        cout <<endl;
    }

    // Neu tat ca con deu NULL
    if (isLastNode(head))
        return;

    for (int i = 0; i < MAX; i++)
    {
        if (head->children[i] != NULL)
        {
            currPrefix.push_back(97 + i);
            goiy(head->children[i],currPrefix);
            currPrefix.pop_back();
        }
    }
    return;
}
