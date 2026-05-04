#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  register const unsigned char *ptr1 = (const unsigned char *)str1;
  register const unsigned char *ptr2 = (const unsigned char *)str2;
  int result = 0;

  while (n-- > 0 && (result = *ptr1 - *ptr2) == 0) {
    ptr1++;
    ptr2++;
  }

  return result;
}