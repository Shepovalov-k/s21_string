START_TEST(test_memchr) {
  char str[] = "hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'o', 5), memchr(str, 'o', 5));
  ck_assert_ptr_eq(s21_memchr(str, 'x', 5), memchr(str, 'x', 5));
}
END_TEST

Suite *s21_memchr_tests_suite(void) {
  Suite *s = suite_create("s21_memchr_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memchr);
  suite_add_tcase(s, tc_core);
  return s;
}