#include "s21_support_functions.h"

#include "s21_string.h"

int s21_isalpha(int c) {
  return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

int s21_isdigit(int c) { return (c >= '0' && c <= '9'); }

int s21_isspace(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' ||
          c == '\f');
}

char* s21_avoid_spaces(char* str) { return str + s21_strspn(str, SPACES); }

int s21_choose_radix(specificator spec) {
  int result = 10;
  if (spec == x || spec == X || spec == P)
    result = 16;
  else if (spec == o)
    result = 8;
  else if (spec == I)
    result = 0;
  return result;
}

long long s21_pow(int num, int n) {
  long long result = 1;
  for (; n > 0; n--) result *= num;
  return result;
}

int s21_numcount(long int c) {
  int count = 1;
  int radix = 10;
  unsigned long new_c;
  if (c == LONG_MIN)
    new_c = (unsigned long)LONG_MAX + 1;
  else
    new_c = (c < 0) ? -c : c;
  while (new_c > (unsigned long)radix - 1) {
    count++;
    new_c /= radix;
  }
  return count;
}

int s21_numcount_ld_intpart(long double c) {
  int count = 1;
  long double new_c = (c < 0) ? -c : c;
  while (new_c > nextafter(10.0L, 0.0L)) {
    count++;
    new_c /= 10;
  }
  return count;
}

static int s21_is_last_digit_zero(long double number) {
  const long double epsilon = 0.1L;
  long double last_digit = fmodl(number, 10.0L);
  return (fabsl(last_digit) < epsilon);
}

int s21_count_trailing_zeros(long double x) {
  int count = 0;
  long double int_part;
  int still_has_zeros = 1;
  modfl(x, &int_part);
  if (fabsl(int_part) >= 1.0L) {
    still_has_zeros = s21_is_last_digit_zero(int_part);
    while (still_has_zeros && fabsl(int_part) >= 1.0L) {
      count++;
      int_part /= 10.0L;
      still_has_zeros = s21_is_last_digit_zero(int_part);
    }
  }
  return count;
}

unsigned long s21_choose_uint(UInt c, description* d) {
  unsigned long result;
  if (d->spec == P || d->len == l)
    result = c.ul;
  else if (d->len == h)
    result = c.uh;
  else
    result = c.u;
  return result;
}

int s21_unumcount(UInt c, description* d) {
  int count = 1;
  unsigned long num = s21_choose_uint(c, d);
  int radix = s21_choose_radix(d->spec);
  while (num > (unsigned long)radix - 1) {
    count++;
    num /= radix;
  }
  return count;
}

int s21_need_sign_space(description* d, int isneg) {
  int result = ((isneg) || (d->fs.plus) || (d->fs.space));
  return result;
}

char* s21_addspaces(char* str, int spaces) {
  for (; spaces > 0; spaces--) *(str++) = ' ';
  return str;
}

char* s21_addzeros(char* str, int spaces) {
  for (; spaces > 0; spaces--) *(str++) = '0';
  return str;
}

char* s21_handlesign(char* str, description* d, int isneg) {
  if (isneg) {
    *(str++) = '-';
  } else if (d->fs.plus) {
    *(str++) = '+';
  } else if (d->fs.space) {
    *(str++) = ' ';
  }
  return str;
}

char* s21_handleprecint(char* str, int zeros) {
  for (; zeros > 0; zeros--) *(str++) = '0';
  return str;
}

char* s21_handlenumberint(char* str, long int number) {
  unsigned long new_number;
  if (number == LONG_MIN)
    new_number = (unsigned long)LONG_MAX + 1;
  else
    new_number = (number < 0) ? (unsigned long)-number : (unsigned long)number;
  if (new_number == 0) {
    *str++ = '0';
    return str;
  }

  int num_count = s21_numcount(number);
  int radix = 10;
  char* p_str = str + num_count;

  while (new_number > 0) {
    *--p_str = NUMS[new_number % radix];
    new_number /= radix;
  }

  return str + num_count;
}

char s21_float_notation_to_char(specificator s) {
  char ch = 0;
  if (s == e || s == ge)
    ch = 'e';
  else if (s == E || s == GE)
    ch = 'E';
  return ch;
}

char* s21_add_exponent(char* p, description* d, int exp) {
  *p++ = s21_float_notation_to_char(d->spec);
  *p++ = (exp >= 0) ? '+' : '-';
  exp = (exp >= 0) ? exp : -exp;
  if (exp >= 10) {
    p = s21_handlenumberint(p, (long)exp);
  } else {
    *p++ = '0';
    *p++ = '0' + exp;
  }
  return p;
}

char* s21_handle_float_int_part(char* p, int int_digit_count,
                                long double int_part) {
  for (int i = int_digit_count - 1; i >= 0; i--) {
    int digit = (int)fmodl(int_part, 10.0L);
    p[i] = '0' + digit;
    int_part = floorl(int_part / 10.0L);
  }
  p += int_digit_count;
  return p;
}

int s21_read_exp(long double ld) {
  int exp = 0;
  long double prec_ten = nextafterl(10.0L, 0.0L);
  long double prec_one = nextafterl(1.0L, 0.0L);
  long double test_val = ld;
  if (test_val >= prec_one) {
    while (test_val > nextafterl(9.9L, 0.0L)) {
      test_val /= prec_ten;
      exp++;
    }
  } else {
    while (test_val <= nextafterl(0.9L, 0.0L)) {
      test_val *= prec_ten;
      exp--;
    }
  }
  return exp;
}

