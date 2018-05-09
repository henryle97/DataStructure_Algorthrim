#include <iostream>

using namespace std;

//Cau truc cua node
struct AVLNode{
    int key;
    int bal;    //thuoc tinh cho biet gia tri can bang
                //0: can bang; 1: lech trai; 2: lech phai
    struct AVLNode *pLeft;
    struct AVLNode *pRight;
};
typedef struct AVLNode AVLNode;

/* Thao tac cai dat : xoay trai cay (RotateLeft), xoay phai cay (RotateRight)
, them node moi (InsertNode), duyet cay (Traverse), xoa toan bo node (RemoveAll)*/

//Tao node
AVLNode* CreateNode(int data)
{
    AVLNode *pNode = new AVLNode;   //Cap phat dong tao 1 node moi
    if (pNode == NULL)
    {
        cout << "Out of memory!";
        return NULL;
    }
    pNode->key = data;
    pNode->pLeft = NULL;
    pNode->pRight = NULL;
    pNode->bal = 0;         //Node moi ban dau can bang
    return pNode;
}

//Quay trai
void LeftRotate(AVLNode* &P)
{
    AVLNode *Q;
    Q = P->pRight;          // Q lam con phai cua P
    P->pRight = Q->pLeft;   //gan con trai cua Q lam con phai cua P
    Q->pLeft = P;           //gan P lam con trai cua Q
    P = Q;                  //root moi la Q
}

//Quay phai
void RightRotate(AVLNode* &P)
{
    AVLNode *Q;
    Q = P->pLeft;
    P->pLeft = Q->pRight;
    Q->pRight = P;
    P = Q;
}

// Ham xu ly can bang cay lech trai
void LeftBalance(AVLNode* &P)
{
    switch(P->pLeft->bal)
    {
    case 1: //mat can bang trai trai
        RightRotate(P);
        P->bal = 0;
        P->pRight->bal = 0;
        break;
    case 2: // mat can bang TRAI-PHAI
        LeftBalance(P->pLeft);      //Quay trai con trai node mat can bang
        RightRotate(P);             //Quay phai node mat can bang
        switch(P->bal) {
        case 0:
            P->pLeft->bal = 0;
            P->pRight->bal = 0;
            break;
        case 1:
            P->pLeft->bal = 0;
            P->pRight->bal = 2;
            break;
        case 2:
            P->pLeft->bal = 1;
            P->pRight->bal = 0;
            break;
        }
        P->bal = 0;     //Cay da can bang
        break;
    }
}

// Can bang PHAI node bi mat can bang
void RightBalance(AVLNode* &P)
{
    switch(P->pRight->bal) {
    case 1:                     //mat can bang PHAI - TRAI
        RightRotate(P->pRight); //quay phai con phai node mat can bang
        LeftRotate(P);          // quay trai node mat can bang
        //Update trang thai can bang
        switch (P->bal) {
        case 0:
            P->pLeft->bal = 0;
            P->pRight->bal = 0;
            break;
        case 1:
            P->pLeft->bal = 1;
            P->pRight->bal = 0;
            break;
        case 2:
            P->pLeft->bal = 0;
            P->pRight->bal = 2;
            break;
        }
        P->bal = 0;
        break;
    case 2:                     // Mat can bang phai phai
        LeftRotate(P);
        P->bal = 0;
        P->pLeft->bal = 0;
        break;
    }

}


//Them NODE
/* Thêm một phần tử vào cây AVL diễn ra tương tự như trên CNPTK.
Tuy nhiên, sau khi thêm xong, nếu chiều cao của cây thay đổi, từ vị trí thêm vào, ta phải lần ngược lên gốc để kiểm tra
xem có nút nào bị mất cân bằng không. Nếu có, ta phải cân bằng lại ở nút này. Việc cân bằng lại chỉ cần thực hiện 1 lần
 tại nơi mất cân bằng.*/
int InsertNode(AVLNode* &tree, int x)
{
    int res;                // Bien kiem tra ket qua them node
    if (tree == NULL)   //neu cay rong
    {
        tree = CreateNode(x);       //Gan node moi cho tree
        if (tree == NULL)
            return -1;              //-1 : Them node ko thanh cong vi thieu bo nho
        return 2;                   //2 : Them thanh cong va lam tang chieu cao cua cay
    }
    else
    {
        if (tree->key == x)
        {
            cout << "Khoa nay da ton tai"<<endl;
            return 0;               //0: Khoa nay da ton tai
        }

        else if (tree->key > x)
        {
            res = InsertNode(tree->pLeft, x);
            if (res < 2)
                return res;
            //Neu them thanh cong
            switch (tree->bal)      //Kiem tra trang thai can bang cua tree sau khi them thanh cong
            {
            case 0:
                tree->bal = 1;
                return 2;
            case 1:                 //Neu mat can bang trai
                LeftBalance(tree);
                return 1;
            case 2:
                tree->bal = 0;
                return 1;
            }
        }
        else {          //x > tree->key
            res = InsertNode(tree->pRight, x);
            if (res < 2)
                return res;

            //Neu them thanh cong thi update trang thai can bang cho tree
            switch (tree->bal)
            {
            case 0:         //Neu can bang-> update lech phai
                tree->bal = 2;
                return 2;
            case 1:         //Neu lech trai -> update can bang
                tree->bal = 0;
                return 1;
            case 2:         //Neu lech phai && + node ben phai -> can bang phai
                RightBalance(tree);
                return 1;
            }
        }
    }
}

//Duyet cay theo thu tu giua (Check su can bang cua cac node)
void Traverse(AVLNode* pNode)
{
    if (pNode != NULL)
    {
        Traverse(pNode->pLeft);
        cout << "Khoa "<< pNode->key <<" can bang "<< pNode->bal<<endl;
        Traverse(pNode->pRight);
    }
}

//DELETE ALL NODE
void RemoveAll(AVLNode* &pNode)
{
    if (pNode != NULL)
    {
        RemoveAll(pNode->pLeft);
        RemoveAll(pNode->pRight);
        delete pNode;
    }
}

//Check key x co trong AVL ko ?
bool CheckInAVL(AVLNode *tree, int x)
{
    if (tree != NULL)
    {
        if (x < tree->key)
            CheckInAVL(tree->pLeft, x);
        else if (x > tree->key)
            CheckInAVL(tree->pRight, x);
        else        //x = tree->key
            return true;
    }
    else
        return false;
}
int main()
{
    AVLNode *tree = NULL;
    int data;
    do {
        cout << "Nhap du lieu, -1 de ket thuc: ";
        cin >> data;
        if (data == -1)
            break;
        InsertNode(tree, data);
    } while (data != -1);
    cout << "Cay AVL vua tao thanh cong!"<<endl;

    Traverse(tree);
    int x;
    cout << "Nhap key x can kiem tra: ";
    cin >> x;
    bool result = CheckInAVL(tree, x);
    if (result == true)
        cout << "Tim thay";
    else
        cout << "Khong tim thay";
    RemoveAll(tree);
    return 0;
}
