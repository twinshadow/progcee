#include "twinshadow/check.h"
#include "twinshadow/vec.h"

TS_VEC_HEAD(ivec, int);
TS_VEC_NEW(ivec, int);
TS_VEC_FREE(ivec);
TS_VEC_RESIZE(ivec, int);

START_TEST(test_vec)
{
	struct ivec *test;
	int i, *idx;
	test = ivec_new(10);
	i = 0;
	TS_VEC_FOREACH(idx, test) {
		*idx = i++;
	}
	i = 9;
	TS_VEC_RFOREACH(idx, test) {
		ck_assert_int_eq(*idx, i--);
	}

	ivec_resize(test, 20);
	i = 0;
	TS_VEC_FOREACH(idx, test) {
		*idx = i++;
	}
	i = 19;
	TS_VEC_RFOREACH(idx, test) {
		ck_assert_int_eq(*idx, i--);
	}
	ivec_free(test);
}
END_TEST

TS_VEC_HEAD(svec, char*);
TS_VEC_NEW(svec, char*);
TS_VEC_FREE(svec);
TS_VEC_RESIZE(svec, char*);

START_TEST(test_vec2)
{
	struct svec *test;
	char **idx;
	int i;
	char *expect[] = {
		"lorem",
		"ipsum",
		"delorum",
		"sit",
		"amet"
	};

	test = svec_new(5);
	i = 0;
	TS_VEC_FOREACH(idx, test) {
		*idx = strdup(expect[i++]);
	}
	i = 4;
	TS_VEC_RFOREACH(idx, test) {
		ck_assert_str_eq(*idx, expect[i--]);
	}
	free(test);
}
END_TEST

int
main(void)
{
	int number_failed;

	Suite *s = suite_create("check_vec");
	TCase *tc = tcase_create("Main");
	tcase_add_test(tc, test_vec);
	tcase_add_test(tc, test_vec2);
	suite_add_tcase(s, tc);

	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
