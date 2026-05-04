#include "s21_string.h"
#include "s21_support_functions.h"

#define WRITING_SUPPRESSED 0
#define WRITTEN 1
#define WRITE_ERROR -1

typedef struct scan_counter {
  int written_args;
  int read_chars;
} scan_counter;

int s21_is_ulong_in_range(long long c) {
  return ((unsigned long long)c <= ULONG_MAX);
}

void s21_write_decim_to_ptr(long long int c, lenght len, void *p) {
  switch (len) {
    case l:
      *((long *)p) = (long)c;
      break;
    case h:
      *((short *)p) = (short)c;
      break;
    default:
      *((int *)p) = (int)c;
      break;
  }
}

void s21_write_udecim_to_ptr(unsigned long long int c, lenght len, void *p) {
  switch (len) {
    case l:
      *((unsigned long *)p) = (unsigned long)c;
      break;
    case h:
      *((unsigned short *)p) = (unsigned short)c;
      break;
    default:
      *((unsigned int *)p) = (unsigned int)c;
      break;
  }
}

void s21_write_float_to_ptr(long double c, lenght len, void *p) {
  switch (len) {
    case l:
      *((double *)p) = (double)c;
      break;
    case L:
      *((long double *)p) = (long double)c;
      break;
    default:
      *((float *)p) = (float)c;
      break;
  }
}

void s21_write_ptr_to_ptr(unsigned long long int c, void **p) {
  *p = (s21_is_ulong_in_range(c)) ? (void *)c : S21_NULL;
}

int s21_readchar(char **str, description *d, char *p) {
  int res = WRITTEN;
  int char_buffer_len = (d->width > 0) ? d->width : 1;
  if (*str && **str) {
    int i = 0;
    for (; *(*str) && i < char_buffer_len; i++) {
      if (p != S21_NULL) p[i] = *(*str);
      (*str)++;
    }
    res = (p == S21_NULL || i == 0) ? WRITING_SUPPRESSED : res;
  } else
    res = WRITE_ERROR;
  return res;
}

int s21_readstring(char **str, description *d, char *p) {
  int res = WRITTEN;
  if (*str && **str) {
    int i = 0;
    for (; **str && !s21_isspace(*(*str)) && !(d->width >= 0 && i == d->width);
         i++) {
      if (p != S21_NULL) p[i] = *(*str);
      (*str)++;
    }
    res = (p == S21_NULL || i == 0) ? WRITING_SUPPRESSED : res;
    if (p != S21_NULL) p[i] = '\0';
  } else
    res = WRITE_ERROR;
  return res;
}

int s21_is_unsigned(specificator spec) {
  return (spec == X || spec == x || spec == P || spec == U);
}
//""
int s21_readdecim(char **str, description *d, void *p) {
  int res = WRITTEN;
  int base = s21_choose_radix(d->spec);
  long long int c;
  *str = s21_avoid_spaces(*str);
  s21_size_t str_len = s21_strlen(*str);
  char *end_str = *str + ((d->width != -1) && ((s21_size_t)d->width < str_len)
                              ? (s21_size_t)d->width
                              : str_len);
  res = (end_str == *str) ? WRITE_ERROR : res;
  if (res != WRITE_ERROR) {
    c = s21_strtoll(*str, &end_str, base);
    if (end_str == S21_NULL) {
      res = WRITE_ERROR;
    } else if (end_str == *str || p == S21_NULL) {
      res = WRITING_SUPPRESSED;
      *str = end_str;
    } else if (res != WRITE_ERROR) {
      if (!s21_is_unsigned(d->spec))
        s21_write_decim_to_ptr(c, d->len, p);
      else if (d->spec == P)
        s21_write_ptr_to_ptr(c, p);
      else
        s21_write_udecim_to_ptr((unsigned long long)c, d->len, p);
      *str = end_str;
    }
  }
  return res;
}

int s21_readpercent(char **str) {
  int res = WRITING_SUPPRESSED;
  char *p_str = *str;
  p_str = s21_avoid_spaces(p_str);
  if (*p_str == '%') {
    p_str++;
    *str = p_str;
  } else
    res = WRITE_ERROR;
  return res;
}

int s21_write_chars_num(long long c, description *d, void *p) {
  int res = WRITING_SUPPRESSED;
  if (p == S21_NULL)
    res = WRITING_SUPPRESSED;
  else
    s21_write_decim_to_ptr(c, d->len, p);
  return res;
}

int s21_readfloat(char **str, description *d, void *p) {
  int res = WRITTEN;
  long double c;
  *str = s21_avoid_spaces(*str);
  s21_size_t str_len = s21_strlen(*str);
  char *end_str = *str + ((d->width != -1) && ((s21_size_t)d->width < str_len)
                              ? (s21_size_t)d->width
                              : str_len);
  res = (end_str == *str) ? WRITE_ERROR : res;
  if (res != WRITE_ERROR) {
    c = s21_str_to_double(*str, &end_str);
    if (end_str == S21_NULL) {
      res = WRITE_ERROR;
    } else if (end_str == *str || p == S21_NULL) {
      res = WRITING_SUPPRESSED;
      *str = end_str;
    } else if (res != WRITE_ERROR) {
      s21_write_float_to_ptr(c, d->len, p);
      *str = end_str;
    }
  }
  return res;
}

static int s21_handle_spec(char **str, description *d, va_list *list,
                           scan_counter *counter) {
  int res = 0;
  void *p =
      (d->fs.star || d->spec == PERCENT) ? S21_NULL : va_arg(*list, void *);
  char *p_str = *str;
  if (d->spec == C) {
    res = s21_readchar(str, d, p);
  } else if (d->spec == S) {
    res = s21_readstring(str, d, p);
  } else if (d->spec == D || d->spec == x || d->spec == X || d->spec == o ||
             d->spec == U || d->spec == I || d->spec == P) {
    res = s21_readdecim(str, d, p);
  } else if (d->spec == F || d->spec == e || d->spec == E || d->spec == g ||
             d->spec == G) {
    res = s21_readfloat(str, d, p);
  } else if (d->spec == PERCENT) {
    res = s21_readpercent(str);
  } else if (d->spec == n)
    res = s21_write_chars_num(counter->read_chars, d, p);
  if (res != WRITE_ERROR) {
    counter->written_args += res;
    counter->read_chars += *str - p_str;
  }
  return (res == WRITE_ERROR) ? res : OK;
}

int s21_sscanf(const char *str, const char *format, ...) {
  int rescode = OK;
  int res;
  char *p_str = (char *)str;
  scan_counter counter = {0};
  va_list list;
  va_start(list, format);
  if (str == S21_NULL || format == S21_NULL || !*str) rescode = -1;
  res = rescode;
  for (; rescode == OK && *format;) {
    if (*format == '%') {
      description d;
      init_description(&d);
      format++;
      if (*format == '*') {
        d.fs.star = 1;
        format++;
      }
      scan_findwidth(&format, &d);
      findlenght(&format, &d);
      findspec(&format, &d);
      rescode = s21_handle_spec(&p_str, &d, &list, &counter);
    } else if (s21_isspace(*format)) {
      char *old_p = p_str;
      p_str = s21_avoid_spaces(p_str);
      counter.read_chars += p_str - old_p;
      format++;
    } else if (*p_str == *format) {
      p_str++;
      format++;
      counter.read_chars++;
    } else
      rescode = -1;
    counter.read_chars =
        (rescode == -1 && counter.written_args == 0) ? 0 : counter.read_chars;
  }
  res = (counter.written_args == 0 && rescode == -1) ? rescode
                                                     : counter.written_args;
  va_end(list);
  return res;
}