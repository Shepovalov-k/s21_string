START_TEST(test_to_upper_normal_case) {
  const char *str = "hello world12345|";
  char *str_result = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_result, "HELLO WORLD12345|");
  free(str_result);
}
END_TEST

START_TEST(test_to_upper_null_input) {
  char *str_result = (char *)s21_to_upper(NULL);
  ck_assert_ptr_eq(str_result, NULL);
}
END_TEST

START_TEST(test_to_upper_empty_string) {
  const char *str = "";
  char *str_result = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_result, "");
  free(str_result);
}
END_TEST

START_TEST(test_to_upper_no_lowercase) {
  const char *str = "HELLO WORLD12345|";
  char *str_result = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_result, "HELLO WORLD12345|");
  free(str_result);
}
END_TEST

START_TEST(test_to_upper_special_characters) {
  const char *str = "!@#$%^&*()_+";
  char *str_result = (char *)s21_to_upper(str);
  ck_assert_str_eq(str_result, "!@#$%^&*()_+");
  free(str_result);
}
END_TEST

Suite *s21_to_upper_tests_suite(void) {
  Suite *s = suite_create("s21_to_upper_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_upper_normal_case);
  tcase_add_test(tc_core, test_to_upper_null_input);
  tcase_add_test(tc_core, test_to_upper_empty_string);
  tcase_add_test(tc_core, test_to_upper_no_lowercase);
  tcase_add_test(tc_core, test_to_upper_special_characters);

  suite_add_tcase(s, tc_core);
  return s;
}