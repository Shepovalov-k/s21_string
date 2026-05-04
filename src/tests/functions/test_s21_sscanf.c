#include <check.h>

START_TEST(test_sscanf_char) {
  char result, expected;
  ck_assert_int_eq(s21_sscanf("g", "%c", &result),
                   sscanf("g", "%c", &expected));
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sscanf_unsign_int) {
  int result, expected;
  unsigned int num_result, num_expected;

  result = s21_sscanf("%   4", "%%%u", &num_result);
  expected = sscanf("%   4", "%%%u", &num_expected);

  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(test_sscanf_integer) {
  int result, expected;

  // Test case 1: Integer parsing
  const char *input = "123";
  int num_result = 0, num_expected = 0;

  result = s21_sscanf(input, "%d", &num_result);
  expected = sscanf(input, "%d", &num_expected);

  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(test_sscanf_string) {
  int result, expected;

  // Test case 2: String parsing
  const char *input = "HelloWorld";
  char str_result[50] = {0}, str_expected[50] = {0};

  result = s21_sscanf(input, "%s", str_result);
  expected = sscanf(input, "%s", str_expected);

  ck_assert_int_eq(result, expected);
  ck_assert_str_eq(str_result, str_expected);
}
END_TEST

// scientific format is not currently supported
START_TEST(test_sscanf_float) {
  int result, expected;

  // Test case 3: Float parsing
  const char *input = "123.456";
  float float_result = 0.0, float_expected = 0.0;

  result = s21_sscanf(input, "%f", &float_result);
  expected = sscanf(input, "%f", &float_expected);

  ck_assert_int_eq(result, expected);
  ck_assert_float_eq_tol(float_result, float_expected, 1e-6);
}
END_TEST

START_TEST(test_sscanf_ptr) {
  int result, expected;

  int *ptr_result, *ptr_expected;
  int value = 100;
  char buffer[50];
  sprintf(buffer, "%p", (void *)&value);
  result = s21_sscanf(buffer, "%p", (void **)&ptr_result);
  expected = sscanf(buffer, "%p", (void **)&ptr_expected);
  ck_assert_int_eq(result, expected);
  ck_assert_ptr_eq(ptr_result, ptr_expected);
}
END_TEST

START_TEST(test_sscanf_multiple_values) {
  int result, expected;

  // Test case 4: Parsing multiple values
  const char *input = "42 Hello 3.14";
  int int_result = 0, int_expected = 0;
  char str_result[50] = {0}, str_expected[50] = {0};
  float float_result = 0.0, float_expected = 0.0;

  result =
      s21_sscanf(input, "%d %s %f", &int_result, str_result, &float_result);
  expected =
      sscanf(input, "%d %s %f", &int_expected, str_expected, &float_expected);

  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(int_result, int_expected);
  ck_assert_str_eq(str_result, str_expected);
  ck_assert_float_eq_tol(float_result, float_expected, 1e-6);
}
END_TEST

START_TEST(test_sscanf_percent) {
  int result, expected;
  result = s21_sscanf("%%", "%%");
  expected = sscanf("%%", "%%");
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sscanf_hex) {
  unsigned int result, expected;
  int ret1 = s21_sscanf("0x1a3", "%x", &result);
  int ret2 = sscanf("0x1a3", "%x", &expected);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sscanf_octal) {
  unsigned int result, expected;
  int ret1 = s21_sscanf("123", "%o", &result);
  int ret2 = sscanf("123", "%o", &expected);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sscanf_width) {
  char result[5] = {0}, expected[5] = {0};
  int ret1 = s21_sscanf("hello", "%4s", result);
  int ret2 = sscanf("hello", "%4s", expected);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_sscanf_precision) {
  float result, expected;
  int num_result = s21_sscanf("3.141592", "%3f", &result);
  int num_expected = sscanf("3.141592", "%3f", &expected);
  ck_assert_float_eq_tol(result, expected, 1e-6);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(test_sscanf_length_h) {
  short result, expected;
  int num_result = s21_sscanf("12345", "%hd", &result);
  int num_expected = sscanf("12345", "%hd", &expected);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(test_sscanf_length_l) {
  long result, expected;
  int ret1 = s21_sscanf("123456789", "%ld", &result);
  int ret2 = sscanf("123456789", "%ld", &expected);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sscanf_flag_zero) {
  int result, expected;
  int ret1 = s21_sscanf("0042", "%04d", &result);
  int ret2 = sscanf("0042", "%04d", &expected);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sscanf_n) {
  int count1 = 0, count2 = 0;
  int value1 = 0, value2 = 0;
  int ret1 = s21_sscanf("123 abc", "%d abc%n", &value1, &count1);
  int ret2 = sscanf("123 abc", "%d abc%n", &value2, &count2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(value1, value2);
  ck_assert_int_eq(count1, count2);
}
END_TEST

/*START_TEST(test_sscanf_brackets) {
  char result[20] = {0}, expected[20] = {0};
  int ret1 = s21_sscanf("hello123", "%[a-z]", result);
  int ret2 = sscanf("hello123", "%[a-z]", expected);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(result, expected);
}
END_TEST*/

/*START_TEST(test_sscanf_neg_brackets) {
  char result[20] = {0}, expected[20] = {0};
  int ret1 = s21_sscanf("123hello", "%[^a-z]", result);
  int ret2 = sscanf("123hello", "%[^a-z]", expected);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(result, expected);
}
END_TEST*/

/*START_TEST(test_sscanf_star) {
  int value1 = 0, value2 = 0;
  int ret1 = sscanf("123 456", "%*d %d", &value1);
  int ret2 = s21_sscanf("123 456", "%*d %d", &value2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(value1, value2);
}
END_TEST*/

START_TEST(sscanf_spec_c_2) {
  char format[] = "%c";
  char str[] = "\t\n\n  1 \n  \t";
  char c1, c2;
  int16_t res1 = s21_sscanf(str, format, &c1);
  int16_t res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_spec_c_4) {
  char format[] = "%c";
  char str[] = "\t\n\n   \n  \ta";
  char c1, c2;
  int16_t res1 = s21_sscanf(str, format, &c1);
  int16_t res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_spec_c_5) {
  char format[] = "%c%c%c";
  char str[] = "\t\n\n  123 \n  \t";
  char c11, c12, c13, c21, c22, c23;

  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(sscanf_spec_c_6) {
  char format[] = "%c %c \t%c";
  char str[] = "\t\n\n  1    2 3 \n  \t";
  char c11, c12, c13, c21, c22, c23;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_c_7) {
  char format[] = "%c %c \t%c";
  char str[] = "\t\n\n  123 \n  \t";
  char c11, c12, c13, c21, c22, c23;
  int16_t res1 = s21_sscanf(str, format, &c11, &c12, &c13);
  int16_t res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST
START_TEST(sscanf_spec_hd_1) {
  char format[] = "%hd";
  char str[] = "123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_2) {
  char format[] = "%hd";
  char str[] = "-123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_3) {
  char format[] = "%hd";
  char str[] = "+123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_4) {
  char format[] = "%3hd";
  char str[] = "-123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_5) {
  char format[] = "%4hd";
  char str[] = "-123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_6) {
  char format[] = "%10hd";
  char str[] = "-123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_7) {
  char format[] = "%1hd";
  char str[] = "-123";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_hd_8) {
  char format[] = "%3hd";
  char str[] = "+123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_9) {
  char format[] = "%4hd";
  char str[] = "+123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_10) {
  char format[] = "%10hd";
  char str[] = "+123";
  short d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_11) {
  char format[] = "%1hd";
  char str[] = "+123";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_12) {
  char format[] = "%*1hd";
  char str[] = "+123";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_13) {
  char format[] = "%*hd";
  char str[] = "123";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_14) {
  char format[] = "%hd";
  char str[] = "+2147483647";
  short d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_15) {
  char format[] = "%hd";
  char str[] = "+2147483648";
  short d1 = 0, d2 = 0;
  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_16) {
  char format[] = "%hd";
  char str[] = "214743483648";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_17) {
  char format[] = "%hd";
  char str[] = "-2147483648";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_18) {
  char format[] = "%hd";
  char str[] = "-2147483649";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_19) {
  char format[] = "%hd";
  char str[] = "-214748364239";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_20) {
  char format[] = "%hd";
  char str[] = "-9223372036854775808";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_21) {
  char format[] = "%hd";
  char str[] = "-9223372036854775809";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_22) {
  char format[] = "%hd";
  char str[] = "-922337203685477582309";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_23) {
  char format[] = "%hd";
  char str[] = "9223372036854775807";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_24) {
  char format[] = "%hd";
  char str[] = "9223372036854775808";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_25) {
  char format[] = "%hd";
  char str[] = "922337203685477582309";
  short d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_1) {
  char format[] = "%d";
  char str[] = "123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_2) {
  char format[] = "%d";
  char str[] = "-123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_3) {
  char format[] = "%d";
  char str[] = "+123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_4) {
  char format[] = "%3d";
  char str[] = "-123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_5) {
  char format[] = "%4d";
  char str[] = "-123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_6) {
  char format[] = "%10d";
  char str[] = "-123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_7) {
  char format[] = "%1d";
  char str[] = "-123";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_8) {
  char format[] = "%3d";
  char str[] = "+123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_9) {
  char format[] = "%4d";
  char str[] = "+123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_10) {
  char format[] = "%10d";
  char str[] = "+123";
  int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_11) {
  char format[] = "%1d";
  char str[] = "+123";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_12) {
  char format[] = "%*1d";
  char str[] = "+123";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_13) {
  char format[] = "%*d";
  char str[] = "123";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_14) {
  char format[] = "%d";
  char str[] = "2147483647";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_15) {
  char format[] = "%d";
  char str[] = "+2147483648";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_16) {
  char format[] = "%d";
  char str[] = "214743483648";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_17) {
  char format[] = "%d";
  char str[] = "-2147483648";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_18) {
  char format[] = "%d";
  char str[] = "-2147483649";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_19) {
  char format[] = "%d";
  char str[] = "-214748364239";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_20) {
  char format[] = "%d";
  char str[] = "-9223372036854775808";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_21) {
  char format[] = "%d";
  char str[] = "-9223372036854775809";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_22) {
  char format[] = "%d";
  char str[] = "-922337203685477582309";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_23) {
  char format[] = "%d";
  char str[] = "9223372036854775807";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_24) {
  char format[] = "%d";
  char str[] = "9223372036854775808";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_25) {
  char format[] = "%d";
  char str[] = "922337203685477582309";
  int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_1) {
  char format[] = "%ld";
  char str[] = "123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_ld_2) {
  char format[] = "%ld";
  char str[] = "-123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_3) {
  char format[] = "%ld";
  char str[] = "+123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_4) {
  char format[] = "%3ld";
  char str[] = "-123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_5) {
  char format[] = "%4ld";
  char str[] = "-123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_6) {
  char format[] = "%10ld";
  char str[] = "-123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_7) {
  char format[] = "%1ld";
  char str[] = "-123";
  long int d1 = 100, d2 = 100;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_ld_8) {
  char format[] = "%3ld";
  char str[] = "+123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_9) {
  char format[] = "%4ld";
  char str[] = "+123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_10) {
  char format[] = "%10ld";
  char str[] = "+123";
  long int d1, d2;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_11) {
  char format[] = "%1ld";
  char str[] = "+123";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_12) {
  char format[] = "%*1ld";
  char str[] = "+123";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_13) {
  char format[] = "%*ld";
  char str[] = "123";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_14) {
  char format[] = "%ld";
  char str[] = "2147483647";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_15) {
  char format[] = "%ld";
  char str[] = "+2147483648";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_16) {
  char format[] = "%ld";
  char str[] = "214743483648";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_17) {
  char format[] = "%ld";
  char str[] = "-2147483648";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_18) {
  char format[] = "%ld";
  char str[] = "-2147483649";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_19) {
  char format[] = "%ld";
  char str[] = "-214748364239";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_20) {
  char format[] = "%ld";
  char str[] = "-9223372036854775808";
  long int d1 = 100, d2 = 100;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_ld_21) {
  char format[] = "%ld";
  char str[] = "-9223372036854775809";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_ld_22) {
  char format[] = "%ld";
  char str[] = "-922337203685477582309";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_23) {
  char format[] = "%ld";
  char str[] = "9223372036854775807";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_24) {
  char format[] = "%ld";
  char str[] = "9223372036854775808";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_25) {
  char format[] = "%ld";
  char str[] = "922337203685477582309";
  long int d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_empty_1) {
  char format[] = "%d";
  char str[] = "";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_2) {
  char format[] = "%d";
  char str[] = "     ";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_3) {
  char format[] = "%d";
  char str[] = "\n";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_4) {
  char format[] = "%d";
  char str[] = "\t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_5) {
  char format[] = "%d";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_6) {
  char format[] = "";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_7) {
  char format[] = "\t";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_1) {
  short d1, d2;
  short q1, q2;
  short z1, z2;

  int16_t num_result = s21_sscanf("123 +198 -87", "%hi%hi%hi", &d1, &q1, &z1);
  int16_t num_expected = sscanf("123 +198 -87", "%hi%hi%hi", &d2, &q2, &z2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_2) {
  char format[] = "%hi %hi %hi";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_3) {
  char format[] = "%1hi %1hi %1hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_4) {
  char format[] = "%2hi %2hi %2hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_5) {
  char format[] = "%3hi %3hi %3hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_6) {
  char format[] = "%30hi %24hi %21hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_7) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_8) {
  char format[] = "%hi %hi %hi %hi";
  char str[] =
      "9223372036854775807 +9223372036854775808 -9223372036854775808 "
      "-9223372036854775809";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_1) {
  char format[] = "%hi%hi%hi";
  char str[] = "0123 +0198 -087";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_2) {
  char format[] = "%hi %hi %hi";
  char str[] = "0123 +0198 -087";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_3) {
  char format[] = "%1hi %1hi %1hi";
  char str[] = "013 +0137 -08";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_4) {
  char format[] = "%2hi %2hi %2hi";
  char str[] = "013 +0137 -08";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_5) {
  char format[] = "%3hi %3hi %3hi";
  char str[] = "013 +0137 -08";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_6) {
  char format[] = "%30hi %24hi %21hi";
  char str[] = "013 +0137 -08";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_7) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "037777777777 +040000000000 -040000000000 -040000000001";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_8) {
  char format[] = "%hi %hi %hi %hi";
  char str[] =
      "01777777777777777777777 +02000000000000000000000 "
      "-02000000000000000000000 -02000000000000000000001";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_1) {
  char format[] = "%hi%hi%hi";
  char str[] = "0x123 +0X198 -0x87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_2) {
  char format[] = "%hi %hi %hi";
  char str[] = "0X123 +0x198 -0X87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_3) {
  char format[] = "%1hi %1hi %1hi";
  char str[] = "0X13 +0x137 -0x8";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_5) {
  char format[] = "%3hi %3hi %3hi";
  char str[] = "0x13 +0x137 -0x8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_6) {
  char format[] = "%30hi %24hi %21hi";
  char str[] = "0x13 +0x1a -0x8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_7) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "0xffffffff +0xffffffeab -0xFfFfffFf -0x39cdb3aa";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_8) {
  char format[] = "%hi %hi %hi %hi";
  char str[] =
      "0xFFFFFFFFFFFFFFFF 0x8000000000000000 -0xFFFFFFFFFFFFFFFF "
      "-0x348923848239742389328";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_1) {
  char format[] = "%i%i%i";
  char str[] = "123 +198 -87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_2) {
  char format[] = "%i %i %i";
  char str[] = "123 +198 -87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_3) {
  char format[] = "%1i %1i %1i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_4) {
  char format[] = "%2i %2i %2i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_5) {
  char format[] = "%3i %3i %3i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_6) {
  char format[] = "%30i %24i %21i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_7) {
  char format[] = "%i %i %i %i";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  unsigned int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_8) {
  char format[] = "%i %i %i %i";
  char str[] =
      "9223372036854775807 +9223372036854775808 -9223372036854775808 "
      "-9223372036854775809";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  unsigned int w1, w2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_1) {
  char format[] = "%i%i%i";
  char str[] = "0123 +0198 -087";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_2) {
  char format[] = "%i %i %i";
  char str[] = "0123 +0198 -087";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_3) {
  char format[] = "%1i %1i %1i";
  char str[] = "013 +0137 -08";
  int d1, d2;
  int q1, q2;
  int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_4) {
  char format[] = "%2i %2i %2i";
  char str[] = "013 +0137 -08";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_5) {
  char format[] = "%3i %3i %3i";
  char str[] = "013 +0137 -08";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_6) {
  char format[] = "%30i %24i %21i";
  char str[] = "013 +0137 -08";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_7) {
  char format[] = "%i %i %i %i";
  char str[] = "037777777777 +040000000000 -040000000000 -040000000001";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  unsigned int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_oct_8) {
  char format[] = "%i %i %i %i";
  char str[] =
      "01777777777777777777777 +02000000000000000000000 "
      "-02000000000000000000000 -02000000000000000000001";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  unsigned int w1, w2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_hex_1) {
  char format[] = "%i%i%i";
  char str[] = "0x123 +0X198 -0x87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_hex_2) {
  char format[] = "%i %i %i";
  char str[] = "0X123 +0x198 -0X87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_hex_3) {
  char format[] = "%1i %1i %1i";
  char str[] = "0X13 +0x137 -0x8";
  unsigned int d1 = 100, d2 = 100;
  unsigned int q1 = 100, q2 = 100;
  unsigned int z1 = 100, z2 = 100;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_hex_5) {
  char format[] = "%3i %3i %3i";
  char str[] = "0x13 +0x137 -0x8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_hex_6) {
  char format[] = "%30i %24i %21i";
  char str[] = "0x13 +0x1a -0x8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_hex_7) {
  char format[] = "%i %i %i %i";
  char str[] = "0xffffffff +0xffffffeab -0xFfFfffFf -0x39cdb3aa";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  unsigned int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_i_hex_8) {
  char format[] = "%i %i %i %i";
  char str[] =
      "0xFFFFFFFFFFFFFFFF 0x8000000000000000 -0xFFFFFFFFFFFFFFFF "
      "-0x348923848239742389328";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  unsigned int w1, w2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_1) {
  char format[] = "%li%li%li";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_2) {
  char format[] = "%li %li %li";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_3) {
  char format[] = "%1li %1li %1li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_4) {
  char format[] = "%2li %2li %2li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_5) {
  char format[] = "%3li %3li %3li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_6) {
  char format[] = "%30li %24li %21li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_7) {
  char format[] = "%li %li %li %li";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_dec_8) {
  char format[] = "%li %li %li %li";
  char str[] =
      "9223372036854775807 +9223372036854775808 -9223372036854775808 "
      "-9223372036854775809";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;
  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_1) {
  char format[] = "%li%li%li";
  char str[] = "0123 +0198 -087";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_2) {
  char format[] = "%li %li %li";
  char str[] = "0123 +0198 -087";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_3) {
  char format[] = "%1li %1li %1li";
  char str[] = "013 +0137 -08";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_4) {
  char format[] = "%2li %2li %2li";
  char str[] = "013 +0137 -08";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_5) {
  char format[] = "%3li %3li %3li";
  char str[] = "013 +0137 -08";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_6) {
  char format[] = "%30li %24li %21li";
  char str[] = "013 +0137 -08";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_7) {
  char format[] = "%li %li %li %li";
  char str[] = "037777777777 +040000000000 -040000000000 -040000000001";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_oct_8) {
  char format[] = "%li %li %li %li";
  char str[] =
      "01777777777777777777777 +02000000000000000000000 "
      "-02000000000000000000000 -02000000000000000000001";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_hex_1) {
  char format[] = "%li%li%li";
  char str[] = "0x123 +0X198 -0x87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_hex_2) {
  char format[] = "%li %li %li";
  char str[] = "0X123 +0x198 -0X87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_hex_3) {
  char format[] = "%1li %1li %1li";
  char str[] = "0X13 +0x137 -0x8";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_hex_5) {
  char format[] = "%3li %3li %3li";
  char str[] = "0x13 +0x137 -0x8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_hex_6) {
  char format[] = "%30li %24li %21li";
  char str[] = "0x13 +0x1a -0x8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_hex_7) {
  char format[] = "%li %li %li %li";
  char str[] = "0xffffffff +0xffffffeab -0xFfFfffFf -0x39cdb3aa";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_li_hex_8) {
  char format[] = "%li %li %li %li";
  char str[] =
      "0xFFFFFFFFFFFFFFFF 0x8000000000000000 -0xFFFFFFFFFFFFFFFF "
      "-0x348923848239742389328";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_n_1) {
  int result = 0, expected = 0;

  int16_t num_result = s21_sscanf("Kiryusha", "%n", &result);
  int16_t num_expected = sscanf("Kiryusha", "%n", &expected);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_n_2) {
  int d1 = 0, d2 = 0;
  int n1 = 0, n2 = 0;

  int16_t num_expected = s21_sscanf("80 Kiryusha", "%d %n", &d1, &n1);
  int16_t num_result = sscanf("80 Kiryusha", "%d %n", &d2, &n2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_n_3) {
  int d1 = 0, d2 = 0;
  int dd1 = 0, dd2 = 0;
  int f1 = 0, f2 = 0;
  int ff1 = 0, ff2 = 0;
  int k1 = 0, k2 = 0;
  int n1 = 0, n2 = 0;

  int16_t num_result = s21_sscanf("80 50 70 371 327", "%d %d %n %d %d %d", &d1,
                                  &dd1, &n1, &f1, &ff1, &k1);
  int16_t num_expected = sscanf("80 50 70 371 327", "%d %d %n %d %d %d", &d2,
                                &dd2, &n2, &f2, &ff2, &k2);

  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(dd1, dd2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(ff1, ff2);
  ck_assert_int_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_n_4) {
  int n1 = 0, n2 = 0;

  int16_t num_result = s21_sscanf("Hello", "Hello %n ", &n1);
  int16_t num_expected = sscanf("Hello", "Hello %n ", &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_n_5) {
  int d1 = 0, d2 = 0;
  int dd1 = 0, dd2 = 0;
  int f1 = 0, f2 = 0;
  int ff1 = 0, ff2 = 0;
  int k1 = 0, k2 = 0;
  short hn1 = 0, hn2 = 0;
  short hhn1 = 0, hhn2 = 0;
  short n1 = 0, n2 = 0;

  int16_t num_result =
      s21_sscanf("80 50 70 371 327", "%d %hn %d %hn %d %d %hn %d", &d1, &hn1,
                 &dd1, &hhn1, &f1, &ff1, &n1, &k1);
  int16_t num_expected =
      sscanf("80 50 70 371 327", "%d %hn %d %hn %d %d %hn %d", &d2, &hn2, &dd2,
             &hhn2, &f2, &ff2, &n2, &k2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(dd1, dd2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(ff1, ff2);
  ck_assert_int_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(hn1, hn2);
  ck_assert_int_eq(hhn1, hhn2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_n_6) {
  int d1 = 0, d2 = 0;
  int dd1 = 0, dd2 = 0;
  int f1 = 0, f2 = 0;
  int ff1 = 0, ff2 = 0;
  int k1 = 0, k2 = 0;
  long int hn1 = 0, hn2 = 0;
  long int hhn1 = 0, hhn2 = 0;
  long int n1 = 0, n2 = 0;

  int16_t num_expected =
      s21_sscanf("3263 225 724 38 482", "%d %ln %d %ln %d %d %ln %d", &d1, &hn1,
                 &dd1, &hhn1, &f1, &ff1, &n1, &k1);
  int16_t num_result =
      sscanf("3263 225 724 38 482", "%d %ln %d %ln %d %d %ln %d", &d2, &hn2,
             &dd2, &hhn2, &f2, &ff2, &n2, &k2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(dd1, dd2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(ff1, ff2);
  ck_assert_int_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(hn1, hn2);
  ck_assert_int_eq(hhn1, hhn2);
  ck_assert_int_eq(num_expected, num_result);
}
END_TEST

START_TEST(sscanf_spec_n_7) {
  char format[] = "%%%c";
  char str[] = "%p";
  char d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_n_8) {
  char s1[30], s2[30], s3[30], s4[30], s5[30], s6[30], s7[30], s8[30], s9[30],
      s10[30];
  int n1 = 0, n2 = 0;
  int hn1 = 0, hn2 = 0;
  int hhn1 = 0, hhn2 = 0;

  int16_t num_expected =
      s21_sscanf("Hello, my name is Jinny", "%s %n %s %n %s %s %s %n", s1, &hn1,
                 s3, &hhn1, s5, s7, s9, &n1);
  int16_t num_result =
      sscanf("Hello, my name is Jinny", "%s %n %s %n %s %s %s %n", s2, &hn2, s4,
             &hhn2, s6, s8, s10, &n2);
  ck_assert_pstr_eq(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  ck_assert_pstr_eq(s5, s6);
  ck_assert_pstr_eq(s7, s8);
  ck_assert_pstr_eq(s9, s10);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(hn1, hn2);
  ck_assert_int_eq(hhn1, hhn2);
  ck_assert_int_eq(num_expected, num_result);
}
END_TEST

START_TEST(sscanf_spec_n_9) {
  char format[] = "%lf %lf %lf %lf %n %lf";
  char str[] = ".0 66.34 9877.66 1.99 0.999";
  long double d1 = 0, d2 = 0;
  long double dd1 = 0, dd2 = 0;
  long double f1 = 0, f2 = 0;
  long double ff1 = 0, ff2 = 0;
  long double k1 = 0, k2 = 0;
  int n1 = 0, n2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &dd1, &f1, &ff1, &n1, &k1);
  int16_t num_expected = sscanf(str, format, &d2, &dd2, &f2, &ff2, &n2, &k2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(dd1, dd2);
  ck_assert_ldouble_eq(f1, f2);
  ck_assert_ldouble_eq(ff1, ff2);
  ck_assert_ldouble_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
  ck_assert_ldouble_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_n_10) {
  char format[] = "%s %s";
  char str[] = "hi \t\n";
  char s1[20], s2[20] = {0}, s3[20], s4[20] = {0};

  int16_t res1 = s21_sscanf(str, format, s1, s2);
  int16_t res2 = sscanf(str, format, s3, s4);
  ck_assert_ldouble_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(sscanf_spec_ho_1) {
  char format[] = "%ho%ho%ho";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_ho_2) {
  char format[] = "%ho%ho%ho";
  char str[] = "123 +1564 -1723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_ho_3) {
  char format[] = "%1ho %1ho %1ho";
  char str[] = "1 +04 -3723";
  unsigned short d1 = 100, d2 = 100;
  unsigned short q1 = 100, q2 = 100;
  unsigned short z1 = 200, z2 = 200;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_ho_4) {
  char format[] = "%2ho %2ho %2ho";
  char str[] = "0123 +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_ho_5) {
  char format[] = "%3ho %3ho %3ho";
  char str[] = "0123 +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_ho_6) {
  char format[] = "%*ho %*ho %*ho";
  char str[] = "0123 +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_o_1) {
  char format[] = "%o%o%o";
  char str[] = "123 +198 -87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_o_2) {
  char format[] = "%o%o%o";
  char str[] = "123 +1564 -1723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_o_3) {
  char format[] = "%1o %1o %1o";
  char str[] = "1 +04 -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_4) {
  char format[] = "%2o %2o %2o";
  char str[] = "0123 +04 -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_5) {
  char format[] = "%3o %3o %3o";
  char str[] = "0123 +04 -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_6) {
  char format[] = "%*o %*o %*o";
  char str[] = "0123 +04 -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_1) {
  char format[] = "%lo%lo%lo";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_2) {
  char format[] = "%lo%lo%lo";
  char str[] = "123 +1564 -1723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_3) {
  char format[] = "%1lo %1lo %1lo";
  char str[] = "1 +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_4) {
  char format[] = "%2lo %2lo %2lo";
  char str[] = "0123 +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_5) {
  char format[] = "%3lo %3lo %3lo";
  char str[] = "0123 +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_6) {
  char format[] = "%*lo %*lo %*lo";
  char str[] = "0123 +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(num_result, num_expected);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_p_1) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xAAAA", "%p", &p_result);
  int16_t num_expected = sscanf("0xAAAA", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_2) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xAAAA", "%5p", &p_result);
  int16_t num_expected = sscanf("0xAAAA", "%5p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_3) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xFFFFFF", "%p", &p_result);
  int16_t num_expected = sscanf("0xFFFFFF", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_4) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0x0000", "%p", &p_result);
  int16_t num_expected = sscanf("0x0000", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_5) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xA2361598", "%p", &p_result);
  int16_t num_expected = sscanf("0xA2361598", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_6) {
  char format[] = "%p";
  char str[] = "0x34567hjk";
  int *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf(str, format, &p_result);
  int16_t num_expected = sscanf(str, format, &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_7) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0x34567hjk678", "%p", &p_result);
  int16_t num_expected = sscanf("0x34567hjk678", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_8) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0x34ABcd68", "%p", &p_result);
  int16_t num_expected = sscanf("0x34ABcd68", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_9) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("1234567890ABCDEF", "%p", &p_result);
  int16_t num_expected = sscanf("1234567890ABCDEF", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_10) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0x237481", "%5p", &p_result);
  int16_t num_expected = sscanf("0x237481", "%5p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_11) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xdksajh", "%6p", &p_result);
  int16_t num_expected = sscanf("0xdksajh", "%6p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_12) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xAGAGUIY", "%6p", &p_result);
  int16_t num_expected = sscanf("0xAGAGUIY", "%6p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_13) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xAGAGUIYUYGFSV", "%p", &p_result);
  int16_t num_expected = sscanf("0xAGAGUIYUYGFSV", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_14) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xAA64BB", "%p", &p_result);
  int16_t num_expected = sscanf("0xAA64BB", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_p_15) {
  void *p_result = 0, *p_expected = 0;

  int16_t num_result = s21_sscanf("0xGGH7TY", "%p", &p_result);
  int16_t num_expected = sscanf("0xGGH7TY", "%p", &p_expected);
  ck_assert_ptr_eq(p_result, p_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_1) {
  char format[] = "%f %f %f";
  char str[] = "123 +198 -87";
  float d1, d2;
  float q1, q2;
  float z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_real_2) {
  char format[] = "%fg %f w%fx";
  char str[] = "75g +19.8w -87.x";
  float d1, d2;
  float q1, q2;
  float z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_real_3) {
  float d1, d2;
  float q1, q2;
  float z1, z2;
  float w1, w2;
  int16_t num_result =
      s21_sscanf("NAN nan -INF +inf", "%f %f %f %f", &d1, &q1, &z1, &w1);
  int16_t num_expected =
      sscanf("NAN nan -INF +inf", "%f %f %f %f", &d2, &q2, &z2, &w2);
  ck_assert_float_nan(d1);
  ck_assert_float_nan(d2);
  ck_assert_float_nan(q1);
  ck_assert_float_nan(q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_4) {
  float d1 = 0, d2 = 0;

  int16_t num_result = s21_sscanf("Nap", "%f", &d1);
  int16_t num_expected = sscanf("Nap", "%f", &d2);
  ck_assert_float_eq(d1, d2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_5) {
  float d1 = 0, d2 = 0;

  int16_t num_result = s21_sscanf("Np", "%f", &d1);
  int16_t num_expected = sscanf("Np", "%f", &d2);
  ck_assert_float_eq(d1, d2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_6) {
  float d1 = 0, d2 = 0;

  int16_t num_result = s21_sscanf("iNd", "%f", &d1);
  int16_t num_expected = sscanf("iNd", "%f", &d2);

  ck_assert_float_eq(d1, d2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_7) {
  float d1 = 0, d2 = 0;

  int16_t num_result = s21_sscanf("id", "%f", &d1);
  int16_t num_expected = sscanf("id", "%f", &d2);
  ck_assert_float_eq(d1, d2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_8) {
  char format[] = "%Lf %f %f %f";
  char str[] = "34.56e3 83.2e-4 .43e+1 +2.43e3";
  long double d1, d2;
  float q1, q2;
  float z1, z2;
  float w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_real_9) {
  float d1, d2;
  float q1, q2;
  float z1, z2;
  float w1 = 0, w2 = 0;

  int16_t num_result = s21_sscanf("34.5+6e3 83.2e-4 .43e+1 +2.43e3",
                                  "%1f %1f %2f %1f", &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf("34.5+6e3 83.2e-4 .43e+1 +2.43e3",
                                "%1f %1f %2f %1f", &d2, &q2, &z2, &w2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_10) {
  char format[] = "%*f %7f %*f %*f";
  char str[] = "34.5+6e3 83.2e-4 +43e+1 +2.43e3";
  float d1, d2;
  float q1 = 0, q2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1);
  int16_t res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_real_11) {
  char format[] = "%fr %7f p";
  char str[] = "34.5r 83.2ep4";
  float d1, d2;
  float q1 = 0, q2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1);
  int16_t res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_real_12) {
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int16_t num_result = s21_sscanf("34 32. +45.e +23E3 -0.3e4",
                                  "%1f %1f %1f %1f", &d1, &q1, &z1, &w1);
  int16_t num_expected = sscanf("34 32. +45.e +23E3 -0.3e4", "%1f %1f %1f %1f",
                                &d2, &q2, &z2, &w2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_13) {
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int16_t num_result = s21_sscanf("34 3. +45.e +23E3 -0.3e4", "%2f %2f %2f %2f",
                                  &d1, &q1, &z1, &w1);
  int16_t num_expected =
      sscanf("34 3. +45.e +23E3 -0.3e4", "%2f %2f %2f %2f", &d2, &q2, &z2, &w2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_14) {
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 100, z2 = 100;
  float w1 = 100, w2 = 100;

  int16_t num_result = s21_sscanf("34 3. +45.e +23E3 -0.3e4", "%3f %3f %4f %3f",
                                  &d1, &q1, &z1, &w1);
  int16_t num_expected =
      sscanf("34 3. +45.e +23E3 -0.3e4", "%3f %3f %4f %3f", &d2, &q2, &z2, &w2);

  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_15) {
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int16_t num_result = s21_sscanf("34 3. +45.e +23E3 -0.3e4", "%4f %4f %4f %4f",
                                  &d1, &q1, &z1, &w1);
  int16_t num_expected =
      sscanf("34 3. +45.e +23E3 -0.3e4", "%4f %4f %4f %4f", &d2, &q2, &z2, &w2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_18) {
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int16_t num_result =
      s21_sscanf("1.1 2.x 1.1 2.x 1.1 2.x", "%f %fx %2f1 %2fx %*f %*f", &d1,
                 &q1, &z1, &w1);
  int16_t num_expected = sscanf("1.1 2.x 1.1 2.x 1.1 2.x",
                                "%f %fx %2f1 %2fx %*f %*f", &d2, &q2, &z2, &w2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_real_19) {
  char format[] = "%f %4f %5fq %6f %*f q%*f";
  char str[] = "1.3e1 1.4eq2 1.3e1q 1.4 1.3eq 1.4e2";
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hx_1) {
  char format[] = "%hx%hx%hx";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_2) {
  char format[] = "%hx%hx%hx";
  char str[] = "12a3 +156B4 -17C23";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_3) {
  char format[] = "%hx%hx";
  char str[] = "0 +0x";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1);
  int16_t num_expected = sscanf(str, format, &d2, &q2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_4) {
  char format[] = "%hx%hx%hx";
  char str[] = "0 -0XABC -0X";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_5) {
  char format[] = "%hx%hx%hx";
  char str[] = "0abc4 -0XABC 0x";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_6) {
  char format[] = "%1hx %1hx %1hx";
  char str[] = "1a +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_7) {
  char format[] = "%1hx %1hx %1hx";
  char str[] = "1a 0x -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_8) {
  char format[] = "%2hx %2hx %2hx";
  char str[] = "1a bc 0x -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_9) {
  char format[] = "%2hx %2hx %2hx";
  char str[] = "1a bCc 0x -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_10) {
  char format[] = "%3hx %3hx %3hx";
  char str[] = "0x123 +0X4 -37x23";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_hx_11) {
  char format[] = "%*hx %*hx %*hx";
  char str[] = "0x123 +04 -372f3";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_1) {
  char format[] = "%x%x%x";
  char str[] = "123 +198 -87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_2) {
  char format[] = "%x%x%x";
  char str[] = "12a3 +156B4 -17C23";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_3) {
  char format[] = "%x%x";
  char str[] = "0 +0x";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1);
  int16_t num_expected = sscanf(str, format, &d2, &q2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_4) {
  char format[] = "%x%x%x";
  char str[] = "0 -0XABC -0X";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_5) {
  char format[] = "%x%x%x";
  char str[] = "0abc4 -0XABC 0x";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_6) {
  char format[] = "%1x %1x %1x";
  char str[] = "1a +04 -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_7) {
  char format[] = "%1x %1x %1x";
  char str[] = "1a 0x -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_8) {
  char format[] = "%2x %2x %2x";
  char str[] = "1a bc 0x -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_9) {
  char format[] = "%2x %2x %2x";
  char str[] = "1a bCc 0x -3723";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_10) {
  char format[] = "%3x %3x %3x";
  char str[] = "0x123 +0X4 -37x23";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_x_11) {
  char format[] = "%*x %*x %*x";
  char str[] = "0x123 +04 -372f3";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_1) {
  char format[] = "%lx%lx%lx";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_2) {
  char format[] = "%lx%lx%lx";
  char str[] = "12a3 +156B4 -17C23";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_3) {
  char format[] = "%lx%lx";
  char str[] = "0 +0x";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1);
  int16_t num_expected = sscanf(str, format, &d2, &q2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_4) {
  char format[] = "%lx%lx%lx";
  char str[] = "0 -0XABC -0X";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_5) {
  char format[] = "%lx%lx%lx";
  char str[] = "0abc4 -0XABC 0x";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_6) {
  char format[] = "%1lx %1lx %1lx";
  char str[] = "1a +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_7) {
  char format[] = "%1lx %1lx %1lx";
  char str[] = "1a 0x -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_8) {
  char format[] = "%2lx %2lx %2lx";
  char str[] = "1a bc 0x -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_9) {
  char format[] = "%2lx %2lx %2lx";
  char str[] = "1a bCc 0x -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_10) {
  char format[] = "%3lx %3lx %3lx";
  char str[] = "0x123 +0X4 -37x23";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sscanf_spec_lx_11) {
  char format[] = "%*lx %*lx %*lx";
  char str[] = "0x123 +04 -372f3";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int16_t num_result = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t num_expected = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

Suite *s21_sscanf_tests_suite(void) {
  Suite *s = suite_create("s21_sscanf_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sscanf_integer);
  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_unsign_int);
  tcase_add_test(tc_core, test_sscanf_string);
  tcase_add_test(tc_core, test_sscanf_float);
  tcase_add_test(tc_core, test_sscanf_multiple_values);
  tcase_add_test(tc_core, test_sscanf_ptr);

  tcase_add_test(tc_core, test_sscanf_percent);
  tcase_add_test(tc_core, test_sscanf_hex);
  tcase_add_test(tc_core, test_sscanf_octal);
  tcase_add_test(tc_core, test_sscanf_width);
  tcase_add_test(tc_core, test_sscanf_precision);
  tcase_add_test(tc_core, test_sscanf_length_h);
  tcase_add_test(tc_core, test_sscanf_length_l);
  tcase_add_test(tc_core, test_sscanf_flag_zero);
  tcase_add_test(tc_core, test_sscanf_n);
  // tcase_add_test(tc_core, test_sscanf_brackets);
  // tcase_add_test(tc_core, test_sscanf_neg_brackets);
  // tcase_add_test(tc_core, test_sscanf_star);
  tcase_add_test(tc_core, sscanf_spec_c_2);
  tcase_add_test(tc_core, sscanf_spec_c_4);
  tcase_add_test(tc_core, sscanf_spec_c_5);
  tcase_add_test(tc_core, sscanf_spec_c_6);
  tcase_add_test(tc_core, sscanf_spec_c_7);

  tcase_add_test(tc_core, sscanf_spec_hd_1);
  tcase_add_test(tc_core, sscanf_spec_hd_2);
  tcase_add_test(tc_core, sscanf_spec_hd_3);
  tcase_add_test(tc_core, sscanf_spec_hd_4);
  tcase_add_test(tc_core, sscanf_spec_hd_5);
  tcase_add_test(tc_core, sscanf_spec_hd_6);
  tcase_add_test(tc_core, sscanf_spec_hd_7);
  tcase_add_test(tc_core, sscanf_spec_hd_8);
  tcase_add_test(tc_core, sscanf_spec_hd_9);
  tcase_add_test(tc_core, sscanf_spec_hd_10);
  tcase_add_test(tc_core, sscanf_spec_hd_11);
  tcase_add_test(tc_core, sscanf_spec_hd_12);
  tcase_add_test(tc_core, sscanf_spec_hd_13);
  tcase_add_test(tc_core, sscanf_spec_hd_14);
  tcase_add_test(tc_core, sscanf_spec_hd_15);
  tcase_add_test(tc_core, sscanf_spec_hd_16);
  tcase_add_test(tc_core, sscanf_spec_hd_17);
  tcase_add_test(tc_core, sscanf_spec_hd_18);
  tcase_add_test(tc_core, sscanf_spec_hd_19);
  tcase_add_test(tc_core, sscanf_spec_hd_20);
  tcase_add_test(tc_core, sscanf_spec_hd_21);
  tcase_add_test(tc_core, sscanf_spec_hd_22);
  tcase_add_test(tc_core, sscanf_spec_hd_23);
  tcase_add_test(tc_core, sscanf_spec_hd_24);
  tcase_add_test(tc_core, sscanf_spec_hd_25);

  tcase_add_test(tc_core, sscanf_spec_d_1);
  tcase_add_test(tc_core, sscanf_spec_d_2);
  tcase_add_test(tc_core, sscanf_spec_d_3);
  tcase_add_test(tc_core, sscanf_spec_d_4);
  tcase_add_test(tc_core, sscanf_spec_d_5);
  tcase_add_test(tc_core, sscanf_spec_d_6);
  tcase_add_test(tc_core, sscanf_spec_d_7);
  tcase_add_test(tc_core, sscanf_spec_d_8);
  tcase_add_test(tc_core, sscanf_spec_d_9);
  tcase_add_test(tc_core, sscanf_spec_d_10);
  tcase_add_test(tc_core, sscanf_spec_d_11);
  tcase_add_test(tc_core, sscanf_spec_d_12);
  tcase_add_test(tc_core, sscanf_spec_d_13);
  tcase_add_test(tc_core, sscanf_spec_d_14);
  tcase_add_test(tc_core, sscanf_spec_d_15);
  tcase_add_test(tc_core, sscanf_spec_d_16);
  tcase_add_test(tc_core, sscanf_spec_d_17);
  tcase_add_test(tc_core, sscanf_spec_d_18);
  tcase_add_test(tc_core, sscanf_spec_d_19);
  tcase_add_test(tc_core, sscanf_spec_d_20);
  tcase_add_test(tc_core, sscanf_spec_d_21);
  tcase_add_test(tc_core, sscanf_spec_d_22);
  tcase_add_test(tc_core, sscanf_spec_d_23);
  tcase_add_test(tc_core, sscanf_spec_d_24);
  tcase_add_test(tc_core, sscanf_spec_d_25);

  tcase_add_test(tc_core, sscanf_spec_ld_1);
  tcase_add_test(tc_core, sscanf_spec_ld_2);
  tcase_add_test(tc_core, sscanf_spec_ld_3);
  tcase_add_test(tc_core, sscanf_spec_ld_4);
  tcase_add_test(tc_core, sscanf_spec_ld_5);
  tcase_add_test(tc_core, sscanf_spec_ld_6);
  tcase_add_test(tc_core, sscanf_spec_ld_7);
  tcase_add_test(tc_core, sscanf_spec_ld_8);
  tcase_add_test(tc_core, sscanf_spec_ld_9);
  tcase_add_test(tc_core, sscanf_spec_ld_10);
  tcase_add_test(tc_core, sscanf_spec_ld_11);
  tcase_add_test(tc_core, sscanf_spec_ld_12);
  tcase_add_test(tc_core, sscanf_spec_ld_13);
  tcase_add_test(tc_core, sscanf_spec_ld_14);
  tcase_add_test(tc_core, sscanf_spec_ld_15);
  tcase_add_test(tc_core, sscanf_spec_ld_16);
  tcase_add_test(tc_core, sscanf_spec_ld_17);
  tcase_add_test(tc_core, sscanf_spec_ld_18);
  tcase_add_test(tc_core, sscanf_spec_ld_19);
  tcase_add_test(tc_core, sscanf_spec_ld_20);
  tcase_add_test(tc_core, sscanf_spec_ld_21);
  tcase_add_test(tc_core, sscanf_spec_ld_22);
  tcase_add_test(tc_core, sscanf_spec_ld_23);
  tcase_add_test(tc_core, sscanf_spec_ld_24);
  tcase_add_test(tc_core, sscanf_spec_ld_25);

  tcase_add_test(tc_core, sscanf_empty_1);
  tcase_add_test(tc_core, sscanf_empty_2);
  tcase_add_test(tc_core, sscanf_empty_3);
  tcase_add_test(tc_core, sscanf_empty_4);
  tcase_add_test(tc_core, sscanf_empty_5);
  tcase_add_test(tc_core, sscanf_empty_6);
  tcase_add_test(tc_core, sscanf_empty_7);

  tcase_add_test(tc_core, sscanf_spec_i_dec_1);
  tcase_add_test(tc_core, sscanf_spec_i_dec_2);
  tcase_add_test(tc_core, sscanf_spec_i_dec_3);
  tcase_add_test(tc_core, sscanf_spec_i_dec_4);
  tcase_add_test(tc_core, sscanf_spec_i_dec_5);
  tcase_add_test(tc_core, sscanf_spec_i_dec_6);
  tcase_add_test(tc_core, sscanf_spec_i_dec_7);
  tcase_add_test(tc_core, sscanf_spec_i_dec_8);

  tcase_add_test(tc_core, sscanf_spec_i_oct_1);
  tcase_add_test(tc_core, sscanf_spec_i_oct_2);
  tcase_add_test(tc_core, sscanf_spec_i_oct_3);
  tcase_add_test(tc_core, sscanf_spec_i_oct_4);
  tcase_add_test(tc_core, sscanf_spec_i_oct_5);
  tcase_add_test(tc_core, sscanf_spec_i_oct_6);
  tcase_add_test(tc_core, sscanf_spec_i_oct_7);
  tcase_add_test(tc_core, sscanf_spec_i_oct_8);

  tcase_add_test(tc_core, sscanf_spec_i_hex_1);
  tcase_add_test(tc_core, sscanf_spec_i_hex_2);
  tcase_add_test(tc_core, sscanf_spec_i_hex_3);
  tcase_add_test(tc_core, sscanf_spec_i_hex_5);
  tcase_add_test(tc_core, sscanf_spec_i_hex_6);
  tcase_add_test(tc_core, sscanf_spec_i_hex_7);
  tcase_add_test(tc_core, sscanf_spec_i_hex_8);

  tcase_add_test(tc_core, sscanf_spec_hi_dec_1);
  tcase_add_test(tc_core, sscanf_spec_hi_dec_2);
  tcase_add_test(tc_core, sscanf_spec_hi_dec_3);
  tcase_add_test(tc_core, sscanf_spec_hi_dec_4);
  tcase_add_test(tc_core, sscanf_spec_hi_dec_5);
  tcase_add_test(tc_core, sscanf_spec_hi_dec_6);
  tcase_add_test(tc_core, sscanf_spec_hi_dec_7);
  tcase_add_test(tc_core, sscanf_spec_hi_dec_8);

  tcase_add_test(tc_core, sscanf_spec_hi_oct_1);
  tcase_add_test(tc_core, sscanf_spec_hi_oct_2);
  tcase_add_test(tc_core, sscanf_spec_hi_oct_3);
  tcase_add_test(tc_core, sscanf_spec_hi_oct_4);
  tcase_add_test(tc_core, sscanf_spec_hi_oct_5);
  tcase_add_test(tc_core, sscanf_spec_hi_oct_6);
  tcase_add_test(tc_core, sscanf_spec_hi_oct_7);
  tcase_add_test(tc_core, sscanf_spec_hi_oct_8);

  tcase_add_test(tc_core, sscanf_spec_hi_hex_1);
  tcase_add_test(tc_core, sscanf_spec_hi_hex_2);
  tcase_add_test(tc_core, sscanf_spec_hi_hex_3);
  tcase_add_test(tc_core, sscanf_spec_hi_hex_5);
  tcase_add_test(tc_core, sscanf_spec_hi_hex_6);
  tcase_add_test(tc_core, sscanf_spec_hi_hex_7);
  tcase_add_test(tc_core, sscanf_spec_hi_hex_8);

  tcase_add_test(tc_core, sscanf_spec_li_dec_1);
  tcase_add_test(tc_core, sscanf_spec_li_dec_2);
  tcase_add_test(tc_core, sscanf_spec_li_dec_3);
  tcase_add_test(tc_core, sscanf_spec_li_dec_4);
  tcase_add_test(tc_core, sscanf_spec_li_dec_5);
  tcase_add_test(tc_core, sscanf_spec_li_dec_6);
  tcase_add_test(tc_core, sscanf_spec_li_dec_7);
  tcase_add_test(tc_core, sscanf_spec_li_dec_8);

  tcase_add_test(tc_core, sscanf_spec_li_oct_1);
  tcase_add_test(tc_core, sscanf_spec_li_oct_2);
  tcase_add_test(tc_core, sscanf_spec_li_oct_3);
  tcase_add_test(tc_core, sscanf_spec_li_oct_4);
  tcase_add_test(tc_core, sscanf_spec_li_oct_5);
  tcase_add_test(tc_core, sscanf_spec_li_oct_6);
  tcase_add_test(tc_core, sscanf_spec_li_oct_7);
  tcase_add_test(tc_core, sscanf_spec_li_oct_8);

  tcase_add_test(tc_core, sscanf_spec_li_hex_1);
  tcase_add_test(tc_core, sscanf_spec_li_hex_2);
  tcase_add_test(tc_core, sscanf_spec_li_hex_3);
  tcase_add_test(tc_core, sscanf_spec_li_hex_5);
  tcase_add_test(tc_core, sscanf_spec_li_hex_6);
  tcase_add_test(tc_core, sscanf_spec_li_hex_7);
  tcase_add_test(tc_core, sscanf_spec_li_hex_8);

  tcase_add_test(tc_core, sscanf_spec_n_1);
  tcase_add_test(tc_core, sscanf_spec_n_2);
  tcase_add_test(tc_core, sscanf_spec_n_3);
  tcase_add_test(tc_core, sscanf_spec_n_4);
  tcase_add_test(tc_core, sscanf_spec_n_5);
  tcase_add_test(tc_core, sscanf_spec_n_6);
  tcase_add_test(tc_core, sscanf_spec_n_7);
  tcase_add_test(tc_core, sscanf_spec_n_8);
  tcase_add_test(tc_core, sscanf_spec_n_9);
  tcase_add_test(tc_core, sscanf_spec_n_10);

  tcase_add_test(tc_core, sscanf_spec_ho_1);
  tcase_add_test(tc_core, sscanf_spec_ho_2);
  tcase_add_test(tc_core, sscanf_spec_ho_3);
  tcase_add_test(tc_core, sscanf_spec_ho_4);
  tcase_add_test(tc_core, sscanf_spec_ho_5);
  tcase_add_test(tc_core, sscanf_spec_ho_6);
  tcase_add_test(tc_core, sscanf_spec_o_1);
  tcase_add_test(tc_core, sscanf_spec_o_2);
  tcase_add_test(tc_core, sscanf_spec_o_3);
  tcase_add_test(tc_core, sscanf_spec_o_4);
  tcase_add_test(tc_core, sscanf_spec_o_5);
  tcase_add_test(tc_core, sscanf_spec_o_6);
  tcase_add_test(tc_core, sscanf_spec_lo_1);
  tcase_add_test(tc_core, sscanf_spec_lo_2);
  tcase_add_test(tc_core, sscanf_spec_lo_3);
  tcase_add_test(tc_core, sscanf_spec_lo_4);
  tcase_add_test(tc_core, sscanf_spec_lo_5);
  tcase_add_test(tc_core, sscanf_spec_lo_6);

  tcase_add_test(tc_core, sscanf_spec_p_1);
  tcase_add_test(tc_core, sscanf_spec_p_2);
  tcase_add_test(tc_core, sscanf_spec_p_3);
  tcase_add_test(tc_core, sscanf_spec_p_4);
  tcase_add_test(tc_core, sscanf_spec_p_5);
  tcase_add_test(tc_core, sscanf_spec_p_6);
  tcase_add_test(tc_core, sscanf_spec_p_7);
  tcase_add_test(tc_core, sscanf_spec_p_8);
  tcase_add_test(tc_core, sscanf_spec_p_9);
  tcase_add_test(tc_core, sscanf_spec_p_10);
  tcase_add_test(tc_core, sscanf_spec_p_11);
  tcase_add_test(tc_core, sscanf_spec_p_12);
  tcase_add_test(tc_core, sscanf_spec_p_13);
  tcase_add_test(tc_core, sscanf_spec_p_14);
  tcase_add_test(tc_core, sscanf_spec_p_15);

  tcase_add_test(tc_core, sscanf_spec_real_1);
  tcase_add_test(tc_core, sscanf_spec_real_2);
  tcase_add_test(tc_core, sscanf_spec_real_3);
  tcase_add_test(tc_core, sscanf_spec_real_4);
  tcase_add_test(tc_core, sscanf_spec_real_5);
  tcase_add_test(tc_core, sscanf_spec_real_6);
  tcase_add_test(tc_core, sscanf_spec_real_7);
  tcase_add_test(tc_core, sscanf_spec_real_8);
  tcase_add_test(tc_core, sscanf_spec_real_9);
  tcase_add_test(tc_core, sscanf_spec_real_10);
  tcase_add_test(tc_core, sscanf_spec_real_11);
  tcase_add_test(tc_core, sscanf_spec_real_12);
  tcase_add_test(tc_core, sscanf_spec_real_13);
  tcase_add_test(tc_core, sscanf_spec_real_14);
  tcase_add_test(tc_core, sscanf_spec_real_15);
  tcase_add_test(tc_core, sscanf_spec_real_18);
  tcase_add_test(tc_core, sscanf_spec_real_19);

  tcase_add_test(tc_core, sscanf_spec_hx_1);
  tcase_add_test(tc_core, sscanf_spec_hx_2);
  tcase_add_test(tc_core, sscanf_spec_hx_3);
  tcase_add_test(tc_core, sscanf_spec_hx_4);
  tcase_add_test(tc_core, sscanf_spec_hx_5);
  tcase_add_test(tc_core, sscanf_spec_hx_6);
  tcase_add_test(tc_core, sscanf_spec_hx_7);
  tcase_add_test(tc_core, sscanf_spec_hx_8);
  tcase_add_test(tc_core, sscanf_spec_hx_9);
  tcase_add_test(tc_core, sscanf_spec_hx_10);
  tcase_add_test(tc_core, sscanf_spec_hx_11);
  tcase_add_test(tc_core, sscanf_spec_x_1);
  tcase_add_test(tc_core, sscanf_spec_x_2);
  tcase_add_test(tc_core, sscanf_spec_x_3);
  tcase_add_test(tc_core, sscanf_spec_x_4);
  tcase_add_test(tc_core, sscanf_spec_x_5);
  tcase_add_test(tc_core, sscanf_spec_x_6);
  tcase_add_test(tc_core, sscanf_spec_x_7);
  tcase_add_test(tc_core, sscanf_spec_x_8);
  tcase_add_test(tc_core, sscanf_spec_x_9);
  tcase_add_test(tc_core, sscanf_spec_x_10);
  tcase_add_test(tc_core, sscanf_spec_x_11);
  tcase_add_test(tc_core, sscanf_spec_lx_1);
  tcase_add_test(tc_core, sscanf_spec_lx_2);
  tcase_add_test(tc_core, sscanf_spec_lx_3);
  tcase_add_test(tc_core, sscanf_spec_lx_4);
  tcase_add_test(tc_core, sscanf_spec_lx_5);
  tcase_add_test(tc_core, sscanf_spec_lx_6);
  tcase_add_test(tc_core, sscanf_spec_lx_7);
  tcase_add_test(tc_core, sscanf_spec_lx_8);
  tcase_add_test(tc_core, sscanf_spec_lx_9);
  tcase_add_test(tc_core, sscanf_spec_lx_10);
  tcase_add_test(tc_core, sscanf_spec_lx_11);

  suite_add_tcase(s, tc_core);

  return s;
}