#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  void *result = S21_NULL;
  while (n--) {
    if (*ptr == (unsigned char)c) {
      result = (void *)ptr;
      continue;
    }
    ptr++;
  }
  return result;
}