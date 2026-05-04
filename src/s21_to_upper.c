#include "s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t len;
  char *upper_str = S21_NULL;

  if (str != S21_NULL &&
      (upper_str = (char *)malloc((len = s21_strlen(str)) + 1))) {
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        upper_str[i] = str[i] - 32;
      } else {
        upper_str[i] = str[i];
      }
    }

    upper_str[len] = '\0';
  }
  return upper_str;
}