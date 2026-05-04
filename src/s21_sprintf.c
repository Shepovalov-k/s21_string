#include "s21_string.h"
#include "s21_support_functions.h"

int writedecim(char **str, description *d, long int c);
int writefloat(char **str, description *d, long double c);
int writedouble(char **str, description *d, double c);
int writechar(char **str, description *d, int c);
int writestring(char **str, description *d, char *chararr);
void writepercent(char **str);

long int s21_choose_int_type(description *d, va_list *list) {
  long int result;
  if (d->len == l || d->spec == P)
    result = va_arg(*list, long);
  else
    result = va_arg(*list, int);
  return result;
}

long double s21_choose_float_type(description *d, va_list *list) {
  long double result =
      (d->len == L) ? va_arg(*list, long double) : va_arg(*list, double);
  return result;
}

static int s21_handle_spec(char **str, description *d, va_list *list) {
  int res_code = OK;
  if (d->spec == C)
    res_code = writechar(str, d, va_arg(*list, int));
  else if (d->spec == S)
    res_code = writestring(str, d, va_arg(*list, char *));
  else if (d->spec == D || d->spec == x || d->spec == X || d->spec == o ||
           d->spec == U || d->spec == P) {
    long int c = s21_choose_int_type(d, list);
    res_code = writedecim(str, d, c);
  } else if (d->spec == F || d->spec == e || d->spec == E || d->spec == g ||
             d->spec == G) {
    long double c = s21_choose_float_type(d, list);
    res_code = writefloat(str, d, c);
  } else if (d->spec == PERCENT)
    writepercent(str);
  else if (d->spec == NONE)
    res_code = -1;
  return res_code;
}

int s21_sprintf(char *str, const char *format, ...) {
  int res = 0;
  int rescode = OK;
  char *p_str = str;

  va_list list;
  va_start(list, format);
  if (str == S21_NULL || format == S21_NULL) rescode = -1;
  for (; rescode == OK && *format;) {
    if (*format == '%') {
      description d;
      char *p_str_old = p_str;
      init_description(&d);
      format++;
      findflags(&format, &d);
      findwidth(&format, &d, &list);
      findprecision(&format, &d, &list);
      findlenght(&format, &d);
      findspec(&format, &d);
      rescode = s21_handle_spec(&p_str, &d, &list);
      res += p_str - p_str_old;
    } else {
      *p_str = *format;
      p_str++;
      format++;
      res++;
    }
  }
  if (rescode == OK) {
    *p_str = '\0';
  } else {
    res = -1;
  }
  va_end(list);
  return res;
}

int writechar(char **str, description *d, int c) {
  int result = OK;
  char *p = *str;
  p = (d->width > 1 && !d->fs.minus) ? s21_addspaces(p, d->width - 1) : p;
  *p = c;
  p++;
  p = (d->width > 1 && d->fs.minus) ? s21_addspaces(p, d->width - 1) : p;
  *str = p;
  return result;
}

int writestring(char **str, description *d, char *chararr) {
  int result = OK;
  if (chararr == S21_NULL) {
    chararr = "(null)";
  }

  int len = s21_strlen(chararr);
  int output_len =
      (d->precision > -1 && d->precision < len) ? d->precision : len;

  if (d->width > output_len && !d->fs.minus) {
    *str = s21_addspaces(*str, d->width - output_len);
  }

  for (int i = 0; i < output_len && result == OK; i++) {
    description d_char;
    d_char.width = 0;
    d_char.fs = (flags){0};
    writechar(str, &d_char, chararr[i]);
  }

  if (d->width > output_len && d->fs.minus) {
    *str = s21_addspaces(*str, d->width - output_len);
  }

  return result;
}

void s21_validate_flags(description *d) {
  if (d->spec != D && d->spec != P) d->fs.plus = 0;
  if (d->spec == P) d->fs.dash = 1;
  if (d->fs.minus) d->fs.zero = 0;
}

int writedecim(char **str, description *d, long int c) {
  s21_validate_flags(d);
  char *temp = s21_int_to_str(d, c);
  int written = s21_strlen(temp);
  *str = (char *)s21_memcpy(*str, temp, written * sizeof(char)) + written;
  free(temp);
  return (written >= 0) ? 0 : -1;
}

void s21_handle_g(description *d, long double num) {
  int precision = (d->precision == -1)  ? 6
                  : (d->precision == 0) ? 1
                                        : d->precision;

  int exponent = (num == 0.0) ? 0 : (int)floor(log10l(fabsl(num)));

  if (exponent < -4 || exponent >= precision) {
    d->spec = (d->spec == g) ? ge : GE;
    d->precision = precision - 1;
  } else {
    d->precision = precision - 1 - exponent;
  }
}

int writefloat(char **str, description *d, long double c) {
  char *temp;
  if (d->spec == g || d->spec == G) s21_handle_g(d, c);
  temp = s21_ld_to_str(d, c);
  int written = s21_strlen(temp);
  *str = (char *)s21_memcpy(*str, temp, written * sizeof(char)) + written;
  free(temp);
  return (written > 0) ? 0 : -1;
}

void writepercent(char **str) {
  **str = '%';
  (*str)++;
}