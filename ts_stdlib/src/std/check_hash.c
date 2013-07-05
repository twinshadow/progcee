#include "twinshadow/check.h"
#include "twinshadow/hash.h"

START_TEST(test_hash)
{
	struct ts_table_s *table;
	struct ts_table_item_s **item;
	table = ts_table_new(4);
	char *test = "Hello World!";
	item = ts_table_lookup(test, strlen(test), table);
	ck_assert(item != NULL);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("check_hash");
	TCase *tc = tcase_create("Main");
	tcase_add_test(tc, test_hash);
	suite_add_tcase(s, tc);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
