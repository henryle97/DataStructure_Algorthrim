#include <stdio.h>
#include <stdlib.h>


//Node
typedef struct LNode
{
    int data;
    struct LNode *next;

} LNode;

//Add a node at front of the list
LNode *insertHead(LNode *First, int newdata)
{
    LNode *TempNode = (LNode*) malloc(sizeof(LNode)); //Tao 1 con tro nut
    TempNode->data = newdata;
    TempNode->next = First;
    First = TempNode;
    return First;
}

//Add midle : tai vi tri sau node duoc tro boi con tro Pred
LNode *insertMidle(LNode *Pred, int newdata)
{
    LNode *NewNode = (LNode *) malloc(sizeof(LNode));

    NewNode->data = newdata;
    NewNode->next = Pred->next;
    Pred->next = NewNode;
    return NewNode;                  //dia chi cua nut moi

}

//Add a node at the end
//Neu dung thuong xuyen thi bo sung them LNode *Last
//LNode *inserLast(){...return Last}
LNode *insertLast(LNode *First, int newdata)
{
    //Can 2 *Node : 1 *Node de duyet tu dau den cuoi, 1 *Node de luu data
    LNode *NewNode = (LNode *) malloc(sizeof(LNode));                 //Node moi
    LNode *lastNode;                //dung de duyet tu First den Last

    //Nap du lieu
    NewNode->data = newdata;
    NewNode->next = NULL;
    // lastNode  nhan dia chi cua node dau tien
    lastNode = First;
    //Neu danh sach rong
    if(First == NULL)
    {
        First = NewNode;
        return First;
    }
    //Chay den node cuoi cung thi dung
    while (lastNode->next != NULL)
    {
        lastNode = lastNode->next;
    }
    lastNode->next = NewNode;

    return First;
}

//Delete head list
void deleteHead(LNode **First)
{
    LNode *temp = (LNode *) malloc(sizeof(LNode));
    temp = *First;
    *First = temp->next;
    free(temp);
}
//Kiem tra danh sach rong
int isEmpty(LNode *First)
{
    return !First; //Neu First=NULL thi return 1.
}
//Dua ra tat ca cac phan tu
void printList(LNode *node)
{
    int count = 0;
    while (node != NULL)
    {
        printf("%d ",node->data);
        node = node->next;
        count++;
        if (count % 11 == 0)
            printf("\n");
    }

}

void printReverse(LNode *node)
{
    if (node == NULL)
        return;
    else {
        printReverse(node->next);
        printf("%d ", node->data);
    }
}
int main()
{
//Tao ngau nhien 1 danh sach voi cac phan tu la so nguyen
    LNode *head = NULL;        //Con tro luu dia chi cua nut dau tien trong danh sach
    int n;                      //so luong phan tu
    int i,a;                    //index
    printf("Nhap so luong phan tu: "); scanf("%d", &n);
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        a = rand()%100;                                   //0-99
        head = insertHead(head, a);
    }
    printf("Linked List: ");
    printList(head);
    printf("\n");

    printf("Linkded List in the reverse order: ");
    printReverse(head);

    free(head);
    return 0;
}
