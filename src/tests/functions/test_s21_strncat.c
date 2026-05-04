START_TEST(test_strncat) {
  char dest[20] = "Hello ";
  char src[] = "world!";
  ck_assert_str_eq(s21_strncat(dest, src, 3), strncat(dest, src, 3));
}
END_TEST

Suite *s21_strncat_tests_suite(void) {
  Suite *s = suite_create("s21_strncat_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncat);
  suite_add_tcase(s, tc_core);
  return s;
}