#include <check.h>
#include <stdlib.h>
#include <string.h>

// Test case 1: Insert in the middle
START_TEST(test_insert_middle) {
  const char *src = "Hello, World!";
  const char *str = "Beautiful ";
  size_t start_index = 7;

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, Beautiful World!");
  free(result);
}
END_TEST

// Test case 2: Insert at the beginning
START_TEST(test_insert_beginning) {
  const char *src = "World!";
  const char *str = "Hello, ";
  size_t start_index = 0;

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

// Test case 3: Insert at the end
START_TEST(test_insert_end) {
  const char *src = "Hello, ";
  const char *str = "World!";
  size_t start_index = strlen(src);

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

// Test case 4: Insert into an empty string
START_TEST(test_insert_into_empty) {
  const char *src = "";
  const char *str = "Hello, World!";
  size_t start_index = 0;

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

// Test case 5: Insert an empty string
START_TEST(test_insert_empty_string) {
  const char *src = "Hello, World!";
  const char *str = "";
  size_t start_index = 7;

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

// Test case 6: Source string is NULL
START_TEST(test_insert_src_null) {
  const char *src = NULL;
  const char *str = "Hello, World!";
  size_t start_index = 0;

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
}
END_TEST

// Test case 7: String to insert is NULL
START_TEST(test_insert_str_null) {
  const char *src = "Hello, World!";
  const char *str = NULL;
  size_t start_index = 7;

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
}
END_TEST

// Test case 8: Invalid start index
START_TEST(test_insert_invalid_index) {
  const char *src = "Hello, World!";
  const char *str = "Beautiful ";
  size_t start_index = 20;

  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
}
END_TEST

// Test suite
Suite *s21_insert_tests_suite(void) {
  Suite *s = suite_create("s21_insert_tests");
  TCase *tc_core = tcase_create("Core");

  // Add individual test cases to the test suite
  tcase_add_test(tc_core, test_insert_middle);
  tcase_add_test(tc_core, test_insert_beginning);
  tcase_add_test(tc_core, test_insert_end);
  tcase_add_test(tc_core, test_insert_into_empty);
  tcase_add_test(tc_core, test_insert_empty_string);
  tcase_add_test(tc_core, test_insert_src_null);
  tcase_add_test(tc_core, test_insert_str_null);
  tcase_add_test(tc_core, test_insert_invalid_index);

  suite_add_tcase(s, tc_core);
  return s;
}