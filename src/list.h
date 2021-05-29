#ifndef _list_h_
#define _list_h_

#include <stdlib.h>
#include <stdio.h>

struct ListNode;
typedef struct ListNode
{	
	struct ListNode *prev;
	struct ListNode *next;
	void *value;
} ListNode;

typedef struct List 
{	
	int count;
	ListNode *first;
	ListNode *last;
} List;

//memory allocation for the list structure
List *list_create();
void list_print(List *list);

//fills the list with random n integers smaller than 100
void list_populate(List *list, int *arr, int n);

//clears all data and frees allocated memory
void list_clear_destroy(List *list);

//adds value node at the end of the list
void list_push(List *list, void *value);

//removes last node of the list
void *list_pop(List *list);

//adds value at the start of the list
void list_unshift(List *list, void *value);

//removes first node of the list
void *list_shift(List *list);

//removes any given node from the list
//function is also used by pop and shift
void *list_remove(List *list, ListNode *node);

//copies a given list to another list
//NOTE: list to copy to cannot be NULL
void list_copy(List *from, List *to);


void list_join(List *total, List *firstl, List *second);
void list_split(List *list, ListNode *node);

#define list_count(A) ((A)->count)
#define list_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define list_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

#define LIST_FOREACH(L, S, M, V) \
	ListNode *_node = NULL; \
	ListNode *V = NULL; \
	for (V = _node = L->S; _node != NULL; V = _node = _node->M)
	

#endif

