#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *trimmed_str = S21_NULL;

  s21_size_t src_len;
  s21_size_t trimmed_len;

  if (src && trim_chars) {
    src_len = s21_strlen(src);

    s21_size_t start = 0;
    s21_size_t end = src_len;

    while (start < src_len && s21_strchr(trim_chars, src[start])) {
      start++;
    }

    while (end > start && s21_strchr(trim_chars, src[end - 1])) {
      end--;
    }

    trimmed_len = end - start;

    if ((trimmed_str = (char *)malloc(trimmed_len + 1))) {
      s21_memcpy(trimmed_str, src + start, trimmed_len);
      trimmed_str[trimmed_len] = '\0';
    }
  }

  if (src != S21_NULL && trim_chars == S21_NULL &&
      (trimmed_str = (char *)malloc(s21_strlen(src) + 1))) {
    s21_memcpy(trimmed_str, src, s21_strlen(src));
    trimmed_str[s21_strlen(src)] = '\0';
  }

  return trimmed_str;
}