#include <stdio.h>
#include <stdlib.h>

#include "s21_support_functions.h"

#define NIL_STR "(nil)"

char* s21_addleadsym(char* str, specificator spec) {
  *(str++) = '0';
  switch (spec) {
    case x:
    case P:
      *(str++) = 'x';
      break;
    case X:
      *(str++) = 'X';
      break;
    default:
      break;
  }
  return str;
}

char* s21_handle_nil(char* str, description* d) {
  int nil_len = s21_strlen(NIL_STR);
  int core_len = (d->width > nil_len) ? d->width : nil_len;
  int spaces = core_len - nil_len;
  str = malloc(core_len + 1);
  char* p = str;
  p = (!d->fs.minus) ? s21_addspaces(p, spaces) : p;
  s21_memcpy(p, NIL_STR, nil_len);
  p += nil_len;
  p = (d->fs.minus) ? s21_addspaces(p, spaces) : p;
  *p = '\0';
  return str;
}

char* s21_decimal_to_str(description* d, long int c) {
  int isneg = (c < 0);
  int num_count = s21_numcount(c);
  int is_sign = s21_need_sign_space(d, isneg);
  int num_prec_count =
      ((num_count <= d->precision) ? d->precision : num_count) + is_sign;
  int char_count = (d->width >= num_prec_count) ? d->width : num_prec_count;
  if (c == 0 && char_count == -1) char_count = 1;
  char* str = malloc(char_count * sizeof(char) + 1);
  char* p_str = str;
  int spaces =
      (d->width > num_prec_count)
          ? (d->width - ((c == 0 && d->precision == 0) ? 0 : num_prec_count))
          : 0;
  int zeros = num_prec_count - num_count - is_sign;
  if (d->fs.zero) {
    zeros += spaces;
    spaces = 0;
  }
  p_str = (!d->fs.minus) ? s21_addspaces(p_str, spaces) : p_str;
  p_str = s21_handlesign(p_str, d, isneg);
  p_str = s21_handleprecint(p_str, zeros);
  p_str = (d->precision == 0 && c == 0) ? p_str : s21_handlenumberint(p_str, c);
  p_str = (d->fs.minus) ? s21_addspaces(p_str, spaces) : p_str;
  *(p_str) = '\0';
  return str;
}

char* s21_udecimal_to_str(description* d, long int c) {
  UInt num;
  num.l = c;
  int num_count = s21_unumcount(num, d);
  int is_sign = (d->fs.plus || (d->fs.space && d->spec == P));
  int is_lead_symb = d->fs.dash * ((d->spec == o) ? 1 : 2) * (d->spec != U);
  int num_prec_count =
      ((num_count <= d->precision || (num.l == 0 && d->precision == 0))
           ? d->precision
           : num_count);
  int char_count = (d->width >= num_prec_count + is_lead_symb + is_sign)
                       ? d->width
                       : num_prec_count + is_lead_symb + is_sign;
  char* str = malloc(char_count * sizeof(char) + 1);
  char* p_str = str;
  int spaces = (d->width > num_prec_count)
                   ? d->width - num_prec_count - is_lead_symb
                   : 0;
  int zeros = num_prec_count - num_count - (d->spec == o && is_lead_symb);
  if (d->fs.zero) {
    zeros += spaces;
    spaces = 0;
  }
  p_str = (!d->fs.minus) ? s21_addspaces(p_str, spaces) : p_str;
  p_str = (is_sign) ? s21_handlesign(p_str, d, 0) : p_str;
  p_str = (d->fs.dash && num.l != 0 && d->spec != U)
              ? s21_addleadsym(p_str, d->spec)
              : p_str;
  p_str = s21_handleprecint(p_str, zeros);
  p_str = !(d->precision == 0 && c == 0) ? s21_handleunumberint(p_str, num, d)
                                         : p_str;
  p_str = (d->fs.minus) ? s21_addspaces(p_str, spaces) : p_str;
  *(p_str) = '\0';
  return str;
}

char* s21_int_to_str(description* d, long int c) {
  char* str = S21_NULL;
  if (d->spec == D)
    str = s21_decimal_to_str(d, c);
  else if (d->spec == P && c == 0)
    str = s21_handle_nil(str, d);
  else
    str = s21_udecimal_to_str(d, c);
  return str;
}