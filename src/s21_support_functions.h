#ifndef _S21_SUPPORT_FUNCTIONS_H_
#define _S21_SUPPORT_FUNCTIONS_H_
#include "s21_string.h"

#define SPACES "\n\t \f\r\v"
#define NUMS "0123456789ABCDEF"
#define nums "0123456789abcdef"

typedef union UInt {
  long int l;
  unsigned short uh;
  unsigned u;
  unsigned long ul;
} UInt;
long long s21_pow(int num, int n);
int s21_numcount(long int c);
int s21_need_sign_space(description *d, int isneg);
int s21_maxint(int n, int *arr);
char *s21_addspaces(char *str, int spaces);
char *s21_addzeros(char *str, int spaces);
char *s21_handlesign(char *str, description *d, int isneg);
char *s21_handleprecint(char *str, int zeros);
char *s21_handlenumberint(char *str, long int number);
char *s21_handleunumberint(char *str, UInt number, description *d);
int s21_unumcount(UInt c, description *d);
int s21_choose_radix(specificator spec);
int s21_read_exp(long double ld);
int s21_numcount_ld_intpart(long double c);
char *s21_add_exponent(char *p, description *d, int exp);
char *s21_handle_float_int_part(char *p, int int_digit_count,
                                long double int_part);
char *s21_handle_float_frac_part(char *p, int int_digit_count,
                                 unsigned long long int_part);
int s21_count_trailing_zeros(long double x);
void scan_findwidth(const char **format, description *d);
char *s21_avoid_spaces(char *str);
int s21_alpha_to_digit(int c);
int s21_digit_to_int(int c);
char *s21_scan_sign(char *str, int *c);
char *s21_scan_base_prefix(char *str, char *end_str, int *base);
int s21_digit_alpha_process(char c, int *digit);

int s21_isalpha(int c);
int s21_isdigit(int c);
int s21_isspace(char c);

void init_description(description *d);
void findflags(const char **format, description *d);
void findspec(const char **format, description *d);
void findlenght(const char **format, description *d);
long long findint(const char **format);
void findwidth(const char **format, description *d, va_list *list);
void findprecision(const char **format, description *d, va_list *list);
s21_size_t s21_strspn(const char *str1, const char *str2);
#endif  //_S21_SUPPORT_FUNCTIONS_H_