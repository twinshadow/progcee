#include "twinshadow/check.h"
#include "twinshadow/string.h"

START_TEST(test_strstrip)
{
	char buf[] = "   one two three   ";
	char xpct[] = "one two three";
	char *test = strdup(buf);

	ts_strstrip(test);
	ck_assert_str_eq(test, xpct);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("check_strstrip");
	TCase *tc = tcase_create("Main");
	tcase_add_test(tc, test_strstrip);
	suite_add_tcase(s, tc);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
