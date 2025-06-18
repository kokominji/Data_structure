#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
    int item;
    struct _listnode *next;
} ListNode;
typedef struct _linkedlist {
    int size;
    ListNode *head;
} LinkedList;


void appendNode(LinkedList *ll, int item) {
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->item = item;
    newNode->next = NULL;

    if (ll->head == NULL) {
        ll->head = newNode;
    } else {
        ListNode *cur = ll->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }

    ll->size++;
}
