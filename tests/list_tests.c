#include <assert.h>
#include "minunit.h"
#include "../src/list.h"

int n = 10;


char *test_create()
{
	List *list = list_create();
	mu_assert(list != NULL, "List could not be created.");
	
	list_clear_destroy(list);
	return NULL;
	
}

char *test_populate()
{
	List *list = list_create();
	int *arr = calloc(1, n * sizeof(int));
	list_populate(list, arr, n);
	
	int i = 0;
	LIST_FOREACH(list, first, next, cur)
	{
		mu_assert(*((int *)cur->value) == arr[i], "Wrong values after populate.");
		i ++;
	}
	
	list_clear_destroy(list);
	free(arr);
	return NULL;
}

char *test_clear_destroy()
{
	List *list = list_create();
	list_clear_destroy(list);
	
	return NULL;
}

char *test_push_pop()
{		
	List *list = list_create();
	int *arr = calloc(1, n * sizeof(int));	
	list_populate(list, arr, n);
	int i;
	mu_assert(list_count(list) == n, "Wrong list count value on push.");
	
	int *val = NULL;
	for (i = n - 1; i >= 0; i --)
	{
		val = list_pop(list);
		mu_assert(*val == arr[i], "Wrong value on pop.");
	}
	mu_assert(list_count(list) == 0, "Wrong list count value on pop.");
	
	list_clear_destroy(list);
	free(arr);
	return NULL;
}

char *test_unshift_shift()
{
	List *list = NULL;
	list = list_create();
	int *arr = calloc(1, n * sizeof(int));
	
	int i;
	list_populate(list, arr, n);
	
	mu_assert(list_count(list) == n, "Wrong list count value on unshift.");
	
	int *val = NULL;
	for (i = 0; i < n; i ++)
	{
		val = list_shift(list);
		mu_assert(*val == arr[i], "Wrong value on shift.");
	}
	mu_assert(list_count(list) == 0, "Wrong list count value on pop.");
	
	free(arr);
	
	list_clear_destroy(list);

	return NULL;
}

char *test_copy()
{
	List *from = list_create();
	List *to = list_create();

	int *arr = calloc(1, n * sizeof(int));
	
	list_populate(from, arr, n);
	
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
	List *list = list_create();
	int *arr = calloc(1, n * sizeof(int));
	list_populate(list, arr, n);
	
	int *value = list_remove(list, list->first->next);
	
	mu_assert(list_count(list) == n - 1, "Wrong size after remove.");
	mu_assert(*value == arr[1], "Wrong returned value after remove.");
	
	free(arr);
	list_clear_destroy(list);
	
	return NULL;
}

char *test_join()
{
	int *arr1 = calloc(1, n * sizeof(int));
	int *arr2 = calloc(1, n * sizeof(int));
	
	List *f = list_create();
	list_populate(f, arr1, n);
	
	List *s = list_create();
	list_populate(s, arr2, n);
	
	List *t = list_create();
	
	list_join(t, f, s);
	mu_assert(t->first->value == f->first->value && t->last->value == s->last->value, "Wrong first and last nodes.");
	mu_assert(t->count == (f->count + s->count), "Wrong count value on join.");
	list_print(t);
	list_print(f);
	list_print(s);
	
	free(arr1);
	free(arr2);
	list_clear_destroy(f);
	list_clear_destroy(s);
	list_clear_destroy(t);
	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_populate);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift_shift);
	mu_run_test(test_remove);
	mu_run_test(test_copy);
	mu_run_test(test_join);
	mu_run_test(test_clear_destroy);
	
	
	
	return NULL;
}
	

RUN_TESTS(all_tests);



