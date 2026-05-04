START_TEST(test_trim_spaces) {
  char *result = s21_trim("  hello  ", " ");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_multiple_chars) {
  char *result = s21_trim("xxyyhelloYYxx", "xy");
  ck_assert_str_eq(result, "helloYY");
  free(result);
}
END_TEST

START_TEST(test_trim_no_match) {
  char *result = s21_trim("hello", "xyz");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_all_chars) {
  char *result = s21_trim("xyzxyz", "xyz");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_string) {
  char *result = s21_trim("", "xyz");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_null_src) {
  char *result = s21_trim(NULL, "xyz");
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_null_trim_chars) {
  char *result = s21_trim("hello", NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_prefix) {
  char *result = s21_trim("xyzhello", "xyz");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_suffix) {
  char *result = s21_trim("helloxyz", "xyz");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_no_trim_middle) {
  char *result = s21_trim("helloxyzworld", "xyz");
  ck_assert_str_eq(result, "helloxyzworld");
  free(result);
}
END_TEST

Suite *s21_trim_tests_suite(void) {
  Suite *s = suite_create("s21_trim_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_trim_spaces);
  tcase_add_test(tc_core, test_trim_multiple_chars);
  tcase_add_test(tc_core, test_trim_no_match);
  tcase_add_test(tc_core, test_trim_all_chars);
  tcase_add_test(tc_core, test_trim_empty_string);
  tcase_add_test(tc_core, test_trim_null_src);
  tcase_add_test(tc_core, test_trim_null_trim_chars);
  tcase_add_test(tc_core, test_trim_prefix);
  tcase_add_test(tc_core, test_trim_suffix);
  tcase_add_test(tc_core, test_trim_no_trim_middle);

  suite_add_tcase(s, tc_core);
  return s;
}