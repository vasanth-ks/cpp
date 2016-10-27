/*
 * Given a list, group odd indexed nodes first followed by even indexed nodes
 */
#include <iostream>

using namespace std;

typedef struct linkedList {
    int data;
    linkedList *next;
} linkedList_t;

class Solution
{
    private:
        linkedList *oddTail, *evenHead, *evenTail, *head, *tail;
    public:
        Solution ()
        {
            oddTail = NULL;
            evenHead = NULL;
            evenTail = NULL;
            head = NULL;
            tail = NULL;
        }
        void insert (int data);
        void  rearrangeList ();
        void display ();
};

void Solution::insert (int data)
{
    linkedList_t *node = new linkedList_t;
    linkedList_t *nav = NULL;

    if (head == NULL) {
        node->data = data;
        node->next = head;
        head = node;
        tail = head;
        return;
    }
    node->data = data;
    node->next = NULL;
    tail->next = node;
    tail = node;
    return;
}

void Solution::rearrangeList ()
{
    if (!head) {
        cout << "List is empty\n";
        return;
    }
    oddTail = head;
    evenHead = head->next;
    evenTail = evenHead;
    
    while (evenTail) {
        if (evenTail->next) {
            oddTail->next = evenTail->next;
            oddTail = evenTail->next;
            evenTail->next = oddTail->next;
            oddTail->next = evenHead;
        }
        evenTail = evenTail->next;
    }
    return;
}

void Solution::display ()
{
    linkedList_t *nav = NULL;
    if (!head) {
        cout << "List is empty\n";
        return;
    }
    nav = head;

    cout << "Contents of list\n====================\n";
    while (nav) {
        cout << nav->data << " ";
        nav = nav->next;
    }
    cout << "\n";
    return;
}

int main()
{
    Solution s;
    s.insert (1);
    /*s.insert (2);
    s.insert (3);
    s.insert (4);
    s.insert (5);
    s.insert (6);
    s.insert (7);
    s.insert (8);
    s.insert (9);*/
    s.display();
    s.rearrangeList();
    s.display();
    return 0;
}
