#include <iostream>


using namespace std;

/* Cau truc 1 nut */
struct TreeNodeRec {
    int key;            // khoa de tim kiem
    struct TreeNodeRec *leftPtr;
    struct TreeNodeRec *rightPtr;
};
typedef struct TreeNodeRec TreeNode;

TreeNode* makeTreeNode(int value);
TreeNode* findMin(TreeNode *rootPtr);
TreeNode* findMax(TreeNode *rootPtr);
TreeNode* searchKey(TreeNode *rootPtr, int item);
TreeNode* insertNode(TreeNode *nodePtr, int item);
TreeNode* deleteNode();
void printInOrder(TreeNode *rootPtr);

//Cai dat Binary Search Tree
int main()
{
    TreeNode *rootPtr = NULL;
    int value;

    cout << "Enter value of node: ";
    cin >> value;
    insertNode(rootPtr, value);
    return 0;
}

/* Tao 1 nut moi */
TreeNode* makeTreeNode(int value)
{
    TreeNode *NewNode = new TreeNode;
    if (NewNode == NULL)
    {
        cout << "Out of memory!!!";
        return NULL;
    }
    else
    {
        NewNode->key = value;
        NewNode->leftPtr = NULL;
        NewNode->rightPtr = NULL;
    }
    return NewNode;
}

/* Chen 1 nut
- Tao nut moi chua phan tu can chen
- Di chuyen tren cay de tim cha cua nut moi. Gap NULL thi dung
- Gan nut moi nhu la con cua nut cha tim duoc. Nut moi luon la la.
+ nodePtr: con tro den nut dang xet ( ban dau la root) - con tro duyet
*/

TreeNode* insertNode(TreeNode *nodePtr, int item)
{

    if (nodePtr == NULL)
    {
        nodePtr = makeTreeNode(item);
    }
    /* Neu khoa phan tu bo sung nho hon khoa cua nut hien tai thi tiep tuc
        qua trinh voi nut hien thoi la nut con trai*/
    else if (item < nodePtr->key)
    {
        nodePtr->leftPtr = insertNode(nodePtr->leftPtr, item);
    }
    else if (item > nodePtr->key)
    {
        nodePtr->rightPtr = insertNode(nodePtr->rightPtr, item);
    }
    return nodePtr; // Tra ve con tro den node moi
}

/* Delete phan tu co key = x
 - 4 TH: Nut xoa la la, nut xoa chi co con trai (con phai), nut xoa co 2 con
*/
TreeNode* deleteNode(TreeNode *T, int x)
{
    TreeNode *Temp;
    if (T == NULL)            // Neu cay rong
        cout << "Not found!";
    else if (x < T->key)        /* di ben trai */
        T->leftPtr = deleteNode(T->leftPtr, x);
    else if (x > T->key)        /* di ben phai */
        T->rightPtr = deleteNode(T->rightPtr, x);
    else                     /* tim duoc phan tu can xoa */
    {
        /* Node xoa co 2 con -> phan tu the cho la phan tu min o cay con phai*/
        if (T->leftPtr && T->rightPtr)
        {
            Temp = findMin(T->rightPtr);
            T->key = Temp->key;
            T->rightPtr = deleteNode(T->rightPtr, T->key);  // Xoa phan tu da the cho
        }
        else    /* Co 1 con hoac ko co con */
        {
            Temp = T;
            if (T->leftPtr == NULL)         // Chi co con phai or ko con
                T = T->rightPtr;
            else if (T->rightPtr == NULL)
                T = T->leftPtr;
        }

    }
    delete Temp;
    return T;
}
