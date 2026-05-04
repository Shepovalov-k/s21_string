START_TEST(test_strlen) {
  char test_str_1[] = "An ordinar string";
  char test_str_2[] = "Not an \0rdinar string";
  char test_str_3[] = "1";
  char test_str_4[] = "";
  char test_str_5[] = "Съешь же этих французских булок да выпей чаю";
  char test_str_6[] =
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY "
      "VERY VERY VERY VERY VERY VERY VERY VERY VERY VERY LONG STRING";
  char test_str_7[] = "\0";
  char test_str_8[] = "\0there are some symbols here";
  ck_assert_int_eq(s21_strlen(test_str_1), strlen(test_str_1));
  ck_assert_int_eq(s21_strlen(test_str_2), strlen(test_str_2));
  ck_assert_int_eq(s21_strlen(test_str_3), strlen(test_str_3));
  ck_assert_int_eq(s21_strlen(test_str_4), strlen(test_str_4));
  ck_assert_int_eq(s21_strlen(test_str_5), strlen(test_str_5));
  ck_assert_int_eq(s21_strlen(test_str_6), strlen(test_str_6));
  ck_assert_int_eq(s21_strlen(test_str_7), strlen(test_str_7));
  ck_assert_int_eq(s21_strlen(test_str_8), strlen(test_str_8));
}
END_TEST

Suite *s21_strlen_tests_suite(void) {
  Suite *s = suite_create("s21_strlen_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strlen);
  suite_add_tcase(s, tc_core);
  return s;
}