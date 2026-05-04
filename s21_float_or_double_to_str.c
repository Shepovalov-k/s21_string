#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "s21_string.h"
#include "s21_support_functions.h"
#define INFINITY_STR "INF"
#define INFINITY_STR_SMALL "inf"
#define NAN_STR "NAN"
#define NAN_STR_SMALL "nan"

int is_g(specificator spec) {
  return spec == g || spec == G || spec == ge || spec == GE;
}

int is_e(specificator spec) {
  return spec == e || spec == E || spec == ge || spec == GE;
}

char *s21_handle_inf_nan(char *str, description *d, long double ld) {
  char *inf_nan_str;
  if (d->spec == E || d->spec == GE)
    inf_nan_str = (isnan(ld)) ? NAN_STR : INFINITY_STR;
  else
    inf_nan_str = (isnan(ld)) ? NAN_STR_SMALL : INFINITY_STR_SMALL;
  int sign_len = (signbit(ld) || d->fs.plus || d->fs.space);
  int inf_nan_len = 3 + sign_len;
  int core_len = (d->width > inf_nan_len) ? d->width : inf_nan_len;
  int spaces = core_len - inf_nan_len;
  str = malloc(core_len + 1);
  char *p = str;
  p = (!d->fs.minus) ? s21_addspaces(p, spaces) : p;
  p = s21_handlesign(p, d, signbit(ld));
  s21_memcpy(p, inf_nan_str, inf_nan_len - sign_len);
  p += inf_nan_len - sign_len;
  p = (d->fs.minus) ? s21_addspaces(p, spaces) : p;
  *p = '\0';
  return str;
}

char *s21_ld_to_str(description *d, long double ld) {
  char *str = S21_NULL;
  int isneg = signbit(ld);
  if (isinf(ld) || isnan(ld)) {
    str = s21_handle_inf_nan(str, d, ld);
  } else {
    int core_len;
    int exp = 0;
    int precision = (d->precision < 0) ? 6 : d->precision;
    int sign_len = s21_need_sign_space(d, isneg);
    int full_number_len = sign_len;
    long double abs_val = (isneg) ? -ld : ld;
    if (is_e(d->spec)) {
      exp = s21_read_exp(abs_val);
      abs_val /= powl(10.0L, exp);
      full_number_len += 2 + (abs(exp) >= 99 ? s21_numcount(exp) : 2);
    }
    long double intpart;
    long double fracpart = modfl(abs_val, &intpart);
    intpart = (precision == 0) ? roundl(abs_val) : intpart;
    long double frac_scaled = roundl(fracpart * powl(10, precision));

    if (s21_numcount_ld_intpart(frac_scaled) > precision && precision != 0) {
      intpart++;
      frac_scaled = fmodl(frac_scaled, powl(10, precision - 1)) * 10;
    }

    int frac_zeros = s21_count_trailing_zeros(frac_scaled);
    if ((is_g(d->spec)) && !d->fs.dash && frac_zeros > 0) {
      frac_scaled /= powl(10, frac_zeros);
      precision -= frac_zeros;
    }

    precision =
        (is_g(d->spec) && !d->fs.dash && frac_scaled < 1 && precision != 0)
            ? 0
            : precision;

    int is_point = (precision > 0 || d->fs.dash);
    full_number_len += precision + is_point + s21_numcount_ld_intpart(intpart);

    core_len = (d->width > full_number_len) ? d->width : full_number_len;
    int spaces = core_len - full_number_len;
    str = malloc(core_len + 128);
    char *p = str;
    if (d->fs.zero && !d->fs.minus) {
      p = s21_handlesign(p, d, signbit(ld));
      p = s21_addzeros(p, spaces);
    } else if (!d->fs.minus) {
      p = s21_addspaces(p, spaces);
      p = s21_handlesign(p, d, signbit(ld));
    } else {
      p = s21_handlesign(p, d, signbit(ld));
    }
    p = s21_handle_float_int_part(p, s21_numcount_ld_intpart(intpart), intpart);
    if (is_point) *p++ = '.';
    p = (is_point) ? s21_handle_float_int_part(p, precision, frac_scaled) : p;
    p = (is_e(d->spec)) ? s21_add_exponent(p, d, exp) : p;
    p = (d->fs.minus) ? s21_addspaces(p, spaces) : p;
    *p = '\0';
  }
  return str;
}