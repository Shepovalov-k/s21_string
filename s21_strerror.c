#include "s21_strerror.h"

#include "s21_string.h"
#include "s21_support_functions.h"

char *s21_strerror(int errnum) {
  static char buffer[BUFFSIZE];
  static const char *errors[] = ERRORS;
  static char *result = S21_NULL;
  s21_size_t error_count = sizeof(errors) / sizeof(errors[0]);
  if (errnum < 0 || errnum >= (int)error_count ||
      !s21_strncmp(errors[errnum], "(null)", 6)) {
    int sign = (errnum < 0);
    int num_count = s21_numcount(errnum);
    s21_memcpy(buffer, UERROR, s21_strlen(UERROR));
    char *p_str = buffer + sizeof(UERROR) + num_count + sign;
    *--p_str = '\0';
    if (sign) {
      errnum = -errnum;
      buffer[sizeof(UERROR) - 1] = '-';
    }
    while (errnum) {
      *--p_str = NUMS[errnum % 10];
      errnum /= 10;
    }
    result = buffer;
  } else {
    result = (char *)errors[errnum];
  }
  return result;
}