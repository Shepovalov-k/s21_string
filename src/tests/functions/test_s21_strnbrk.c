START_TEST(test_strnbrk) {
  char test_str_1[] = "An ordinar string";
  char test_breakset_1[] = "aNg";

  char test_str_2[] = "An ordinar string";
  char test_breakset_2[] = "";

  char test_str_3[] = "An ordinar string";
  char test_breakset_3[] = "PoP";

  ck_assert_ptr_eq(s21_strpbrk(test_str_1, test_breakset_1),
                   strpbrk(test_str_1, test_breakset_1));
  ck_assert_ptr_eq(s21_strpbrk(test_str_2, test_breakset_2),
                   strpbrk(test_str_2, test_breakset_2));
  ck_assert_ptr_eq(s21_strpbrk(test_str_3, test_breakset_3),
                   strpbrk(test_str_3, test_breakset_3));
}
END_TEST

Suite *s21_strnbrk_tests_suite(void) {
  Suite *s = suite_create("s21_strnbrk_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strnbrk);
  suite_add_tcase(s, tc_core);
  return s;
}