#include "s21_string.h"

void *s21_to_lower(const char *str) {
  s21_size_t len;
  char *lower_str = S21_NULL;

  if (str != S21_NULL &&
      (lower_str = (char *)malloc((len = s21_strlen(str)) + 1))) {
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        lower_str[i] = str[i] + 32;
      } else {
        lower_str[i] = str[i];
      }
    }

    lower_str[len] = '\0';
  }
  return lower_str;
}