#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct linked_list_
{
    int popularity;
    struct linked_list_ *next;
    struct linked_list_ *prev;
}linked_list_;

typedef struct linked_list_ linked_list_t;

linked_list_t *tail = NULL;

linked_list_t* insert (linked_list_t *head, int p)
{
    linked_list_t* newNode = NULL, *nav = NULL;
    if (!head) {
        head = (linked_list_t*)malloc(sizeof(linked_list_t));
        head->popularity = p;
        head->next = NULL;
        head->prev = NULL;
        tail = head;
        return head;
    }
    nav = head;

    newNode = (linked_list_t*)malloc(sizeof(linked_list_t));
    newNode->popularity = p;
    newNode->next = NULL;
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;

    return head;
}

void display(linked_list_t* head)
{
    linked_list_t* nav = NULL;
    unsigned int count = 0;

    if (!head) {
        printf("Empty list to display\n");
        return;
    }
    for (nav = head; nav; nav = nav->next) {
        printf("%d ", nav->popularity);
        if (nav->prev) {
            free(nav->prev);
        }
        count++;
    }
    printf("\n");
    return;
}

linked_list_t* delete_friends(linked_list_t* head, unsigned int k)
{
    linked_list_t* node = NULL, *prev = NULL;
    bool delete_friend = false;
    unsigned int n_del = 0;

    if (!head) {
        printf("No friends in the list\n");
        return head;
    }
    node = head;

    while (n_del < k) {
        while (node && node->next) {
            if (node->popularity < node->next->popularity) {
                if (node == head) {
                    head = node->next;
                    head->prev = NULL;
                    free(node);
                    node = head;
                } else {
                   node->prev->next = node->next;
                   prev = node->next->prev = node->prev;
                   free(node);
                   node = prev;
                }
                delete_friend = true;
                n_del++;
                break;
            } else {
                node = node->next;
            }
        }
        if (!delete_friend) {
            if (tail) {
                prev = tail->prev;
                prev->next = tail->next;
                free(tail);
                tail = prev;
                node = head;
                n_del++;
            }
        }
        delete_friend = false;
    }
    return head;
}

int main()
{
    int n_tests = 0, n_removals = 0, n_friends = 0, i = 0, j = 0, popularity = 0;
    linked_list_t* head = NULL;
    scanf("%d", &n_tests);

    for (i = 0; i < n_tests; ++i) {
        scanf("%d %d", &n_friends, &n_removals);
        for (j = 0; j < n_friends; ++j) {
            scanf("%d", &popularity);
            head = insert(head, popularity);
        }
        head = delete_friends(head, n_removals);
        display(head);
        head = NULL;
    }
    return 0;
}
