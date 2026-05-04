START_TEST(test_strrchr) {
  char test_str_1[] = "An ordinar string";
  int test_ch_1 = 'n';

  char test_str_2[] = "Not an ordinar string";
  int test_ch_2 = ' ';

  char test_str_3[] = "";
  int test_ch_3 = 'n';

  char test_str_4[] = "An ordinar string";
  int test_ch_4 = '?';

  char test_str_5[] = "Not an \0rdinar string";
  int test_ch_5 = 0;

  char test_str_6[] = "An ordinar string";
  int test_ch_6 = 0;

  char test_str_7[] = "An ordinar string";
  int test_ch_7 = 256;

  char test_str_8[] = "An ordinar string";
  int test_ch_8 = 1024;

  ck_assert_ptr_eq(s21_strrchr(test_str_1, test_ch_1),
                   strrchr(test_str_1, test_ch_1));
  ck_assert_ptr_eq(s21_strrchr(test_str_2, test_ch_2),
                   strrchr(test_str_2, test_ch_2));
  ck_assert_ptr_eq(s21_strrchr(test_str_3, test_ch_3),
                   strrchr(test_str_3, test_ch_3));
  ck_assert_ptr_eq(s21_strrchr(test_str_4, test_ch_4),
                   strrchr(test_str_4, test_ch_4));
  ck_assert_ptr_eq(s21_strrchr(test_str_5, test_ch_5),
                   strrchr(test_str_5, test_ch_5));
  ck_assert_ptr_eq(s21_strrchr(test_str_6, test_ch_6),
                   strrchr(test_str_6, test_ch_6));
  ck_assert_ptr_eq(s21_strrchr(test_str_7, test_ch_7),
                   strrchr(test_str_7, test_ch_7));
  ck_assert_ptr_eq(s21_strrchr(test_str_8, test_ch_8),
                   strrchr(test_str_8, test_ch_8));
}
END_TEST

Suite *s21_strrchr_tests_suite(void) {
  Suite *s = suite_create("s21_strrchr_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strrchr);
  suite_add_tcase(s, tc_core);
  return s;
}