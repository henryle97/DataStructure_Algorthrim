#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

/* Set up k -d Tree */
const int k = 2;

// A structure to represent node of kd tree
typedef struct Node
{
    int point[k];       // To store k dimensional point
    Node *left, *right;
} Node;

// A method to creat a node of K-D tree
Node* newNode(int arr[])
{
    Node *temp = new Node;

    for (int i = 0; i < k; i++)
        temp->point[i] = arr[i];
    temp->left = temp->right = NULL;
    return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter deph is used to decide axis of comparison: depth at root equal 0
Node* insertRec(Node *root, int point[], unsigned int depth)
{
    // Tree is empty
    if (root == NULL)
        return newNode(point);

    // Caculate current dimension (cd) of comparison
    unsigned int cd = depth % k;

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[cd]< (root->point[cd]))
        root->left = insertRec(root->left, point, depth+1);
    else
        root->right = insertRec(root->right, point, depth+1);

    return root;
}

// Function to insert a new point with given point in KD tree
// and return new root. It mainly uses above recursive
Node *insert(Node *root, int point[])
{
    return insertRec(root, point, 0);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(int point1[], int point2[])
{
    // Compare individual pointinate values
    for (int i = 0; i < k; i++)
    {
        if (point1[i] != point2[i])
            return false;
    }
    return true;
}

// Distance between two points
float dist(int point1[], int point2[])
{
    return sqrt(pow(point1[0]-point2[0], 2)+ pow(point1[1] - point2[1], 2));
}

// Nearest Neighbour
void nearestNeighbour(Node *root, int pointA[])
{
    int minNeighbour[2] = {root->point[0], root->point[1]};
    float mindist;
    int depth = 0;
    int cd;
    float tempDist;

    mindist = dist(pointA, root->point);
    while (root != NULL)
    {
        tempDist = dist(pointA, root->point);
        if (tempDist < mindist && tempDist != 0)
        {
            mindist = tempDist;
            minNeighbour[0] = root->point[0];
            minNeighbour[1] = root->point[1];
        }

        cd = depth % 2;
        if (pointA[cd] < root->point[cd])
        {
            root = root->left;
            depth++;

        }
        else {
            root = root->right;
            depth++;
        }
    }

    cout << "Diem gan voi " << pointA[0] << "," << pointA[1] << " la " << minNeighbour[0] << "," << minNeighbour[1];
}
int main()
{
    Node *root = NULL;
    int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
                       {9, 1}, {2, 7}, {10, 19}};
    int n = sizeof(points) / sizeof(points[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, points[i]);

    int pointA[2];
    cout << "Nhap diem A(x,y)= ";
    cin >> pointA[0] >> pointA[1];

    nearestNeighbour(root, pointA);
    return 0;
}
