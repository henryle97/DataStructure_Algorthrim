#include <iostream>

using namespace std;


// A BTree node
class BTreeNode
{
    int *keys;                  // An array of keys
    int t;                      // Minimum degree (defines the range for number of keys)
    BTreeNode **C;              // An array of child pointers
    int n;                      // Current number of keys
    bool leaf;                  // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf);      // Constructor

    // Chen 1 khoa moi trong cay con bat nguon tu khoa nay
    void insertNonFull(int k);

    // Chia con y cua node nay. i la index cua y trong mang con C[]
    // Con y phai full khi ham nay duoc goi
    void splitChild(int i, BTreeNode *y);
    // A function to traverse all nodes in a subtree rooted with the node
    void traverse();

    // A function to search a key in subtree rooted with the node
    BTreeNode *search(int k);           // Return NULL if k is not present.

// Make BTree friend of this so that we can access private member of this class in BTree functions
friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root;            // Pointer to root node
    int t;                      // Minimum degree
public:
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    // function to travese the tree
    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    // function to search a key in this tree
    BTreeNode *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int k);
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int _t, bool _leaf)
{
    // Copy the given minimum degree and leaf property
    t = _t;
    leaf = _leaf;

    // Allocate memory for maximum number of possible keys and child pointers
    keys = new int[2*t - 1];
    C = new BTreeNode *[2*t];

    // Initialize the number of key as 0
    n = 0;

}

// Function to traverse all nodes in a subtree rooted with the node
void BTreeNode::traverse()
{
    int i;
    // There are n keys and n+1 children, traverse through n keys and first n children
    for (i = 0; i < n; i++)
    {
        // If this is not leaf. then before printing key[i],
        // traverse the subtree rooted with child C[i]
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k)
{
    //Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;

    // Go to the appropriate child
    return C[i]->search(k);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
    // If tree is empty
    if (root = NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k;      //insert key
        root->n = 1;            // Update number of keys in root
    }
    else                // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2*t-1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now. Decide which of two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        }
        else            // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = n-1;

    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Find the location of new key to be inserted
        // b) Moves all greater key to one place ahead
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i+1] = k;
        n = n+1;
    }
    else        // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full
        if (C[i+1]->n == 2*t-1)
        {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);

            // After split , the middle key of C[i] goes up and
            // C[i] is splitted into two. See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }

}
int main()
{

    return 0;
}
