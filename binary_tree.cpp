#include <iostream>
#include <queue>

using namespace std;

typedef struct Node {
    Node *left, *right;
    int data;
} node;

Node* insert(Node *root, int value)
{
    Node* curr = NULL, *prev = NULL, *newNode = NULL;
    if (!root) {
        root = new Node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
    } else {
        newNode = new Node;
        curr = root;
        prev = root;
        while (curr) {
            if (curr->data < value) {
                prev = curr;
                curr = curr->right;
            } else {
                prev = curr;
                curr = curr->left;
            }
        }
        if (prev->data < value) {
            prev->right = newNode;
        } else {
            prev->left = newNode;
        }
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return root;
}
void DepthFirstSearch(Node *root) 
{
    Node* curr = NULL;
    queue <Node *> q;

    if (!root) {
        return;
    }
    cout << "Depth First Search...\n";
    q.push(root);
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        if (curr) {
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
            cout << curr->data << " ";
        }
    }
    cout << endl;
    return;
}

void InOrderTraversal(Node* root)
{
    Node *curr = NULL;
    if (!root) {
        return;
    }
    curr = root;
    
    InOrderTraversal(curr->left);
    cout << curr->data << " ";
    InOrderTraversal(curr->right);
    return;
}

int main()
{
    Node* r = NULL;

    r = insert(r, 33);
    r = insert(r, 21);
    r = insert(r, 35);
    r = insert(r, 20);
    r = insert(r, 25);
    r = insert(r, 34);
    r = insert(r, 55);
    
    cout << "In-order traversal...\n";
    InOrderTraversal(r);
    cout << endl;
    DepthFirstSearch(r);
    return 0;
}
