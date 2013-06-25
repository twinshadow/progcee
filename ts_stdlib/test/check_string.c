#include <stdlib.h>
#include "twinshadow/string.h"

#include <check.h>
#include "twinshadow/check.h"

START_TEST(test_strshift_pos1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(3, buf, strlen(buf));
	ck_assert_str_eq(buf, "7890123456");
}
END_TEST

START_TEST(test_strshift_pos2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(8, buf, strlen(buf));
	ck_assert_str_eq(buf, "2345678901");
}
END_TEST

START_TEST(test_strshift_empty)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "");
	strshift(3, buf, 11);
	ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_strshift_neg1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(-3, buf, strlen(buf));
	ck_assert_str_eq(buf, "3456789012");
}
END_TEST

START_TEST(test_strshift_neg2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(-8, buf, strlen(buf));
	ck_assert_str_eq(buf, "8901234567");
}
END_TEST

START_TEST(test_strstrip_1)
{
	char test[] = "12345",
	     xpct[] = "12345";
	new_ck_str(buf, test);

	strstrip(buf, strlen(test));
	ck_assert_str_eq(buf, test);
}
END_TEST

Suite *
string_suite(void)
{
	Suite *s = suite_create("String");

	TCase *tc_strshift = tcase_create("strshift");
	tcase_add_test(tc_strshift, test_strshift_pos1);
	tcase_add_test(tc_strshift, test_strshift_pos2);
	tcase_add_test(tc_strshift, test_strshift_neg1);
	tcase_add_test(tc_strshift, test_strshift_neg2);
	tcase_add_test(tc_strshift, test_strshift_empty);
	suite_add_tcase(s, tc_strshift);

	TCase *tc_strstrip = tcase_create("strstrip");
	tcase_add_test(tc_strstrip, test_strstrip_1);
	suite_add_tcase(s, tc_strstrip);

	return s;
}

int
main(void)
{
	int number_failed;
	Suite *s = string_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
