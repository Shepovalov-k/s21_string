#include "s21_string.h"
#include "s21_support_functions.h"

static int s21_is_support_beginning(int p) {
  return (s21_isdigit(p) || p == '-' || p == '+' || p == 'n' || p == 'N' ||
          p == 'i' || p == 'I' || p == '.');
}

static int s21_is_nan(char *p) {
  return (s21_strncmp(p, "nan", 3) == 0 || s21_strncmp(p, "NAN", 3) == 0);
}

static int s21_is_inf(char *p) {
  return (s21_strncmp(p, "inf", 3) == 0 || s21_strncmp(p, "INF", 3) == 0);
}

double s21_scan_inf_nan(char *p, char **endptr) {
  double result = 0.0;
  if (s21_is_inf(p)) {
    *endptr = (char *)(p + 3);
    result = INFINITY;
  } else if (s21_is_nan(p)) {
    *endptr = (char *)(p + 3);
    result = NAN;
  }
  return result;
}

long double s21_str_to_double(const char *str, char **endptr) {
  long double result = 0.0;
  int sign = 1;
  int exp_sign = 1;
  double fraction = 0.0;
  int exp = 0;
  int inf_nan_written = 0;
  char *p = (char *)str;
  const char *old_p = p;

  if (s21_is_support_beginning(*p)) {
    p = (p < *endptr) ? s21_scan_sign((char *)p, &sign) : p;
    result = (p < *endptr) ? s21_scan_inf_nan(p, endptr) : result;
    inf_nan_written = (isnan(result) || isinf(result));
    old_p = (inf_nan_written) ? old_p : p;
    if ((p < *endptr) && !inf_nan_written) {
      while ((p < *endptr) && s21_isdigit(*p)) {
        result = result * 10.0 + (*p - '0');
        p++;
      }
      if ((p < *endptr) && *p == '.') {
        p++;
        double divisor = 10.0;
        while ((p < *endptr) && s21_isdigit(*p)) {
          fraction += (*p - '0') / divisor;
          divisor *= 10.0;
          p++;
        }
      }
      result += fraction;
      if ((p < *endptr) && (*p == 'e' || *p == 'E')) {
        p++;
        if ((p < *endptr) && *p == '-') {
          exp_sign = -1;
          p++;
        } else if ((p < *endptr) && *p == '+') {
          p++;
        }
        while ((p < *endptr) && s21_isdigit(*p)) {
          exp = exp * 10 + (*p - '0');
          p++;
        }
        exp *= exp_sign;
        result *= pow(10.0, exp);
      }
    }
    if (p == old_p && !inf_nan_written)
      *endptr = (char *)str;
    else if (!inf_nan_written)
      *endptr = (char *)p;
  } else {
    *endptr = S21_NULL;
  }

  result *= sign;
  return result;
}