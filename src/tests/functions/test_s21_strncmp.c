START_TEST(test_strncmp) {
  ck_assert_int_eq(s21_strncmp("hello", "hello", 5),
                   strncmp("hello", "hello", 5));
  ck_assert_int_eq(s21_strncmp("hello", "hella", 5),
                   strncmp("hello", "hella", 5));
  ck_assert_int_eq(s21_strncmp("hello", "hella", 3),
                   strncmp("hello", "hella", 3));
}
END_TEST

Suite *s21_strncmp_tests_suite(void) {
  Suite *s = suite_create("s21_strncmp_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncmp);
  suite_add_tcase(s, tc_core);
  return s;
}