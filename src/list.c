#include "debug.h"
#include "list.h"

List *list_create()
{
	return calloc(1, sizeof(List)); 
}

void list_destroy(List *list)
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

void list_clear(List *list)
{
	LIST_FOREACH(list, first, next, cur)
	{
		free(cur->value);
	}
}

void list_clear_destroy(List *list)
{
	list_clear(list);
	list_destroy(list);
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
		node->next = list->first;
		list->first->prev = node;
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


	
