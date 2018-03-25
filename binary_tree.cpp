#include <iostream>
#include <queue>
#include <stack>
#include <limits.h>

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

void BreadthFirstSearch(Node *root)
{
    Node* curr = NULL;
    queue <Node *> q;

    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    cout << "Breadth First Search...\n";
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

void IterativeInOrderTraversal(Node* root)
{
    Node* curr = NULL;
    stack <Node *> s;

    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    curr = root;
    s.push(curr);
    cout << "Iterative In-order traversal...\n";
    while (!s.empty()) {
        while (curr) {
            if (curr->left) {
                s.push(curr->left);
            }
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->data << " ";
        curr = curr->right;
        if (curr) {
            s.push(curr);
        }
    }
    cout << endl;
    return;
}

bool checkSubtree (Node* root, int min, int max)
{
    bool isBST = true;
    if (!root) {
        return true;
    }

    if (root->data <= min || root->data >= max) {
        return false;
    }

    isBST = checkSubtree(root->left, min, root->data);
    if (!isBST) {
        return isBST;
    }
    isBST = checkSubtree(root->right, root->data, max);
    return isBST;

}

bool checkBST (Node* root)
{
    return checkSubtree(root, INT_MIN, INT_MAX);
}

Node* invertTree (Node *root)
{
    Node *tmp = root;
    if (root) {
        tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        invertTree(root->left);
        invertTree(root->right);
    }
    return root;
}

int main()
{
    Node* r = NULL;

    r = insert(r, 15);
    r = insert(r, 10);
    r = insert(r, 5);
    r = insert(r, 1);
    r = insert(r, 7);
    r = insert(r, 8);
    r = insert(r, 20);
    r = insert(r, 17);
    r = insert(r, 25);
    r = insert(r, 21);
    r = insert(r, 26);

    IterativeInOrderTraversal(r);
    cout << "In-order traversal...\n";
    InOrderTraversal(r);
    cout << endl;

    BreadthFirstSearch(r);

    cout << "Binary Search Tree: " << checkBST(r)  << endl;

    cout << "Binary tree after inverting the node...\n";
    r = invertTree(r);
    InOrderTraversal(r);

    return 0;
}
