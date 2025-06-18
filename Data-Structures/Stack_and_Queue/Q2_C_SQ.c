//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000
//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList

typedef struct _stack
{
	LinkedList ll;
}Stack;  // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createStackFromLinkedList(LinkedList *ll , Stack *stack);
void removeEvenValues(Stack *s);

void push(Stack *s , int item);
int pop(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Stack s;

	c = 1;
	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the stack from the linked list:\n");
	printf("3: Remove even numbers from the stack:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createStackFromLinkedList(&ll, &s); // You need to code this function
			printf("The resulting stack is: ");
			printList(&(s.ll));
			break;
		case 3:
			removeEvenValues(&s); // You need to code this function
			printf("The resulting stack after removing even integers is: ");
			printList(&(s.ll));
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void createStackFromLinkedList(LinkedList *ll, Stack *s)
{
	if(ll == NULL || s == NULL) return;

	removeAllItemsFromStack(s);
	
	ListNode *cur = ll -> head;

    while (cur != NULL) {
        push(s, cur->item);  // 맨 앞에 삽입되므로 스택에는 역순 저장됨
        cur = cur->next;
    }
}

	// Stack tempStack;
	// tempStack.ll.head = NULL;
	// tempStack.ll.size = 0;

	//스택은LIFO 마지막에 들어간게 먼저 나옴
	//ll과 s가 비어있는지 확인하고 비어있다면 return
	//스택초기화
	//앞에서부터 push하기


void removeEvenValues(Stack *s)
{

	if (s == NULL) return;

	Stack temp;
	temp.ll.head = NULL;
	temp.ll.size =0;

	while (!isEmptyStack(s)){
		int val = pop(s);
		if (val % 2 != 0){
			push(&temp, val);
		}
	}
	while (!isEmptyStack(&temp)){
		int val = pop(&temp);
		push(s, val);
	}
	// if (s == NULL)
    //     return;

    // Stack temp;
    // temp.ll.head = NULL;
    // temp.ll.size = 0;

    // // 홀수만 임시 스택에 저장
    // while (!isEmptyStack(s)) {
    //     int val = pop(s);
    //     if (val % 2 != 0) { // 홀수이면 temp에 push
    //         push(&temp, val);
    //     }
    // }

    // // temp에서 다시 원래 스택으로 push → 순서 복원
    // while (!isEmptyStack(&temp)) {
    //     int val = pop(&temp);
    //     push(s, val);
    // }
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer

	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL) exit(0);
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links

	if ((pre = findNode(ll,index -1)) != NULL){
		cur = pre -> next;
		pre->next = malloc(sizeof(ListNode)); //새 노드를 만듦
		if (pre->next == NULL) exit(0);
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}
	// if ((pre = findNode(ll, index - 1)) != NULL){
	// 	cur = pre->next;
	// 	pre->next = malloc(sizeof(ListNode));
	// 	if (pre->next == NULL) exit(0);
	// 	pre->next->item = value;
	// 	pre->next->next = cur;
	// 	ll->size++;
	// 	return 0;
	// }

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer

	if (index == 0) {
		cur = ll->head->next;
		free(ll->head);
		ll->head=cur;
		ll->size--;
		return 0;
	}
	// if (index == 0){
	// 	cur = ll->head->next;
	// 	free(ll->head);
	// 	ll->head = cur;
	// 	ll->size--;
	// 	return 0;
	// }

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links

	if ((pre = findNode(11, index -1)) != NULL) {
		if (pre->next == NULL) return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}
	// if ((pre = findNode(ll, index - 1)) != NULL){

	// 	if (pre->next == NULL)
	// 		return -1;

	// 	cur = pre->next;
	// 	pre->next = cur->next;
	// 	free(cur);
	// 	ll->size--;
	// 	return 0;
	// }

	return -1;
}
