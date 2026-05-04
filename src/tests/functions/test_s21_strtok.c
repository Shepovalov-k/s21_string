START_TEST(test_strtok_normal_case) {
  char s21_test_str[] = "An###ordinar####    ##string########";
  char test_str[] = "An###ordinar####    ##string########";
  char test_delim[] = "# ";

  ck_assert_str_eq(s21_strtok(s21_test_str, test_delim),
                   strtok(test_str, test_delim));
  ck_assert_str_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_str_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
}
END_TEST

START_TEST(test_strtok_empty_delimiter) {
  char s21_test_str[] = "An ordinar string";
  char test_str[] = "An ordinar string";
  char test_delim[] = "";

  ck_assert_str_eq(s21_strtok(s21_test_str, test_delim),
                   strtok(test_str, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
}
END_TEST

START_TEST(test_strtok_all_delimiters) {
  char s21_test_str[] = "aaaaaaaaaaaaaaaaaaaaaaaa";
  char test_str[] = "aaaaaaaaaaaaaaaaaaaaaaaa";
  char test_delim[] = "a";

  ck_assert_ptr_eq(s21_strtok(s21_test_str, test_delim),
                   strtok(test_str, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
}
END_TEST

START_TEST(test_strtok_no_delimiters_in_string) {
  char s21_test_str[] = "kekekekekek";
  char test_str[] = "kekekekekek";
  char test_delim[] = "lo";

  ck_assert_str_eq(s21_strtok(s21_test_str, test_delim),
                   strtok(test_str, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
}
END_TEST

START_TEST(test_strtok_empty_string) {
  char s21_test_str[] = "";
  char test_str[] = "";
  char test_delim[] = "a";

  ck_assert_ptr_eq(s21_strtok(s21_test_str, test_delim),
                   strtok(test_str, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
}
END_TEST

START_TEST(test_strtok_empty_string_and_delimiter) {
  char s21_test_str[] = "";
  char test_str[] = "";
  char test_delim[] = "";

  ck_assert_ptr_eq(s21_strtok(s21_test_str, test_delim),
                   strtok(test_str, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
  ck_assert_ptr_eq(s21_strtok(NULL, test_delim), strtok(NULL, test_delim));
}
END_TEST

Suite *s21_strtok_tests_suite(void) {
  Suite *s = suite_create("s21_strtok_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strtok_normal_case);
  tcase_add_test(tc_core, test_strtok_empty_delimiter);
  tcase_add_test(tc_core, test_strtok_all_delimiters);
  tcase_add_test(tc_core, test_strtok_no_delimiters_in_string);
  tcase_add_test(tc_core, test_strtok_empty_string);
  tcase_add_test(tc_core, test_strtok_empty_string_and_delimiter);

  suite_add_tcase(s, tc_core);
  return s;
}