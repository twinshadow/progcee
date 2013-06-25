#include "twinshadow/check.h"
#include "twinshadow/string.h"

#define TESTNAME "strrev"

START_TEST(test_strrev)
{
	char test[] = "12345",
	     xpct[] = "54321";
	char *buf = ts_strdup(test);

	ts_strrev(buf);
	ck_assert_str_eq(buf, xpct);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("check_strrev");
	TCase *tc = tcase_create("Main");
	tcase_add_test(tc, test_strrev);
	suite_add_tcase(s, tc);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