char* s21_handle_float_frac_part(char* p, int int_digit_count,
                                 unsigned long long frac_part) {
  int i = int_digit_count - 1;
  for (; i >= 0; i--) {
    p[i] = '0' + (frac_part % 10);
    frac_part /= 10;
  }
  p += int_digit_count;
  return p;
}

char* s21_handleunumberint(char* str, UInt number, description* d) {
  unsigned long num = s21_choose_uint(number, d);
  int num_count = s21_unumcount(number, d);
  int radix = s21_choose_radix(d->spec);
  char* p_str = str + num_count;
  if (num > 0) {
    while (num > 0) {
      *--p_str = (d->spec == X) ? NUMS[num % radix] : nums[num % radix];
      num /= radix;
    }
  } else if (num == 0)
    *--p_str = '0';
  return str + num_count;
}

int s21_alpha_to_digit(int c) {
  return c - ((c >= 'A' && c <= 'F') ? 'A' : 'a') + 10;
}

char* s21_scan_sign(char* str, int* c) {
  if (*str == '+') {
    str++;
  } else if (*str == '-') {
    *c = -1;
    str++;
  }
  return str;
}

char* s21_scan_base_prefix(char* str, char* end_str, int* base) {
  if (str < end_str && *base == 0 && s21_isdigit(*str)) {
    if (*str == '0') {
      if (str + 1 < end_str && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
        *base = 16;
        str += 2;
      } else {
        *base = 8;
        str++;
      }
    } else {
      *base = 10;
    }
  } else if (*base == 16 && (str + 1 < end_str) && *str == '0' &&
             (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
  } else if (*base == 8 && *str == '0')
    str++;
  return str;
}

int s21_digit_alpha_process(char c, int* digit) {
  int flag = 1;
  if (s21_isdigit(c)) {
    *digit = c - '0';
  } else if (s21_isalpha(c)) {
    *digit = s21_alpha_to_digit(c);
  } else
    flag = 0;
  return flag;
}

void init_description(description* d) {
  d->fs = (flags){0};
  d->len = default_len;
  d->spec = NONE;
  d->width = -1;
  d->precision = -1;
}

void findflags(const char** format, description* d) {
  for (; *format != S21_NULL && **format &&
         s21_strrchr(FLAGS, **format) != S21_NULL;
       (*format)++) {
    switch (**format) {
      case '+':
        d->fs.plus = 1;
        break;
      case '-':
        d->fs.minus = 1;
        break;
      case ' ':
        d->fs.space = 1;
        break;
      case '#':
        d->fs.dash = 1;
        break;
      case '0':
        d->fs.zero = 1;
        break;
    }
  }
}

void findspec(const char** format, description* d) {
  if (s21_strrchr(SPECS, **format) != S21_NULL) {
    switch (**format) {
      case 'c':
        d->spec = C;
        break;
      case 'd':
        d->spec = D;
        break;
      case 'i':
        d->spec = I;
        break;
      case 'f':
        d->spec = F;
        break;
      case 's':
        d->spec = S;
        break;
      case 'u':
        d->spec = U;
        break;
      case 'e':
        d->spec = e;
        break;
      case 'E':
        d->spec = E;
        break;
      case 'x':
        d->spec = x;
        break;
      case 'X':
        d->spec = X;
        break;
      case 'o':
        d->spec = o;
        break;
      case '%':
        d->spec = PERCENT;
        break;
      case 'p':
        d->spec = P;
        break;
      case 'g':
        d->spec = g;
        break;
      case 'G':
        d->spec = G;
        break;
      case 'n':
        d->spec = n;
        break;
    }
    (*format)++;
  }
}

void findlenght(const char** format, description* d) {
  if (s21_strrchr(LENGHTS, **format) != S21_NULL) {
    int ch = **format;
    switch (ch) {
      case 'l':
        d->len = l;
        break;
      case 'h':
        d->len = h;
        break;
      case 'L':
        d->len = L;
        break;
    }
    (*format)++;
  }
}

long long int findint(const char** format) {
  int flag = -1;
  long long int res = 0;
  for (; *format != S21_NULL && **format && s21_isdigit(**format);
       (*format)++) {
    res = res * 10 + (**format - '0');
    flag = 0;
  }
  return (flag == 0) ? res : flag;
}

void findwidth(const char** format, description* d, va_list* list) {
  if (**format == '*') {
    (*format)++;
    d->width = va_arg(*list, int);
    if (d->width < 0) {
      d->fs.minus = 1;
      d->width = -d->width;
    }
  } else {
    int new_width = findint(format);
    d->width = (new_width != -1) ? new_width : d->width;
  }
}

void scan_findwidth(const char** format, description* d) {
  int new_width = findint(format);
  d->width = (new_width != -1) ? new_width : d->width;
}

void findprecision(const char** format, description* d, va_list* list) {
  if (**format == '.') {
    (*format)++;
    if (**format == '*') {
      (*format)++;
      d->precision = va_arg(*list, int);
      d->precision = (d->precision < 0) ? -1 : d->precision;
    } else {
      int new_precision = findint(format);
      d->precision = (new_precision != -1) ? new_precision : 0;
    }
  }
}

s21_size_t s21_strspn(const char* str1, const char* str2) {
  const char* s1 = str1;
  int flag = 1;
  while (*s1 != '\0' && flag) {
    const char* s2 = str2;
    int is_delim = 0;
    while (*s2 != '\0') {
      if (*s1 == *s2) {
        is_delim = 1;
      }
      s2++;
    }
    if (!is_delim) {
      flag = 0;
    }
    if (flag) s1++;
  }
  return s1 - str1;
}