#include "twinshadow/string.h"
#include "twinshadow/check.h"

START_TEST(test_strrot)
{
	char test[] = "abcxyz ABCXYZ 012789",
	     xpct[] = "nopklm NOPKLM 345012";
	char *buf = ts_strdup(test);

	ts_strrot(13, buf);
	ck_assert_str_eq(buf, xpct);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("String");
	TCase *tc_strshift = tcase_create("strrot");
	tcase_add_test(tc_strshift, test_strrot);
	suite_add_tcase(s, tc_strshift);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
