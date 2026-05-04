#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char *s1 = str1;
  int flag = 1;
  while (*s1 && flag) {
    const char *s2 = str2;
    while (*s2 && *s2 != *s1) {
      if (!*(s2 + 1)) flag = 0;
      s2++;
    }
    s1 += flag;
  }
  return s1 - str1;
}