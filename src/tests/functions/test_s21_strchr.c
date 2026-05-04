START_TEST(test_strchr) {
  char str[] = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
  ck_assert_ptr_eq(s21_strchr(str, 'x'), strchr(str, 'x'));
}
END_TEST

Suite *s21_strchr_tests(void) {
  Suite *s = suite_create("s21_strnchr_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strnchr);
  suite_add_tcase(s, tc_core);
  return s;
}