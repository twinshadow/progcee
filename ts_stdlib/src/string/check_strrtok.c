#include "twinshadow/check.h"
#include "twinshadow/string.h"

START_TEST(test_strrtok)
{
	char buf[] = "one two three four five";
	char *xpct[] = {
		"five",
		"four",
		"three",
		"two",
		"one"
	};
	char *test = strdup(buf);

	int i;
	char *ptr = NULL;
	for (i = 0; (ptr = ts_strrtok(test, ' ')); i++)
		ck_assert_str_eq(ptr, xpct[i]);

	free(test);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("check_strrtok");
	TCase *tc = tcase_create("Main");
	tcase_add_test(tc, test_strrtok);
	suite_add_tcase(s, tc);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
