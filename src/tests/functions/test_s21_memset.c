START_TEST(test_memset) {
  char str[5] = "abcd";
  ck_assert_ptr_eq(s21_memset(str, 'x', 3), memset(str, 'x', 3));
}
END_TEST

Suite *s21_memset_tests_suite(void) {
  Suite *s = suite_create("s21_memset_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memset);
  suite_add_tcase(s, tc_core);
  return s;
}