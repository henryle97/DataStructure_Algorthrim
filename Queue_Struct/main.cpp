#include <iostream>

using namespace std;

//A linked list node to store a queue entry
struct QNode
{
    int data;
    QNode *pNext;
};
//The queue, front stores the front node of LL and rear stores the last node of LL
struct Queue
{
    QNode *Front, *Rear;
};

//A utility function to create a new linked list node
QNode *CreatNode(int value)
{
    QNode *newNode = new QNode;
    newNode->data = value;
    newNode->pNext = NULL;
    return newNode;
}

//A utility function to create an empty queue q

Queue *CreatQueue()
{
    Queue *q = new Queue;
    q->Front = q->Rear = NULL;
    return q;       //Return pointer Queue
}

//The function to add a value to queue (have name is q)
// EnQueue into Rear
// O day q ko thay doi , chi q->front and q->rear thay doi
void enQueue(Queue *q, int value)
{
    QNode *newNode = CreatNode(value);

    //If queue is empty, then new node is front and rear both
    if (q->Rear == NULL)
    {
        q->Front = q->Rear = newNode;
        return;
    }

    //Add the new node at the end of the queue and change rear
    q->Rear->pNext = newNode;
    q->Rear = newNode;

}

//The function to remove a key from given queue q
// Dequeue at FRONT
QNode* deQueue(Queue *q)
{
    // If the queue is empty, return NULL
    if (q->Front == NULL)
        return NULL;

    // Store previous front and move one node ahead
    QNode *temp = q->Front;
    q->Front = q->Front->pNext;

    //If front becomes NULL, then change rear also as NULL
    if (q->Front == NULL)
        q->Rear = NULL;
    return temp;        // Return the deleted pointer
}

int isEmpty(Queue *q)
{
    // Ko the xay ra truong hop 1 trong 2 front or rear bang NULL
    if (q->Front == NULL && q->Rear == NULL)
        return 1;
    else
        return 0;
}
void PrintQueue(Queue *q)
{
    QNode *temp = q->Front;
    if (isEmpty(q))
    {
        cout << "Queue is empty." <<endl;
        return;
    }
    else
        do {
            cout << temp->data << " ";
            temp = temp->pNext;
        } while (temp != NULL);
}
int SizeOfQueue(Queue *q)
{
    int count = 1;
    QNode *temp = q->Front;
    while (temp != q->Rear)
    {
        count++;
        temp = temp->pNext;
    }
    return count;
}
int main()
{
    Queue *q = new Queue;           //Create a queue
    enQueue(q,4);
    enQueue(q,7);
    enQueue(q, 5);
    deQueue(q);
    enQueue(q, 3);
    deQueue(q);
    deQueue(q);
    enQueue(q,9);
    PrintQueue(q);
    return 0;
}
