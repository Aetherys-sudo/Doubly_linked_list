#include "debug.h"
#include "list.h"

List *list_create()
{
	return calloc(1, sizeof(List));
}

void list_populate(List *list, int *arr, int n)
{
	int i = 0;
	
	for (i = 0; i < n; i ++)
	{
		arr[i] = rand() % 100;
		list_push(list, &arr[i]);
	}
}

void list_print(List* list)
{
	check(list != NULL, "List to be printed cannot be NULL.");
	printf("Printed list: ");
	LIST_FOREACH(list, first, next, cur)
	{
		printf("%d ", (*(int *) cur->value));
	}
	printf("\n");
error:
	return;
}

void list_clear_destroy(List *list)
{
	LIST_FOREACH(list, first, next, cur)
	{	
		if (cur->prev)
		{
			free(cur->prev);
		}
	}
	
	free(list->last);
	free(list);
	
}

void list_push(List *list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if (list->last == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	
	list->count ++;
	
error:
	return;
}

void *list_pop(List *list)
{
	ListNode *node = list->last;
	return node != NULL ? list_remove(list, node) : NULL;
}

void list_unshift(List *list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->first->prev = node;
		node->next = list->first;
		list->first = node;
	}
	
	list->count ++;

error:
	return;
}

void *list_shift(List *list)
{
	ListNode *node = list->first;
	return node != NULL ? list_remove(list, node) : NULL;
}

void *list_remove(List *list, ListNode *node)
{
	void *result = NULL;
	
	check(list->first && list->last, "List is empty.");
	check(node, "Node can't be NULL.");
	
	if (node == list->first && node == list->last)
	{
		list->first = NULL;
		list->last = NULL;
	}
	else if (node == list->first)
	{
		list->first = node->next;
		check(list->first != NULL, "List first item is NULL.");
		list->first->prev = NULL;
	} 
	else if (node == list->last)
	{
		list->last = node->prev;
		check(list->last != NULL, "List last item is NULL.");
		list->last->next = NULL;
	}
	else
	{
		ListNode *before = node->prev;
		ListNode *after = node->next;
		after->prev = before;
		before->next = after;
	}
		
	list->count --;
	result = node->value;
	free(node);
	
error:
	return result;
}

void list_copy(List *from, List *to)
{
	check(from != NULL, "List to copy from cannot be NULL.");
	check(to != NULL, "List to copy to cannot be NULL.");
	int i = 0;
	
	LIST_FOREACH(from, first, next, cur)
	{
		i ++;
		list_push(to, cur->value);
		if (i > list_count(from))
		{
			printf("Maximum copy size reached.\n");
			break;
		}
	}	

error:
	return;
	
}

void list_join(List *total, List *firstl, List *second)
{
	check(total != NULL, "List to be merged into cannot be NULL.");
	check(firstl != NULL, "First list to be merged cannot be NULL.");
	check(second != NULL, "Second list to be merged cannot be NULL.");
	
	total->first = total->last = NULL;
	LIST_FOREACH(firstl, first, next, cur)
	{
		list_push(total, cur->value);
	}
	
	ListNode *node = NULL;
	ListNode *cur1 = NULL;
	for (cur1 = node = second->first; cur1 != NULL; cur1 = node = node->next)
	{
		list_push(total, cur1->value);
	}
	
error:
	return;
}

void list_split(List *list, ListNode *node)
{
	
