
#ifndef _S21_STRING_H_
#define _S21_STRING_H_
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#define S21_NULL ((void *)0)
#define SPECS "cdfsu%xXoeEpgGin"
#define FLAGS "+- 0#"
#define LENGHTS "lhL"
#define ERROR_INCORRECT_PRECISION 2
#define ERROR_SPEC_NOT_FOUND 1
#define OK 0
typedef unsigned long s21_size_t;
typedef enum specificator {
  C,
  D,
  I,
  F,
  S,
  U,
  PERCENT,
  e,
  E,
  x,
  X,
  o,
  P,
  g,
  G,
  ge,
  GE,
  n,
  NONE
} specificator;
typedef enum lenght { h, l, L, default_len } lenght;
typedef struct flags {
  unsigned int plus : 1;
  unsigned int minus : 1;
  unsigned int space : 1;
  unsigned int dash : 1;
  unsigned int zero : 1;
  unsigned int star : 1;
} flags;
typedef struct description {
  flags fs;
  int width;
  int precision;
  lenght len;
  specificator spec;
} description;
s21_size_t s21_strlen(const char *str);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_ld_to_str(description *d, long double ld);
char *s21_int_to_str(description *d, long int c);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
long long int s21_strtoll(const char *str, char **endptr, int base);
unsigned long long int s21_strtoull(const char *str, char **endptr, int base);
long double s21_str_to_double(const char *str, char **endptr);
void s21_write_decim_to_ptr(long long int c, lenght len, void *p);
int s21_is_short_in_range(long long c);
#endif  //_S21_STRING_H_