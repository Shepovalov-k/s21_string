#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

// Assuming s21_sprintf is defined elsewhere
int s21_sprintf(char *str, const char *format, ...);

START_TEST(test_sprintf_flag_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  // Test all flags (-, +, space, #, 0)
  result = s21_sprintf(buffer_result, "Flags: [%-10d] [%+d] [% d] [%#x] [%05d]",
                       42, 42, 42, 42, 42);
  expected = sprintf(buffer_expected, "Flags: [%-10d] [%+d] [% d] [%#x] [%05d]",
                     42, 42, 42, 42, 42);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_width_star_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];
  int width = 10;
  int precision = 4;

  // Test width and precision with *
  result = s21_sprintf(buffer_result, "Star: [%*d] [%.*f] [%*.*f]", width, 42,
                       precision, 3.14159, width, precision, 3.14159);
  expected = sprintf(buffer_expected, "Star: [%*d] [%.*f] [%*.*f]", width, 42,
                     precision, 3.14159, width, precision, 3.14159);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_length_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];
  short h = 123;
  long l = 1234567890;
  long double L = 3.14159265358979323846L;

  // Test all length modifiers (h, l, L)
  result = s21_sprintf(buffer_result, "Length: [%hd] [%ld] [%Lf]", h, l, L);
  expected = sprintf(buffer_expected, "Length: [%hd] [%ld] [%Lf]", h, l, L);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

// START_TEST(test_sprintf_n_specifier) {
//   int result, expected;
//   char buffer_result[2024];
//   char buffer_expected[2024];
//   int n_result, n_expected;

//   // Test %n specifier
//   result = s21_sprintf(buffer_result, "Hello world!%n", &n_result);
//   expected = sprintf(buffer_expected, "Hello world!%n", &n_expected);
//   ck_assert_str_eq(buffer_result, buffer_expected);
//   ck_assert_int_eq(result, expected);
//   ck_assert_int_eq(n_result, n_expected);
// }
// END_TEST

START_TEST(test_sprintf_scientific_notation) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];
  double num = 12345.6789;
  // Test scientific notation (e, E, g, G)
  result = s21_sprintf(buffer_result, "Scientific: [%e] [%E] [%g] [%G]", num,
                       num, num, num);
  expected = sprintf(buffer_expected, "Scientific: [%e] [%E] [%g] [%G]", num,
                     num, num, num);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_edge_cases_basic) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  // Test basic edge cases with empty string and null character
  result = s21_sprintf(buffer_result, "Edges: [%d] [%s] [%c]", 0, "", '\0');
  expected = sprintf(buffer_expected, "Edges: [%d] [%s] [%c]", 0, "", '\0');
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

// START_TEST(test_sprintf_edge_cases_max_width_precision) {
//   char result[10000];
//   char expected[10000];

//   // Test extreme width and precision values
//   int num_result = s21_sprintf(result, "Max: [%1000d] [%.1000f]",
//   42, 3.14159); int num_expected = sprintf(expected, "Max: [%1000d]
//   [%.1000f]", 42, 3.14159); ck_assert(memcmp(result, expected, num_expected)
//   == 0); ck_assert_int_eq(num_result, num_expected);
// }
// END_TEST

START_TEST(test_sprintf_integer_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "Numbers: [%-5.4d]", -243);
  expected = sprintf(buffer_expected, "Numbers: [%-5.4d]", -243);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);

  result = s21_sprintf(buffer_result, "Numbers: [%-5.4u]", -243);
  expected = sprintf(buffer_expected, "Numbers: [%-5.4u]", -243);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);

  result = s21_sprintf(buffer_result, "Numbers: [%-5.9x]", -243);
  expected = sprintf(buffer_expected, "Numbers: [%-5.9x]", -243);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_string_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "Hello %s!", "World");
  expected = sprintf(buffer_expected, "Hello %s!", "World");
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_string_formatting_precision) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "%.3s", "World");
  expected = sprintf(buffer_expected, "%.3s", "World");
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_floating_point_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "Pi is approximately %.2f", 3.14159);
  expected = sprintf(buffer_expected, "Pi is approximately %.2f", 3.14159);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_multiple_format_specifiers) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result =
      s21_sprintf(buffer_result, "Hello %s, your score is %d", "Alice", 95);
  expected =
      sprintf(buffer_expected, "Hello %s, your score is %d", "Alice", 95);
  ck_assert_int_eq(result, expected);
  ck_assert_str_eq(buffer_result, buffer_expected);
}
END_TEST

