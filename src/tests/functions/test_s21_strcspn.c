START_TEST(test_strcspn) {
  ck_assert_int_eq(s21_strcspn("hello", "aeiou"), strcspn("hello", "aeiou"));
  ck_assert_int_eq(s21_strcspn("hello", "xyz"), strcspn("hello", "xyz"));
}
END_TEST

Suite *s21_strcspn_tests_suite(void) {
  Suite *s = suite_create("s21_strnspn_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strcspn);
  suite_add_tcase(s, tc_core);
  return s;
}