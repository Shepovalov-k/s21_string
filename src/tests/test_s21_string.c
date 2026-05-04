#include <check.h>
#include <limits.h>
#include <string.h>

#include "../s21_string.h"
#include "./functions/test_s21_insert.c"
#include "./functions/test_s21_memchr.c"
#include "./functions/test_s21_memcmp.c"
#include "./functions/test_s21_memcpy.c"
#include "./functions/test_s21_memset.c"
#include "./functions/test_s21_sprintf.c"
#include "./functions/test_s21_sscanf.c"
#include "./functions/test_s21_strcspn.c"
#include "./functions/test_s21_strerror.c"
#include "./functions/test_s21_strlen.c"
#include "./functions/test_s21_strnbrk.c"
#include "./functions/test_s21_strncat.c"
#include "./functions/test_s21_strncmp.c"
#include "./functions/test_s21_strncpy.c"
#include "./functions/test_s21_strrchr.c"
#include "./functions/test_s21_strstr.c"
#include "./functions/test_s21_strtok.c"
#include "./functions/test_s21_to_lower.c"
#include "./functions/test_s21_to_upper.c"
#include "./functions/test_s21_trim.c"

int main(void) {
  int number_failed;
  SRunner *sr = srunner_create(NULL);
  srunner_add_suite(sr, s21_to_upper_tests_suite());
  srunner_add_suite(sr, s21_to_lower_tests_suite());
  srunner_add_suite(sr, s21_trim_tests_suite());
  srunner_add_suite(sr, s21_insert_tests_suite());
  srunner_add_suite(sr, s21_memchr_tests_suite());
  srunner_add_suite(sr, s21_memcmp_tests_suite());
  srunner_add_suite(sr, s21_memcpy_tests_suite());
  srunner_add_suite(sr, s21_memset_tests_suite());
  srunner_add_suite(sr, s21_strncat_tests_suite());
  srunner_add_suite(sr, s21_strncpy_tests_suite());
  srunner_add_suite(sr, s21_strrchr_tests_suite());
  srunner_add_suite(sr, s21_strncmp_tests_suite());
  srunner_add_suite(sr, s21_strcspn_tests_suite());
  srunner_add_suite(sr, s21_strerror_tests_suite());
  srunner_add_suite(sr, s21_strlen_tests_suite());
  srunner_add_suite(sr, s21_strnbrk_tests_suite());
  srunner_add_suite(sr, s21_strstr_tests_suite());
  srunner_add_suite(sr, s21_strtok_tests_suite());
  srunner_add_suite(sr, s21_sprintf_tests_suite());
  srunner_add_suite(sr, s21_sscanf_tests_suite());
  // srunner_add_suite(sr, s21_write_decim_to_ptr_tests_suite());
  // srunner_add_suite(sr, s21_is_short_in_range_tests_suite());
  // srunner_add_suite(sr, s21_handle_g_tests_suite());
  // srunner_add_suite(sr, s21_decimal_to_str_tests_suite());
  // srunner_add_suite(sr, s21_udecimal_to_str_tests_suite());
  // srunner_add_suite(sr, s21_numcount_tests_suite());
  // srunner_add_suite(sr, s21_unumcount_tests_suite());
  // srunner_add_suite(sr, s21_writestring_tests_suite());
  // srunner_add_suite(sr, s21_need_sign_space_tests_suite());
  // srunner_add_suite(sr, s21_ld_to_str_tests_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
// ex?
