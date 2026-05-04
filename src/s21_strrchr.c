#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *p = S21_NULL;
  for (; *str; str++)
    p = ((unsigned char)*str == (unsigned char)c) ? (char *)str : p;
  p = ((unsigned char)*str == (unsigned char)c) ? (char *)str : p;
  return p;
}