#include "twinshadow/check.h"
#include "twinshadow/hash.h"

START_TEST(test_hash_add)
{
	struct ts_table_s *table;
	struct ts_table_item_s **item;
	char *test;

	table = ts_table_new(4);
	test = "Hello World!";

	ts_table_add(test, strlen(test), table);
	item = ts_table_lookup(test, strlen(test), table);
	ck_assert(*item != NULL);
}
END_TEST

START_TEST(test_hash_rem)
{
	struct ts_table_s *table;
	struct ts_table_item_s **item;
	char *test;

	table = ts_table_new(4);
	test = "Hello World!";

	ts_table_add(test, strlen(test), table);
	item = ts_table_lookup(test, strlen(test), table);
	ck_assert(*item != NULL);

	ts_table_rem(test, strlen(test), table);
	item = ts_table_lookup(test, strlen(test), table);
	ck_assert(*item == NULL);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("check_hash");
	TCase *tc = tcase_create("Main");
	tcase_add_test(tc, test_hash_add);
	tcase_add_test(tc, test_hash_rem);
	suite_add_tcase(s, tc);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
