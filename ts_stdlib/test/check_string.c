#include <stdlib.h>
#include <check.h>
#include "twinshadow/string.h"

START_TEST(test_strstrip_pos1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(3, buf, strlen(buf), sizeof(char));
	ck_assert_str_eq(buf, "7890123456");
}
END_TEST

START_TEST(test_strstrip_pos2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(8, buf, strlen(buf), sizeof(char));
	ck_assert_str_eq(buf, "2345678901");
}
END_TEST

START_TEST(test_strstrip_empty)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "");
	strshift(3, buf, 11, sizeof(char));
	ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_strstrip_neg1)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(-3, buf, strlen(buf), sizeof(char));
	ck_assert_str_eq(buf, "3456789012");
}
END_TEST

START_TEST(test_strstrip_neg2)
{
	char *buf = calloc(12, sizeof(char));
	strcpy(buf, "0123456789");
	strshift(-8, buf, strlen(buf), sizeof(char));
	ck_assert_str_eq(buf, "8901234567");
}
END_TEST

START_TEST(test_strshift_int)
{
     int offset = 3;
     int buf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
     int shifted_buf[] = {7, 8, 9, 0, 1, 2, 3, 4, 5, 6};

     strshift(offset, &buf, 10, sizeof(int));

     for(int i = 0; i < 10; i++)
	  ck_assert_int_eq(buf[i], shifted_buf[i]);
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
	tcase_add_test(tc_core, test_strshift_int);
	
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
