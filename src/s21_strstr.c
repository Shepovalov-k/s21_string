#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  int i, found = 0, end_haystack = 0;
  for (; needle != S21_NULL && haystack != S21_NULL && !end_haystack && !found;
       haystack++) {
    for (i = 0; needle != S21_NULL && needle[i] == haystack[i] && needle[i];
         i++);
    end_haystack = !*haystack ? 1 : 0;
    found = (!needle[i]) ? 1 : found;
  }
  return (found) ? (char *)haystack - 1 : S21_NULL;
}