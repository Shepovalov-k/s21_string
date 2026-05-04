START_TEST(test_strstr) {
  char test_str_1[] = "An ordinar string";
  char test_needle_1[] = "An";

  char test_str_2[] = "An ordinar string";
  char test_needle_2[] = "ina";

  char test_str_3[] = "aaaaaaaaaaaaaaaaaaaaaaaa";
  char test_needle_3[] = "aaa";

  char test_str_4[] = "kekekekekek";
  char test_needle_4[] = "lol";

  char test_str_5[] = "";
  char test_needle_5[] = "aaa";

  char test_str_6[] = "";
  char test_needle_6[] = "";

  char test_str_7[] = "some text";
  char test_needle_7[] = "";

  char test_str_8[] = "An ordinar string";
  char test_needle_8[] = "g";

  char test_str_9[] = "Съешь же этих французских булок да выпей чаю";
  char test_needle_9[] = "их";

  ck_assert_ptr_eq(s21_strstr(test_str_1, test_needle_1),
                   strstr(test_str_1, test_needle_1));
  ck_assert_ptr_eq(s21_strstr(test_str_2, test_needle_2),
                   strstr(test_str_2, test_needle_2));
  ck_assert_ptr_eq(s21_strstr(test_str_3, test_needle_3),
                   strstr(test_str_3, test_needle_3));
  ck_assert_ptr_eq(s21_strstr(test_str_4, test_needle_4),
                   strstr(test_str_4, test_needle_4));
  ck_assert_ptr_eq(s21_strstr(test_str_5, test_needle_5),
                   strstr(test_str_5, test_needle_5));
  ck_assert_ptr_eq(s21_strstr(test_str_6, test_needle_6),
                   strstr(test_str_6, test_needle_6));
  ck_assert_ptr_eq(s21_strstr(test_str_7, test_needle_7),
                   strstr(test_str_7, test_needle_7));
  ck_assert_ptr_eq(s21_strstr(test_str_8, test_needle_8),
                   strstr(test_str_8, test_needle_8));
  ck_assert_ptr_eq(s21_strstr(test_str_9, test_needle_9),
                   strstr(test_str_9, test_needle_9));
}
END_TEST

Suite *s21_strstr_tests_suite(void) {
  Suite *s = suite_create("s21_strrchr_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strstr);
  suite_add_tcase(s, tc_core);
  return s;
}