#include "twinshadow/string.h"
#include "twinshadow/check.h"

START_TEST(test_strshift_pos1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	ts_strshift(3, buf);
	ck_assert_str_eq(buf, "7890123456");
}
END_TEST

START_TEST(test_strshift_pos2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	ts_strshift(8, buf);
	ck_assert_str_eq(buf, "2345678901");
}
END_TEST

START_TEST(test_strshift_empty)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "");
	ts_strshift(3, buf);
	ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_strshift_neg1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	ts_strshift(-3, buf);
	ck_assert_str_eq(buf, "3456789012");
}
END_TEST

START_TEST(test_strshift_neg2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	ts_strshift(-8, buf);
	ck_assert_str_eq(buf, "8901234567");
}
END_TEST

START_TEST(test_memshift_int)
{
	int i;
	int offset = 3;
	int buf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int shifted_buf[] = {7, 8, 9, 0, 1, 2, 3, 4, 5, 6};

	ts_memshift(offset * sizeof(int), &buf, 10 * sizeof(int));

	for(i = 0; i < 10; i++)
		ck_assert_int_eq(buf[i], shifted_buf[i]);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("String");
	TCase *tc_strshift = tcase_create("strshift");
	tcase_add_test(tc_strshift, test_strshift_pos1);
	tcase_add_test(tc_strshift, test_strshift_pos2);
	tcase_add_test(tc_strshift, test_strshift_neg1);
	tcase_add_test(tc_strshift, test_strshift_neg2);
	tcase_add_test(tc_strshift, test_strshift_empty);
	tcase_add_test(tc_strshift, test_memshift_int);
	suite_add_tcase(s, tc_strshift);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
