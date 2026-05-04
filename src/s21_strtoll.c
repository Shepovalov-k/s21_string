#include "s21_support_functions.h"

static int s21_is_support_char(int p) {
  return (s21_isdigit(p) || s21_isalpha(p) || p == '-' || p == '+');
}

long long int s21_strtoll(const char *str, char **endptr, int base) {
  const char *p = str;
  long long int result = 0;
  int num_count = 0;
  int sign = 1;
  int flag = 1;
  int sign_written = 0;
  int prefix_written = 0;

  if (s21_is_support_char(*p)) {
    const char *old_p = p;
    p = (p < *endptr) ? s21_scan_sign((char *)p, &sign) : p;
    sign_written = (p != old_p);
    if ((flag = (sign_written || s21_is_support_char(*p)))) {
      old_p = p;
      p = (p < *endptr) ? s21_scan_base_prefix((char *)p, *endptr, &base) : p;
      prefix_written = p - old_p;
      flag = (p < *endptr) && (base != 0);
    }
    num_count += (prefix_written != 0);
    while (*p && flag && p < *endptr) {
      int digit;
      flag = s21_digit_alpha_process(*p, &digit);
      flag = (flag && digit >= base) ? 0 : flag;

      if (flag && (result > (LLONG_MAX - digit) / base ||
                   result < (LLONG_MIN + digit) / base)) {
        flag = 0;
        result = (sign == 1) ? LLONG_MAX : LLONG_MIN;
        num_count++;
        p++;
      }

      if (flag) {
        result = base * result + sign * digit;
        num_count++;
        p++;
      }
    }
    *endptr = (num_count != 0) ? (char *)p : (char *)str;
  } else {
    *endptr = S21_NULL;
  }

  return result;
}