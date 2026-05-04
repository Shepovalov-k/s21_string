#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  while (n-- > 0 && result == 0) {
    result = (*str1 != *str2 || *str1 == '\0')
                 ? (unsigned char)*str1 - (unsigned char)*str2
                 : 0;
    str1++;
    str2++;
  }
  return result;
}
