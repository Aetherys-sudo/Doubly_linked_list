#include <assert.h>
#include "minunit.h"
#include "../src/list.h"

List *list = NULL;

char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

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
	list_push(list, test1);
	mu_assert(list_last(list) == test1, "Pop function failed test1.");
	
	list_push(list, test2);
	mu_assert(list_last(list) == test2, "Pop function failed test2.");
	
	list_push(list, test3);
	mu_assert(list_last(list) == test3, "Pop function failed test3.");
	
	mu_assert(list_count(list) == 3, "Wrong count after push.");
	
	char *val = list_pop(list);
	mu_assert(test3 == val, "Wrong value on pop.");
	
	val = list_pop(list);
	mu_assert(test2 == val, "Wrong value on pop.");
	
	val = list_pop(list);
	mu_assert(test1 == val, "Wrong value on pop.");
	
	mu_assert(list_count(list) == 0, "Wrong value after pop.");
	
	return NULL;
}

char *test_unshift()
{
	list_unshift(list, test3);
	mu_assert(list_first(list) == test3, "Unshift function failed test3.");
	
	list_unshift(list, test2);
	mu_assert(list_first(list) == test2, "Unshift function failed test2.");
	
	list_unshift(list, test1);
	mu_assert(list_first(list) == test1, "Unshift function failed test1.");
	
	mu_assert(list_count(list) == 3, "Wrong count after unshift.");
	
	return NULL;
}

char *test_remove()
{
	char *val = list_remove(list, list->first->next);
	
	mu_assert(val == test2, "Wrong value on remove.");
	mu_assert(list_count(list) == 2, "Wrong count on remove.");
	
	mu_assert(list_first(list) == test1, "Wrong first element on remove.");
	
	mu_assert(list_last(list) == test3, "Wrong last element on remove.");
	
	return NULL;
}

char *test_shift()
{
	mu_assert(list_count(list) != 0, "Wrong count before shift.");
	
	char *val = list_shift(list);
	mu_assert(test1 == val, "Wrong value on shift.");
	
	val = list_shift(list);
	mu_assert(test3 == val, "Wrong value on shift.");
	
	mu_assert(list_count(list) == 0, "Wrong value after shift.");
	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_remove);
	mu_run_test(test_shift);
	mu_run_test(test_clear_destroy);
	
	return NULL;
}
	

RUN_TESTS(all_tests);



