#include <assert.h>
#include "minunit.h"
#include "../src/list.h"

List *list = NULL;

char *test_create()
{
	list = list_create();
	mu_assert(list != NULL, "List could not be created.");
	
	return NULL;
	
}

char *test_clear_destroy()
{
	list_clear_destroy(list);
	
	return NULL;
}

char *test_push_pop()
{	
	int i = 0;
	int *arr = calloc(1, 9 * sizeof(int));
	
	for (i = 0; i < 9; i ++)
	{
		arr[i] = rand() % 100;
		list_push(list, &arr[i]);
	}
	
	
	mu_assert(list_count(list) == 9, "Wrong list count value on push.");
	
	int *val = NULL;
	for (i = 8; i >= 0; i --)
	{
		val = list_pop(list);
		mu_assert(*val == arr[i], "Wrong value on pop.");
	}
	mu_assert(list_count(list) == 0, "Wrong list count value on pop.");
	
	free(arr);
	return NULL;
}

char *test_print()
{
	list_print(list);
	
	return NULL;
}

char *test_unshift_shift()
{
	int i = 0;
	int *arr = calloc(1, 9 * sizeof(int));
	
	for (i = 0; i < 9; i ++)
	{
		arr[i] = rand() % 100;
		list_unshift(list, &arr[i]);
	}
	
	mu_assert(list_count(list) == 9, "Wrong list count value on unshift.");
	
	int *val = NULL;
	for (i = 8; i >= 0; i --)
	{
		val = list_shift(list);
		mu_assert(*val == arr[i], "Wrong value on shift.");
	}
	mu_assert(list_count(list) == 0, "Wrong list count value on pop.");
	
	free(arr);

	return NULL;
}

char *test_copy()
{
	List *from = list_create();
	List *to = list_create();
	int i = 0;
	int *arr = calloc(1, 9 * sizeof(int));
	
	for (i = 0; i < 9; i ++)
	{
		arr[i] = rand() % 100;
		list_push(from, &arr[i]);
	}
	
	list_copy(from, to);
	mu_assert(list_count(from) = list_count(to), "Wrong size after copy.");
	ListNode *node = to->first;
	
	LIST_FOREACH(to, first, next, cur)
	{
		if (node != NULL)
		{
			mu_assert(node->value == cur->value, "Wrong values after copy.");
			node = node->next;
		}
	}
	
	list_clear_destroy(from);
	list_clear_destroy(to);
	free(arr);
	
	return NULL;
	
}

char *test_remove()
{
	int i = 0;
	int size = 4;
	int *arr = calloc(1, 4 * sizeof(int));
	for (i = 0; i < 4; i ++)
	{
		arr[i] = rand() % 100;
		list_push(list, &arr[i]);
	}
	
	int *value = list_remove(list, list->first->next);
	
	mu_assert(list_count(list) == size - 1, "Wrong size after remove.");
	mu_assert(*value == arr[1], "Wrong returned value after remove.");
	
	free(arr);
	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift_shift);
	mu_run_test(test_print);
	mu_run_test(test_remove);
	mu_run_test(test_copy);
	mu_run_test(test_clear_destroy);
	
	
	
	return NULL;
}
	

RUN_TESTS(all_tests);



