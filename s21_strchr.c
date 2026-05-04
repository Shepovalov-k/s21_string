#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  while (*str && result == S21_NULL) {
    result = (*str == (char)c) ? (char *)str : result;
    str++;
  }
  result = (*str == (char)c) ? (char *)str : result;
  return result;
}
