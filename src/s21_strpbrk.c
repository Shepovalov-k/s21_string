#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int found = 0;
  s21_size_t i = 0, j = 0;
  for (i = 0; str1 != S21_NULL && str1[i] && !found; i++)
    for (j = 0; str2[j] && !(found = (str1[i] == str2[j])); j++);
  return (found) ? (char *)str1 + i - 1 : S21_NULL;
}