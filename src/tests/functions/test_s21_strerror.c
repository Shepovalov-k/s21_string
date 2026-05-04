START_TEST(test_strerror) {
  ck_assert_str_eq(s21_strerror(-100), strerror(-100));
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(9), strerror(9));
  ck_assert_str_eq(s21_strerror(999), strerror(999));
}
END_TEST

Suite *s21_strerror_tests_suite(void) {
  Suite *s = suite_create("s21_strerror_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strerror);
  suite_add_tcase(s, tc_core);
  return s;
}