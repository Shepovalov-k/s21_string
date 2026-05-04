#include "s21_string.h"
#include "s21_support_functions.h"

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = S21_NULL;
  char *current_token = S21_NULL;
  int token_found = 0;
  if (str == S21_NULL) {
    str = next_token;
  }
  if (str != S21_NULL) {
    str += s21_strspn(str, delim);
  }
  if (str != S21_NULL && *str != '\0') {
    current_token = str;
    next_token = str + s21_strcspn(str, delim);
    if (*next_token != '\0') {
      *next_token = '\0';
      next_token++;
    } else {
      next_token = S21_NULL;
    }
    token_found = 1;
  }
  return (token_found) ? current_token : S21_NULL;
}