START_TEST(test_sprintf_hex_octal_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "Numbers: [%x] [%X] [%o]", 243, 243, 243);
  expected = sprintf(buffer_expected, "Numbers: [%x] [%X] [%o]", 243, 243, 243);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_pointer_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];
  int d = 100;

  result = s21_sprintf(buffer_result, "Numbers: [%04d] [%p] test 2", 123,
                       (void *)&d);
  expected =
      sprintf(buffer_expected, "Numbers: [%04d] [%p] test 2", 123, (void *)&d);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_long_double_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];
  long double pi = 3.14159;

  result = s21_sprintf(buffer_result, "Numbers: [%Lf] [%Le]", pi, pi);
  expected = sprintf(buffer_expected, "Numbers: [%Lf] [%Le]", pi, pi);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_char_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "Chars: [%c] [%c]", 's', 120);
  expected = sprintf(buffer_expected, "Chars: [%c] [%c]", 's', 120);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_unsigned_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "Numbers: [%u] [%lu]", 42, 10000000000UL);
  expected = sprintf(buffer_expected, "Numbers: [%u] [%lu]", 42, 10000000000UL);
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_sprintf_percent_formatting) {
  int result, expected;
  char buffer_result[2024];
  char buffer_expected[2024];

  result = s21_sprintf(buffer_result, "percents: [%%]");
  expected = sprintf(buffer_expected, "percents: [%%]");
  ck_assert_str_eq(buffer_result, buffer_expected);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_1_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = 76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = -76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%25.18g TEST\n%.6g TEST\n";
  double num = 838.65400000;
  double num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%.2g TEST\n%.3g TEST\n";
  double num = 838.65400000;
  double num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %#5.10g!";
  double num = 0.0000756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %#5.10g!";
  double num = -0.0000756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = 573429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.0g TEST %4.2g TEST %4.g TEST %5.10g!";
  double num = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_g) {
  char str1[200];
  char str2[200];
  char *str3 = "test:%15.1g|%16.2g|%18.3g!";
  double num = -57251397732103429.56589367;
  int result = s21_sprintf(str1, str3, num, num, num);
  int expected = sprintf(str2, str3, num, num, num);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_10_g) {
  char str1[200];
  char str2[200];
  char *str3 = "test: %10.4g\ntest: %25.5g!";
  double num = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test:%-#15.g|%-26.1g|%-18.0g!";
  double num = -7648938790.756589;
  int result = s21_sprintf(str1, str3, num, num, num);
  int expected = sprintf(str2, str3, num, num, num);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_12_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %#-10.g\ntest: %-+25.g!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%5.10g!";
  double num = -0.0000756589367;
  int result = s21_sprintf(str1, str3, num);
  int expected = sprintf(str2, str3, num);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_14_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = 573429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_g) {
  char str1[400];
  char str2[400];
  char *str3 = "%Lg\n%.Lg!";
  long double num_long = -76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num_long, num_long),
                   s21_sprintf(str2, str3, num_long, num_long));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test:%20.10g|%20.15g|%-20.5g!";
  double num = -76.756589;
  int result = s21_sprintf(str1, str3, num, num, num);
  int expected = sprintf(str2, str3, num, num, num);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_17_g) {
  char str1[400];
  char str2[400];
  char *str3 = "%Lg\n%.Lg\n%+-#Lg\n%+#.Lg\n%-#.Lg!";
  long double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.13g!\ntest: %26.15g!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_19_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %18.7g!\ntest: %10.15g!\ntest: %25.15g!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_20_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.13g!\ntest: %26.15g!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_21_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %18.7g!\ntest: %10.15g!\ntest: %25.15g!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_22_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %020g!\ntest: %-020g!\ntest: %+025g!";
  double num = 837564.4753366;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_23_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-+ 025.5g!\ntest: %- 020.4g!";
  double num = 837564.4753366;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_24_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %020g!\ntest: %-020g!\ntest: %+025g!";
  double num = -837564.4753366;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_25_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-+ 025.5g!\ntest: %- 020.4g!";
  double num = -837564.4753366;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_26_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %015g!\ntest: %-026g!\ntest: %+018g!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_27_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 010.2g!\ntest: %- 025.7g!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_28_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15.1Lg!\ntest: % -26.15Lg!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_29_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %- 30.15Lg!\ntest: %+ 50.15Lg!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_30_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % +40.15Lg\ntest: % +-25.15Lg!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_31_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15.1Lg!\ntest: % -26.15Lg!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_32_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %- 30.13Lg!\ntest: %+ 50.15Lg!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_33_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % +40.15Lg!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str1, str3, num), s21_sprintf(str2, str3, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_34_g) {
  char result[400];
  char expected[400];
  long double num = 9999.999999;
  int num_result =
      s21_sprintf(result, "test:%.1Lg|%.2Lg|%.3Lg!", num, num, num);
  int num_expected =
      sprintf(expected, "test:%.1Lg|%.2Lg|%.3Lg!", num, num, num);
  ck_assert_pstr_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sprintf_35_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test:%.6Lg!";
  long double num = 9999.999999;
  int result = s21_sprintf(str1, str3, num);
  int expected = sprintf(str2, str3, num);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_36_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test:%.g|%.2g|%.3g!";
  double num = 0;
  int result = s21_sprintf(str1, str3, num, num, num);
  int expected = sprintf(str2, str3, num, num, num);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_37_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.10g!\ntest: %.6g!\ntest: %.g!";
  double num = 0;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_38_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-20.13g!\ntest: %-25.7g!";
  double num = -4353.235300;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_39_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-.15g!\ntest: %-16g!\ntest: %- 13.5g!";
  double num = -4353.235300;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_40_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test:%20.13g|%25.7g!";
  double num = 0.00000235300;
  int result = s21_sprintf(str1, str3, num, num);
  int expected = sprintf(str2, str3, num, num);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(sprintf_41_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+.15g!\ntest: %+16g!\ntest: %+ 13.5g!";
  double num = 0.00000235300;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_42_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.Lg!\ntest: %.2Lg!\ntest: %.3Lg!";
  long double num = 8236310759735201795485858585858447757573.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_43_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.12Lg!\ntest: %.6Lg!\ntest: %.9Lg!";
  long double num = 8236310759735201795485858585858447757573.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_44_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %Lg!\n";
  long double num = INFINITY;
  ck_assert_int_eq(sprintf(str1, str3, num), s21_sprintf(str2, str3, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_45_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %Lg!\ntest: %Lg!\n";
  long double num = NAN;
  long double num1 = 1.;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_46_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.5Lg\n";
  long double num1 = 1.;
  ck_assert_int_eq(sprintf(str1, str3, num1), s21_sprintf(str2, str3, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// One parameter hex
START_TEST(sprintf_1_hex) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %x Test";
  int val = 0x32;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three hex parameters
START_TEST(sprintf_2_hex) {
  char str1[100];
  char str2[100];
  char *str3 = "%x Test %x Test %x";
  int val = 0x7a4;
  int val2 = 0x91ba123f;
  int val3 = 0x3123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_hex) {
  char str1[100];
  char str2[100];
  char *str3 = "%x Test %x Test %x";
  int val = 0x3015;
  int val2 = 0x712;
  int val3 = 0x99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_4_hex) {
  char str1[100];
  char str2[100];
  char *str3 = "%lx Test %lx Test %hx GOD %hx";
  long int val = 3088675747373646;
  long val2 = 33030030303;
  unsigned short int val3 = 22600;
  unsigned short val4 = 120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_hex) {
  char str1[100];
  char str2[100];
  char *str3 = "%3x Test %5x Test %10x";
  int val = 3015;
  int val2 = 01234;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5x Test %.23x Test %3.x TEST %.x";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 38;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5x Test %-.8x Test %-7x TEST %-.x";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeroes
START_TEST(sprintf_8_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%0x Test %0.x Test %0.0x TEST %0x GOD %.x";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  int val5 = 0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Pluses
START_TEST(sprintf_9_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%+x Test %+3.x Test %+5.7x TEST %+10x";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// One parameter octal
START_TEST(sprintf_1_octal) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %o Test";
  int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three octal parameters
START_TEST(sprintf_2_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%o Test %o Test %o";
  int val = 012;
  int val2 = 017;
  int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%o Test %o Test %o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_4_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%lo Test %lo Test %ho GOD %ho";
  long int val = 3088675747373646;
  unsigned long int val2 = 33030030303;
  unsigned short int val3 = 22600;
  unsigned short val4 = 120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%3o Test %5o Test %10o";
  int val = 3015;
  int val2 = 01234;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5o|%.23o|%3.o|%.o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 38;
  int result = s21_sprintf(str1, str3, val, val2, val3, val4);
  int expected = sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5o Test %-.8o Test %-7o TEST %-.o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeroes
START_TEST(sprintf_8_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%0o Test %0.o Test %0.0o TEST %0o GOD %.o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  int val5 = 0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Pluses
START_TEST(sprintf_9_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%+o Test %+3.o Test %+5.7o TEST %+10o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zero vals
START_TEST(sprintf_10_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "1:%o|2:%3.o|4:%5.7o|5:%10o|6:%#o|7:%-o|8:%+o|9:%.o|10:% .o";
  int val = 0;
  int result =
      s21_sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  int expected =
      sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Spaces
START_TEST(sprintf_11_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "% o|% 3.o|% 5.7o|% 10o|%.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 23;
  int result = s21_sprintf(str1, str3, val, val2, val3, val4, val5);
  int expected = sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Plus
START_TEST(sprintf_12_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%+o Test %+3.o Test %+5.7o TEST %+10o GOD %+.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 3261;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Hash
START_TEST(sprintf_13_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "1:%#o|2:%#3o|3:%#5.7o|4:%#.7o|5:%#.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 8894;
  int result = s21_sprintf(str1, str3, val, val2, val3, val4, val5);
  int expected = sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// "1:040|2:021303|3:00263416|4:00077067|5:021276"
// "1:040|2:021303|3:0263416|4:0077067|5:021276"

// ZERO flag
START_TEST(sprintf_14_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%0o Test %06o Test %05.7o TEST %0.7o Oof %0.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Asterisk
START_TEST(sprintf_15_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%*o Test %-*o Test %*.*o TEST %.*o";
  int val = 32;
  int val2 = 8899;
  int val3 = 919;
  int val4 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Simple extra test
START_TEST(sprintf_16_octal) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%o";
  int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%- o Test %- 15o sdasda %- 15o sdsad %- o";
  int val = -3231;
  int val2 = -3231;
  int val3 = 3231;
  int val4 = 3231;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "fdsdsds %lo";
  long int val = ULONG_MAX;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "%Lf\n%.Lf!";
  long double num_long = -76.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num_long, num_long),
                   s21_sprintf(str_expected, str3, num_long, num_long));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_4_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "%20.10f\n%20.15f\n%-20.5f!";
  double num = -76.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_5_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "%Lf\n%.Lf\n%+-#Lf\n%+#.Lf\n%-#.Lf!";
  long double num = 76.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_6_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %5f\ntest: %6.1f\ntest: %8.2f!";
  double num = 76.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_7_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %10.5f\ntest: %12.4f!";
  double num = 76.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_8_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %15.1f\ntest: %16.2f\ntest: %18.3f!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_9_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %10.4f\ntest: %25.5f!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_10_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+15.f\ntest: %+#16.f\ntest: %+#18.0f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_11_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+ 18.0f\ntest: %+10.f\ntest: %+25.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_12_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %-26.1f\ntest: %-18.0f\ntest: %#-10.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_13_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %-#15.f\ntest: %-+25.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_14_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %-15.4f!\ntest: %-26.1f!\ntest: %-18.0f!";
  double num = -365289.3462865487;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_15_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %#-10.9f!\ntest: %-+25.15f!";
  double num = -365289.3462865487;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_16_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %15.13f!\ntest: %26.15f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_17_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %18.7f!\ntest: %10.15f!\ntest: %25.15f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_18_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %15.13f!\ntest: %26.15f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_19_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %18.7f!\ntest: %10.15f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_20_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %- 23.14f!\ntest: %+ 25.15f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_21_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: % 15f!\ntest: % -26f!\ntest: %- 18f!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_22_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+- 14f!\ntest: %+ 10f!\ntest: % +25f!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_23_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: % 14f!\ntest: % -27f!\ntest: %- 19f!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_24_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+- 16f!\ntest: %+ 44f!\ntest: % +35f!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_25_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %26Lf!\ntest: %18Lf!\ntest: %60Lf!";
  long double num = -3752765839673496.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_26_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %15Lf!test: %100Lf!";
  long double num = -3752765839673496.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_27_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %- 26Lf!\ntest: %+- 18Lf!\ntest: %60Lf!";
  long double num = 3752765839673496.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_28_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: % +15Lf!test: %100Lf!";
  long double num = 3752765839673496.34;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_30_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %020f!\ntest: %-020f!\ntest: %+025f!";
  double num = 837564.4753366;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_31_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %-+ 025.5f!\ntest: %- 020.4f\ntest: %+ 016.6f!";
  double num = 837564.4753366;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_32_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %015f!\ntest: %-026f!\ntest: %+018f!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_33_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+- 010.2f!\ntest: %- 025.7f\ntest: %+- 18.4f!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_34_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: % 15.1Lf!\ntest: % -26.15Lf!\ntest: %- 30.15Lf!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_35_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+ 50.15Lf!\ntest: % +40.15Lf!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_36_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: % 15.1Lf!\ntest: % -26.13Lf!\ntest: %- 30.8Lf!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_37_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+ 50.14Lf!\ntest: % +40.14Lf!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str_result, str3, num, num),
                   s21_sprintf(str_expected, str3, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_38_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test:%.1Lf|%.2Lf|%.3Lf!";
  long double num = -9999.999999999999999999999999999999999999999999L;
  int num_result = s21_sprintf(str_result, str3, num, num, num);
  int num_expected = sprintf(str_expected, str3, num, num, num);
  ck_assert_pstr_eq(str_result, str_expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sprintf_39_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test:%.10Lf|%.6Lf|%.Lf!";
  long double num = -9888.888;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_40_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = 000000000000000.00000000000;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_41_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %.6Lf!\ntest: %.Lf\ntest: %+ 0Lf!!";
  long double num = 000000000000000.00000000000;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_42_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = -635293201236310753.6495633;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_43_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+ 0Lf!\ntest: %.6Lf!\ntest: %.15Lf!";
  long double num = -635293201236310753.6495633;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_44_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = -236310753.6495633;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_45_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test: %+ 0Lf!\ntest: %.6Lf!\ntest: %.15Lf!";
  long double num = -236310753.6495633;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_46_f) {
  char str_result[400];
  char str_expected[400];
  char *str3 = "test:%0Lf!%.20Lf!%.23Lf";
  long double num = -23631075309783.649563313413;
  ck_assert_int_eq(sprintf(str_result, str3, num, num, num),
                   s21_sprintf(str_expected, str3, num, num, num));
  ck_assert_pstr_eq(str_result, str_expected);
}
END_TEST

START_TEST(sprintf_1_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%e Test %5e Test %5.e";
  double num = -764231539.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%e\n%.e\n%4e\n%4.e\n%5.10e!";
  double num = -764231539.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%#e\n%#.e\n%#5.e\n%#.0e\n%#0.0e!";
  double num = -665695342471359.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: %020e\nSecond test: %020.e!";
  double num = -5921563224775967.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Third test: %010e\nForth test: %010.e!";
  double num = -5921563224775967.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Fifth test: %0.0e!";
  double num = -5921563224775967.;
  ck_assert_int_eq(sprintf(str1, str3, num), s21_sprintf(str2, str3, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: %020e\nSecond test: %020.e!";
  double num =
      -5921563224775977777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777776.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Third test: %010e\nForth test: %010.e\nFifth test: %0.0e!";
  double num =
      -5921563224775977777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777776.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: %020e\nSecond test: %020.5e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Third test: %020.4e\nForth test: %020.3e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Fifth test: %020.2e\nSixth test: %020.1e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Seventh test: %020.e\n Eighth test: %020.0e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: % 20e\nSecond test: % 20.5e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Third test: % 20.4e\nForth test: % 20.3e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Fifth test: % 20.2e\nSixth test: % 20.1e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Seventh test: % 20.e\n Eighth test: % 20.0e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: % 31e\nSecond test: % 30.5e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Third test: % 33.4e\nForth test: % 35.3e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_19_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Fifth test: % 36.2e\nSixth test: % 45.1e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_20_e) {
  char str1[300];
  char str2[300];
  char *str3 = "Seventh test: % 64.e\n Eighth test: % 80.0e!";
  double num = -592156322477596.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_21_e) {
  char result[300];
  char expected[300];
  double num1 = -89435776876.;
  double num2 = -894357768.76;
  int num_expected =
      sprintf(expected, "New test: %e\nSecond test: %e!", num1, num2);
  int num_result =
      s21_sprintf(result, "New test: %e\nSecond test: %e!", num1, num2);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sprintf_22_e) {
  char str1[300];
  char str2[300];
  double num3 = -89435.776876;
  double num4 = -0.89435776876;
  char *str3 = "Third test: %e\nForth test: %e\n!";
  ck_assert_int_eq(sprintf(str1, str3, num3, num4),
                   s21_sprintf(str2, str3, num3, num4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_23_e) {
  char str1[300];
  char str2[300];
  double num1 = -.89435776876;
  double num2 = -.00089435776876;
  char *str3 = "New test: %e\nSecond test: %e!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2),
                   s21_sprintf(str2, str3, num1, num2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_24_e) {
  char str1[300];
  char str2[300];
  double num3 = -0.000000089435776876;
  double num4 = -0000000000000.89435776876;
  char *str3 = "Third test: %e\nForth test: %e\n!";
  ck_assert_int_eq(sprintf(str1, str3, num3, num4),
                   s21_sprintf(str2, str3, num3, num4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_25_e) {
  char str1[300];
  char str2[300];
  double num1 = -.89435776876;
  double num2 = -.00089435776876;
  double num3 = -0.000000089435776876;
  double num4 = -0000000000000.89435776876;
  char *str3 = "test: %.E!\ntest: %#E!\ntest: %#.E!\ntest: %0.E!\n";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2, num3, num4),
                   s21_sprintf(str2, str3, num1, num2, num3, num4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_26_e) {
  char str1[300];
  char str2[300];
  double num1 = -.3529373967;
  double num2 = -.0003529373967;
  double num3 = -0.00000003529373967;
  char *str3 = "test: % 013.E\ntest: %#4.9E\ntest: %016.2E!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2, num3),
                   s21_sprintf(str2, str3, num1, num2, num3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_27_e) {
  char str1[300];
  char str2[300];
  double num1 = -.3529373967;
  double num4 = -0000000000000.3529373967;
  char *str3 = "test: %20.E\ntest: %-20.E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num4, num1),
                   s21_sprintf(str2, str3, num4, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_28_e) {
  char str1[300];
  char str2[300];
  double num1 = .3529373967;
  double num2 = .0003529373967;
  double num3 = 0.00000003529373967;
  char *str3 = "test: % 30.1E\ntest: % 30.E\ntest: %030.0E!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2, num3),
                   s21_sprintf(str2, str3, num1, num2, num3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_29_e) {
  char str1[300];
  char str2[300];
  double num1 = .3529373967;
  double num4 = 0000000000000.3529373967;
  char *str3 = "test: %066.E\ntest: %-20.E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num4, num1),
                   s21_sprintf(str2, str3, num4, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_30_e) {
  char str1[300];
  char str2[300];
  double num1 = 53296575676899283734747273752737878257.;
  char *str3 = "test: %- 17.1E\ntest: % -17.1E!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num1),
                   s21_sprintf(str2, str3, num1, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_31_e) {
  char str1[300];
  char str2[300];
  double num2 = -53296575676899283734747273752737878257.;
  char *str3 = "test: %# 10.2E\ntest: % #10.0E\ntest: %010.E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num2, num2, num2),
                   s21_sprintf(str2, str3, num2, num2, num2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_32_e) {
  char str1[600];
  char str2[600];
  double num1 = 1234567890000.0938217586;
  char *str3 = "test: %- 67.1E\ntest: % -67.1E!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num1),
                   s21_sprintf(str2, str3, num1, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_33_e) {
  char str1[600];
  char str2[600];
  double num2 = -.12345678900000938217586;
  char *str3 = "test: %# 100.0E\ntest: % #100.0E\ntest: %0100.E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num2, num2, num2),
                   s21_sprintf(str2, str3, num2, num2, num2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_34_e) {
  char str1[1000];
  char str2[1000];
  double num1 = 1234567890000.0938217586;
  double num2 = -.12345678900000938217586;
  char *str3 = "test: % 070.10E\ntest: % -67.10E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2),
                   s21_sprintf(str2, str3, num1, num2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_35_e) {
  char str1[1000];
  char str2[1000];
  double num1 = -12345678900000938217586.;
  double num2 = .12345678900000938217586;
  char *str3 = "test: % 070.10E\ntest: % -67.10E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2),
                   s21_sprintf(str2, str3, num1, num2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_36_e) {
  char str1[600];
  char str2[600];
  double num1 = 53296575676899283734747273752737878257.;
  char *str3 = "test: % 10.1E\ntest: %- 10.1E!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num1),
                   s21_sprintf(str2, str3, num1, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_37_e) {
  char str1[600];
  char str2[600];
  double num2 = 53296575676899283.734747273752737878257;
  char *str3 = "test: % -10.0E\ntest: %- 10.0E\ntest: % -10.E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num2, num2, num2),
                   s21_sprintf(str2, str3, num2, num2, num2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_38_e) {
  char str1[600];
  char str2[600];
  double num1 = .000000005329657567689928373474727375273787825732159676631957;
  double num2 = 53296575676899283.73474727375273787825732159676631957;
  char *str3 = "test: % 20E\ntest: %-20E\ntest: %+ 020.E\n!";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2, num1),
                   s21_sprintf(str2, str3, num1, num2, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_39_e) {
  char str1[600];
  char str2[600];
  double num3 = 5329657567689928373474727375.273787825732159676631957;
  double num4 = 53296575676899283734747273752737878257.32159676631957;
  char *str3 = "test: %#20.E\ntest: %- 20E!";
  ck_assert_int_eq(sprintf(str1, str3, num3, num4),
                   s21_sprintf(str2, str3, num3, num4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_40_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%.e\n%.2e\n%.5E\n%.9E\n%.13E!";
  double num = -2599999999.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_41_e) {
  char str1[200];
  char str2[200];
  char *str3 = "%.Le\n%.2Le\n%.5Le\n%.9Le\n%.13LE!";
  long double num = -2599999999.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// One parameter pointer
START_TEST(sprintf_1_pointer) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %p Test";
  char *val = "0p32";
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three pointer parameters
START_TEST(sprintf_2_pointer) {
  char str1[100];
  char str2[100];
  char *str3 = "%p Test %p Test %p";
  char *val = "0p7a4";
  char *val2 = "0p91ba123f";
  char *val3 = "0p3123";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_pointer) {
  char str1[100];
  char str2[100];
  char *str3 = "%p Test %p Test %p";
  char *val = "0p3015";
  char *val2 = "0p712";
  char *val3 = "0p99";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_4_pointer) {
  char str1[100];
  char str2[100];
  char *str3 = "%p Test %p Test %p GOD %p";
  long int *val = (void *)3088675747373646;
  long long int *val2 = (void *)33030030303;
  unsigned short int *val3 = (void *)22600;
  unsigned char *val4 = (void *)120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_pointer) {
  char str1[100];
  char str2[100];
  char *str3 = "%3p Test %5p Test %12p";
  char *val = "3015";
  char *val2 = "01234";
  char *val3 = "99";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5p Test %.23p Test %3.p TEST %.p";
  char *val = "3015";
  char *val2 = "712";
  char *val3 = "99";
  char *val4 = "38";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5p Test %-.4p Test %-16p TEST %-.5p";
  char *val = "3015";
  char *val2 = "712";
  char *val3 = "99";
  char *val4 = "2939";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeroes
START_TEST(sprintf_8_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%0p Test %0.p Test %0.0p TEST %0p GOD %.p";
  char *val = "3015";
  char *val2 = "712";
  char *val3 = "99";
  char *val4 = "2939";
  char *val5 = "0123";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Pluses
START_TEST(sprintf_9_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%+p Test %+3.p Test %+5.7p TEST %+10p";
  char *val = "3015";
  char *val2 = "712";
  char *val3 = "99";
  char *val4 = "2939";
  int result = s21_sprintf(str1, str3, val, val2, val3, val4);
  int expected = sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Zero vals
START_TEST(sprintf_10_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%p|%3.p|%5.7p|%10p|%#p|%-p|%+p|%.p|% .p";
  char *val = 0;
  int result =
      s21_sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  int expected =
      sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST
// "0| |0000000|       0|0|0|+0||"
// "(nil)|(nil)|(nil)|     (nil)|(nil)|(nil)|(nil)|(nil)|(nil)"

// Spaces
START_TEST(sprintf_11_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "% p|% 3.p|% 5.7p|% 10p|%.p";
  char *val = "32";
  char *val2 = "8899";
  char *val3 = "91918";
  char *val4 = "32311";
  char *val5 = "23";
  int result = s21_sprintf(str1, str3, val, val2, val3, val4, val5);
  int expected = sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// "0x64724bd8be16|0x64724bd8be19|0x64724bd8be1e|0x64724bd8be24|0x64724bd8be2a"
// " 0x64724bd8be16| 0x64724bd8be19| 0x64724bd8be1e|
// 0x64724bd8be24|0x64724bd8be2a"

// Plus
START_TEST(sprintf_12_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%+p Test %+3.p Test %+5.7p TEST %+10p GOD %+.p";
  char *val = "32";
  char *val2 = "8899";
  char *val3 = "91918";
  char *val4 = "32311";
  char *val5 = "3261";
  int result = s21_sprintf(str1, str3, val, val2, val3, val4, val5);
  int expected = sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Hash
START_TEST(sprintf_13_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%#p Test %#3p Test %#5.7p TEST %#.7p Oof %#.p";
  char *val = "32";
  char *val2 = "8899";
  char *val3 = "91918";
  char *val4 = "32311";
  char *val5 = "8894";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// ZERO flag
START_TEST(sprintf_14_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%0p Test %06p Test %05.7p TEST %0.7p Oof %0.p";
  char *val = "32";
  char *val2 = "8899";
  char *val3 = "91918";
  char *val4 = "32311";
  char *val5 = "8894";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Asterisk
START_TEST(sprintf_15_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%*p Test %-*p Test %*.*p TEST %.*p Lololol %.*p";
  char *val = "32";
  char *val2 = "8899";
  char *val3 = "9193112312312";
  char *val4 = "32311";
  char *val5 = "WTF cmon";
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  int ast6 = 18;
  ck_assert_int_eq(sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3,
                           ast5, val4, ast6, val5),
                   s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4,
                               val3, ast5, val4, ast6, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// One parameter string
START_TEST(sprintf_1_string) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %s Test";
  char *val = "Why am I here?!";
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three string parameters
START_TEST(sprintf_2_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s Test %s Test %s";
  char *val = "I'm so tired";
  char *val2 = "Who invented this?";
  char *val3 = "This project gave me hemmoroids";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s Test %s Test %s";
  char *val = "Don't need this test";
  char *val2 = "Just for the kicks";
  char *val3 = "Lol";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes WCHAR FOR LATER
/*START_TEST(sprintf_4_string_wchar) {
  char result[100];
  char expected[100];
  wchar_t *val = L"3wtf80";
  int num_expected = sprintf(expected, "Test %ls Test2", val);
  int num_result = s21_sprintf(result, "Test %ls Test2", val);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST*/

// Different width
START_TEST(sprintf_5_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%3s Test %5s Test %10s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore";
  char *val3 = "PPAP";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_string) {
  char result[200];
  char expected[200];
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";

  int num_expected = sprintf(expected, "%6.5s Test %.23s Test %3.s TEST %.s",
                             val, val2, val3, val4);
  int num_result = s21_sprintf(result, "%6.5s Test %.23s Test %3.s TEST %.s",
                               val, val2, val3, val4);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_string) {
  char result[200];
  char expected[200];
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  int num_expected = sprintf(expected, "%-10.5s Test %-.8s Test %-7s TEST %-.s",
                             val, val2, val3, val4);
  int num_result = s21_sprintf(result, "%-10.5s Test %-.8s Test %-7s TEST %-.s",
                               val, val2, val3, val4);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

// // Zeroes
// START_TEST(sprintf_8_string) {
//   char result[200];
//   char expected[200];
//   char *val = "WHAT IS THIS";
//   char *val2 = "i don't care anymore, really";
//   char *val3 = "PPAP";
//   char *val4 = "I don't feel so good";
//   char *val5 = "What is lovin'?!";
//   int num_expected = sprintf(expected, "%0s Test %0.s Test %0.0s TEST %0s GOD
//   %.s", val, val2, val3, val4, val5); int num_result = s21_sprintf(result,
//   "%0s Test %0.s Test %0.0s TEST %0s GOD %.s", val, val2, val3, val4, val5);
//   ck_assert_str_eq(result, expected);
//   ck_assert_int_eq(num_result, num_expected);
// }
// END_TEST

// Pluses
START_TEST(sprintf_9_string) {
  char result[200];
  char expected[200];
  char *val3 = "abcd";
  char *val4 = "I don't feel so good";
  int num_expected = sprintf(expected, " Test %5.7s TEST %10s", val3, val4);
  int num_result = s21_sprintf(result, " Test %5.7s TEST %10s", val3, val4);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

// Zero vals
START_TEST(sprintf_10_string) {
  char result[200];
  char expected[200];
  char *val = NULL;
  int num_expected =
      sprintf(expected, "%s Test %3.s Test %5.7s TEST %10s  %-s %.s ", val, val,
              val, val, val, val);
  int num_result =
      s21_sprintf(result, "%s Test %3.s Test %5.7s TEST %10s  %-s %.s ", val,
                  val, val, val, val, val);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

// Spaces
START_TEST(sprintf_11_string) {
  char result[200];
  char expected[200];
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  int num_expected =
      sprintf(expected, " Test %3.s Test %5.7s TEST %10s GOD %.s", val2, val3,
              val4, val5);
  int num_result =
      s21_sprintf(result, " Test %3.s Test %5.7s TEST %10s GOD %.s", val2, val3,
                  val4, val5);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

// Plus
START_TEST(sprintf_12_string) {
  char result[200];
  char expected[200];
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  int num_expected =
      sprintf(expected, "%s Test %3.s Test %5.7s TEST %10s GOD %.s", val, val2,
              val3, val4, val5);
  int num_result =
      s21_sprintf(result, "%s Test %3.s Test %5.7s TEST %10s GOD %.s", val,
                  val2, val3, val4, val5);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

// // Hash
// START_TEST(sprintf_13_string) {
//   char result[200];
//   char expected[200];
//   char *val = "WHAT IS THIS";
//   char *val2 = "i don't care anymore, really";
//   char *val3 = "PPAP";
//   char *val4 = "I don't feel so good";
//   char *val5 = "What is lovin'?!";
//   int num_expected = sprintf(expected, "%#s Test %#3s Test %#5.7s TEST %#.7s
//   Oof %#.s", val, val2, val3, val4, val5); int num_result   =
//   s21_sprintf(result, "%#s Test %#3s Test %#5.7s TEST %#.7s Oof %#.s", val,
//   val2, val3, val4, val5); ck_assert_str_eq(result, expected);
//   ck_assert_int_eq(num_result, num_expected);
// }
// END_TEST

// // ZERO flag
// START_TEST(sprintf_14_string) {
//   char result[200];
//   char expected[200];
//   char *val = "WHAT IS THIS";
//   char *val2 = "idx";
//   char *val3 = "PPAP";
//   char *val4 = "I don't";
//   char *val5 = "What is lovin'?!";
//   int num_expected = sprintf(expected, "%0s Test %06s Test %05.7s TEST %0.7s
//   Oof %0.s", val, val2, val3, val4, val5); int num_result =
//   s21_sprintf(result, "%0s Test %06s Test %05.7s TEST %0.7s Oof %0.s", val,
//   val2, val3, val4, val5); ck_assert_str_eq(result, expected);
//   ck_assert_int_eq(num_result, num_expected);
// }
// END_TEST

// Asterisk
START_TEST(sprintf_15_string) {
  char result[200];
  char expected[200];
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  int num_expected =
      sprintf(expected, "%*s Test %-*s Test %*.*s TEST %.*s", ast, val, ast2,
              val2, ast3, ast4, val3, ast5, val4);
  int num_result =
      s21_sprintf(result, "%*s Test %-*s Test %*.*s TEST %.*s", ast, val, ast2,
                  val2, ast3, ast4, val3, ast5, val4);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num_result, num_expected);
}
END_TEST

START_TEST(sprintf_16_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s %s %s %% %d";
  char *val = "This";
  char *val2 = "\0";
  int val3 = 65;
  char *val4 = "string";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val4, val3),
                   s21_sprintf(str2, str3, val, val2, val4, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// One parameter unsigned
START_TEST(sprintf_1_unsigned) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %u Test";
  unsigned int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three unsigned parameters
START_TEST(sprintf_2_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%u Test %u Test %u";
  unsigned int val = 012;
  unsigned int val2 = 017;
  unsigned int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%u Test %u Test %u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_4_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%lu Test %lu Test %hu GOD %hu";
  long unsigned int val = 3088675747373646;
  long unsigned val2 = 33030030303;
  unsigned short val3 = 22600;
  unsigned short val4 = 120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%3u Test %5u Test %10u";
  unsigned int val = 3015;
  unsigned int val2 = 01234;
  unsigned int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5u Test %.23u Test %3.u TEST %.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 38;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5u Test %-.8u Test %-7u TEST %-.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zerues
START_TEST(sprintf_8_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%0u Test %0.u Test %0.0u TEST %0u GOD %.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  unsigned int val5 = 0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Pluses
START_TEST(sprintf_9_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeru vals
START_TEST(sprintf_10_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%u Test %3.u Test %5.7u TEST %10u %#u %-u %+u %.u % .u";
  unsigned int val = 0;
  sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Spaces
START_TEST(sprintf_11_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "% u Test % 3.u Test % 5.7u TEST % 10u GOD %.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 23;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Plus
START_TEST(sprintf_12_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u GOD %+.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 3261;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Hash
START_TEST(sprintf_13_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%#u|%#3u|%#5.7u|%#.7u|%#.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 8894;
  int result = s21_sprintf(str1, str3, val, val2, val3, val4, val5);
  int expected = sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

// "32|8899|091918|032311|8894"
// "32|8899|0091918|0032311|8894"

// ZERO flag
START_TEST(sprintf_14_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%0u Test %06u Test %05.7u TEST %0.7u Ouf %0.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Asterisk
START_TEST(sprintf_15_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%*u Test %-*u Test %*.*u TEST %.*u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 919;
  unsigned int val4 = 32311;
  unsigned int ast = 2;
  unsigned int ast2 = 5;
  unsigned int ast3 = 4;
  unsigned int ast4 = 10;
  unsigned int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "fdsdsds %lu";
  unsigned long int val = ULONG_MAX;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%- u Test %- 15u sdasda %- 15u sdsad %- u";
  unsigned int val = -3231;
  unsigned int val2 = -3231;
  unsigned int val3 = 3231;
  unsigned int val4 = 3231;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

Suite *s21_sprintf_tests_suite(void) {
  Suite *s = suite_create("s21_sprintf_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sprintf_integer_formatting);
  tcase_add_test(tc_core, test_sprintf_string_formatting);
  tcase_add_test(tc_core, test_sprintf_floating_point_formatting);
  tcase_add_test(tc_core, test_sprintf_multiple_format_specifiers);
  tcase_add_test(tc_core, test_sprintf_hex_octal_formatting);
  tcase_add_test(tc_core, test_sprintf_pointer_formatting);
  tcase_add_test(tc_core, test_sprintf_long_double_formatting);
  tcase_add_test(tc_core, test_sprintf_char_formatting);
  tcase_add_test(tc_core, test_sprintf_unsigned_formatting);
  tcase_add_test(tc_core, test_sprintf_percent_formatting);
  tcase_add_test(tc_core, test_sprintf_integer_formatting);
  tcase_add_test(tc_core, test_sprintf_string_formatting);
  tcase_add_test(tc_core, test_sprintf_string_formatting_precision);
  tcase_add_test(tc_core, test_sprintf_floating_point_formatting);
  tcase_add_test(tc_core, test_sprintf_multiple_format_specifiers);
  tcase_add_test(tc_core, test_sprintf_hex_octal_formatting);
  tcase_add_test(tc_core, test_sprintf_pointer_formatting);
  tcase_add_test(tc_core, test_sprintf_long_double_formatting);
  tcase_add_test(tc_core, test_sprintf_char_formatting);
  tcase_add_test(tc_core, test_sprintf_unsigned_formatting);
  tcase_add_test(tc_core, test_sprintf_percent_formatting);
  tcase_add_test(tc_core, test_sprintf_edge_cases_basic);
  // tcase_add_test(tc_core, test_sprintf_edge_cases_max_width_precision);
  tcase_add_test(tc_core, test_sprintf_scientific_notation);
  // tcase_add_test(tc_core, test_sprintf_n_specifier);
  tcase_add_test(tc_core, test_sprintf_length_formatting);
  tcase_add_test(tc_core, test_sprintf_width_star_formatting);
  tcase_add_test(tc_core, test_sprintf_flag_formatting);
  tcase_add_test(tc_core, sprintf_1_g);
  tcase_add_test(tc_core, sprintf_2_g);
  tcase_add_test(tc_core, sprintf_3_g);
  tcase_add_test(tc_core, sprintf_4_g);
  tcase_add_test(tc_core, sprintf_5_g);
  tcase_add_test(tc_core, sprintf_6_g);
  tcase_add_test(tc_core, sprintf_7_g);
  tcase_add_test(tc_core, sprintf_8_g);
  tcase_add_test(tc_core, sprintf_9_g);
  tcase_add_test(tc_core, sprintf_10_g);
  tcase_add_test(tc_core, sprintf_11_g);
  tcase_add_test(tc_core, sprintf_12_g);
  tcase_add_test(tc_core, sprintf_13_g);
  tcase_add_test(tc_core, sprintf_14_g);
  tcase_add_test(tc_core, sprintf_15_g);
  tcase_add_test(tc_core, sprintf_16_g);
  tcase_add_test(tc_core, sprintf_17_g);
  tcase_add_test(tc_core, sprintf_18_g);
  tcase_add_test(tc_core, sprintf_19_g);
  tcase_add_test(tc_core, sprintf_20_g);
  tcase_add_test(tc_core, sprintf_21_g);
  tcase_add_test(tc_core, sprintf_22_g);
  tcase_add_test(tc_core, sprintf_23_g);
  tcase_add_test(tc_core, sprintf_24_g);
  tcase_add_test(tc_core, sprintf_25_g);
  tcase_add_test(tc_core, sprintf_26_g);
  tcase_add_test(tc_core, sprintf_27_g);
  tcase_add_test(tc_core, sprintf_28_g);
  tcase_add_test(tc_core, sprintf_29_g);
  tcase_add_test(tc_core, sprintf_30_g);
  tcase_add_test(tc_core, sprintf_31_g);
  tcase_add_test(tc_core, sprintf_32_g);
  tcase_add_test(tc_core, sprintf_33_g);
  tcase_add_test(tc_core, sprintf_34_g);
  tcase_add_test(tc_core, sprintf_35_g);
  tcase_add_test(tc_core, sprintf_36_g);
  tcase_add_test(tc_core, sprintf_37_g);
  tcase_add_test(tc_core, sprintf_38_g);
  tcase_add_test(tc_core, sprintf_39_g);
  tcase_add_test(tc_core, sprintf_40_g);
  tcase_add_test(tc_core, sprintf_41_g);
  tcase_add_test(tc_core, sprintf_42_g);
  tcase_add_test(tc_core, sprintf_43_g);
  tcase_add_test(tc_core, sprintf_44_g);
  tcase_add_test(tc_core, sprintf_45_g);
  tcase_add_test(tc_core, sprintf_46_g);
  tcase_add_test(tc_core, sprintf_1_hex);
  tcase_add_test(tc_core, sprintf_2_hex);
  tcase_add_test(tc_core, sprintf_3_hex);
  tcase_add_test(tc_core, sprintf_4_hex);
  tcase_add_test(tc_core, sprintf_5_hex);
  tcase_add_test(tc_core, sprintf_6_hex);
  tcase_add_test(tc_core, sprintf_7_hex);
  tcase_add_test(tc_core, sprintf_8_hex);
  tcase_add_test(tc_core, sprintf_9_hex);
  tcase_add_test(tc_core, sprintf_1_octal);
  tcase_add_test(tc_core, sprintf_2_octal);
  tcase_add_test(tc_core, sprintf_3_octal);
  tcase_add_test(tc_core, sprintf_4_octal);
  tcase_add_test(tc_core, sprintf_5_octal);
  tcase_add_test(tc_core, sprintf_6_octal);
  tcase_add_test(tc_core, sprintf_7_octal);
  tcase_add_test(tc_core, sprintf_8_octal);
  tcase_add_test(tc_core, sprintf_9_octal);
  tcase_add_test(tc_core, sprintf_10_octal);
  tcase_add_test(tc_core, sprintf_11_octal);
  tcase_add_test(tc_core, sprintf_12_octal);
  tcase_add_test(tc_core, sprintf_13_octal);
  tcase_add_test(tc_core, sprintf_14_octal);
  tcase_add_test(tc_core, sprintf_15_octal);
  tcase_add_test(tc_core, sprintf_16_octal);
  tcase_add_test(tc_core, sprintf_17_octal);
  tcase_add_test(tc_core, sprintf_18_octal);
  tcase_add_test(tc_core, sprintf_3_f);
  tcase_add_test(tc_core, sprintf_4_f);
  tcase_add_test(tc_core, sprintf_5_f);
  tcase_add_test(tc_core, sprintf_6_f);
  tcase_add_test(tc_core, sprintf_7_f);
  tcase_add_test(tc_core, sprintf_8_f);
  tcase_add_test(tc_core, sprintf_9_f);
  tcase_add_test(tc_core, sprintf_10_f);
  tcase_add_test(tc_core, sprintf_11_f);
  tcase_add_test(tc_core, sprintf_12_f);
  tcase_add_test(tc_core, sprintf_13_f);
  tcase_add_test(tc_core, sprintf_14_f);
  tcase_add_test(tc_core, sprintf_15_f);
  tcase_add_test(tc_core, sprintf_16_f);
  tcase_add_test(tc_core, sprintf_17_f);
  tcase_add_test(tc_core, sprintf_18_f);
  tcase_add_test(tc_core, sprintf_19_f);
  tcase_add_test(tc_core, sprintf_20_f);
  tcase_add_test(tc_core, sprintf_21_f);
  tcase_add_test(tc_core, sprintf_22_f);
  tcase_add_test(tc_core, sprintf_23_f);
  tcase_add_test(tc_core, sprintf_24_f);
  tcase_add_test(tc_core, sprintf_25_f);
  tcase_add_test(tc_core, sprintf_26_f);
  tcase_add_test(tc_core, sprintf_27_f);
  tcase_add_test(tc_core, sprintf_28_f);
  tcase_add_test(tc_core, sprintf_30_f);
  tcase_add_test(tc_core, sprintf_31_f);
  tcase_add_test(tc_core, sprintf_32_f);
  tcase_add_test(tc_core, sprintf_33_f);
  tcase_add_test(tc_core, sprintf_34_f);
  tcase_add_test(tc_core, sprintf_35_f);
  tcase_add_test(tc_core, sprintf_36_f);
  tcase_add_test(tc_core, sprintf_37_f);
  tcase_add_test(tc_core, sprintf_38_f);
  tcase_add_test(tc_core, sprintf_39_f);
  tcase_add_test(tc_core, sprintf_40_f);
  tcase_add_test(tc_core, sprintf_41_f);
  tcase_add_test(tc_core, sprintf_42_f);
  tcase_add_test(tc_core, sprintf_43_f);
  tcase_add_test(tc_core, sprintf_44_f);
  tcase_add_test(tc_core, sprintf_45_f);
  tcase_add_test(tc_core, sprintf_46_f);
  tcase_add_test(tc_core, sprintf_1_e);
  tcase_add_test(tc_core, sprintf_2_e);
  tcase_add_test(tc_core, sprintf_3_e);
  tcase_add_test(tc_core, sprintf_4_e);
  tcase_add_test(tc_core, sprintf_5_e);
  tcase_add_test(tc_core, sprintf_6_e);
  tcase_add_test(tc_core, sprintf_7_e);
  tcase_add_test(tc_core, sprintf_8_e);
  tcase_add_test(tc_core, sprintf_9_e);
  tcase_add_test(tc_core, sprintf_10_e);
  tcase_add_test(tc_core, sprintf_11_e);
  tcase_add_test(tc_core, sprintf_12_e);
  tcase_add_test(tc_core, sprintf_13_e);
  tcase_add_test(tc_core, sprintf_14_e);
  tcase_add_test(tc_core, sprintf_15_e);
  tcase_add_test(tc_core, sprintf_16_e);
  tcase_add_test(tc_core, sprintf_17_e);
  tcase_add_test(tc_core, sprintf_18_e);
  tcase_add_test(tc_core, sprintf_19_e);
  tcase_add_test(tc_core, sprintf_20_e);
  tcase_add_test(tc_core, sprintf_21_e);
  tcase_add_test(tc_core, sprintf_22_e);
  tcase_add_test(tc_core, sprintf_23_e);
  tcase_add_test(tc_core, sprintf_24_e);
  tcase_add_test(tc_core, sprintf_25_e);
  tcase_add_test(tc_core, sprintf_26_e);
  tcase_add_test(tc_core, sprintf_27_e);
  tcase_add_test(tc_core, sprintf_28_e);
  tcase_add_test(tc_core, sprintf_29_e);
  tcase_add_test(tc_core, sprintf_30_e);
  tcase_add_test(tc_core, sprintf_31_e);
  tcase_add_test(tc_core, sprintf_32_e);
  tcase_add_test(tc_core, sprintf_33_e);
  tcase_add_test(tc_core, sprintf_34_e);
  tcase_add_test(tc_core, sprintf_35_e);
  tcase_add_test(tc_core, sprintf_36_e);
  tcase_add_test(tc_core, sprintf_37_e);
  tcase_add_test(tc_core, sprintf_38_e);
  tcase_add_test(tc_core, sprintf_39_e);
  tcase_add_test(tc_core, sprintf_40_e);
  tcase_add_test(tc_core, sprintf_41_e);
  tcase_add_test(tc_core, sprintf_1_pointer);
  tcase_add_test(tc_core, sprintf_2_pointer);
  tcase_add_test(tc_core, sprintf_3_pointer);
  tcase_add_test(tc_core, sprintf_4_pointer);
  tcase_add_test(tc_core, sprintf_5_pointer);
  tcase_add_test(tc_core, sprintf_6_pointer);
  tcase_add_test(tc_core, sprintf_7_pointer);
  tcase_add_test(tc_core, sprintf_8_pointer);
  tcase_add_test(tc_core, sprintf_9_pointer);
  tcase_add_test(tc_core, sprintf_10_pointer);
  tcase_add_test(tc_core, sprintf_11_pointer);
  tcase_add_test(tc_core, sprintf_12_pointer);
  tcase_add_test(tc_core, sprintf_13_pointer);
  tcase_add_test(tc_core, sprintf_14_pointer);
  tcase_add_test(tc_core, sprintf_15_pointer);
  tcase_add_test(tc_core, sprintf_1_string);
  tcase_add_test(tc_core, sprintf_2_string);
  tcase_add_test(tc_core, sprintf_3_string);
  tcase_add_test(tc_core, sprintf_5_string);
  tcase_add_test(tc_core, sprintf_6_string);
  tcase_add_test(tc_core, sprintf_7_string);
  // tcase_add_test(tc_core, sprintf_8_string);
  tcase_add_test(tc_core, sprintf_9_string);
  tcase_add_test(tc_core, sprintf_10_string);
  tcase_add_test(tc_core, sprintf_11_string);
  tcase_add_test(tc_core, sprintf_12_string);
  // tcase_add_test(tc_core, sprintf_13_string);
  // tcase_add_test(tc_core, sprintf_14_string);
  tcase_add_test(tc_core, sprintf_15_string);
  tcase_add_test(tc_core, sprintf_16_string);
  tcase_add_test(tc_core, sprintf_1_unsigned);
  tcase_add_test(tc_core, sprintf_2_unsigned);
  tcase_add_test(tc_core, sprintf_3_unsigned);
  tcase_add_test(tc_core, sprintf_4_unsigned);
  tcase_add_test(tc_core, sprintf_5_unsigned);
  tcase_add_test(tc_core, sprintf_6_unsigned);
  tcase_add_test(tc_core, sprintf_7_unsigned);
  tcase_add_test(tc_core, sprintf_8_unsigned);
  tcase_add_test(tc_core, sprintf_9_unsigned);
  tcase_add_test(tc_core, sprintf_10_unsigned);
  tcase_add_test(tc_core, sprintf_11_unsigned);
  tcase_add_test(tc_core, sprintf_12_unsigned);
  tcase_add_test(tc_core, sprintf_13_unsigned);
  tcase_add_test(tc_core, sprintf_14_unsigned);
  tcase_add_test(tc_core, sprintf_15_unsigned);
  tcase_add_test(tc_core, sprintf_16_unsigned);
  tcase_add_test(tc_core, sprintf_17_unsigned);

  suite_add_tcase(s, tc_core);

  return s;
}