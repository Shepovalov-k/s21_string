START_TEST(test_memcpy) {
  char src[] = "source";
  char dest[7];
  ck_assert_ptr_eq(s21_memcpy(dest, src, 6), memcpy(dest, src, 6));
}
END_TEST

Suite *s21_memcpy_tests_suite(void) {
  Suite *s = suite_create("s21_memcpy_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcpy);
  suite_add_tcase(s, tc_core);
  return s;
}