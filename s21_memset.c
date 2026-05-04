#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  unsigned char *result = ptr;
  while (n--) {
    *ptr = (unsigned char)c;
    ptr++;
  }
  return result;
}