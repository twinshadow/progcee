#include <stdlib.h>
#include <check.h>
#include "twinshadow/string.h"

START_TEST(test_strstrip_pos1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(3, buf, strlen(buf));
	ck_assert_str_eq(buf, "7890123456");
}
END_TEST

START_TEST(test_strstrip_pos2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(8, buf, strlen(buf));
	ck_assert_str_eq(buf, "2345678901");
}
END_TEST

START_TEST(test_strstrip_empty)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "");
	strshift(3, buf, 11);
	ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_strstrip_neg1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(-3, buf, strlen(buf));
	ck_assert_str_eq(buf, "3456789012");
}
END_TEST

START_TEST(test_strstrip_neg2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(-8, buf, strlen(buf));
	ck_assert_str_eq(buf, "8901234567");
}
END_TEST

Suite *
string_suite(void)
{
	Suite *s = suite_create("String");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_strstrip_pos1);
	tcase_add_test(tc_core, test_strstrip_pos2);
	tcase_add_test(tc_core, test_strstrip_neg1);
	tcase_add_test(tc_core, test_strstrip_neg2);
	tcase_add_test(tc_core, test_strstrip_empty);

	suite_add_tcase(s, tc_core);

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
