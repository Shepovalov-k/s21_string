CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -g
LIBRARY = s21_string.a
OBJ = s21_string.o
TESTS = ./tests/test_s21_string.c

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rcs $(LIBRARY) $(OBJ)

$(OBJ): s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_strncat.c \
        s21_strchr.c s21_strncmp.c s21_strncpy.c s21_strcspn.c s21_strerror.c \
		s21_strlen.c s21_strpbrk.c s21_strrchr.c s21_strstr.c s21_strtok.c s21_sprintf.c \
		s21_support_functions.c s21_float_or_double_to_str.c s21_int_to_str.c \
		s21_strtoll.c s21_str_to_double.c \
		s21_to_upper.c s21_to_lower.c s21_trim.c s21_insert.c
	$(CC) $(CFLAGS) -c s21_to_upper.c -o s21_to_upper.o
	$(CC) $(CFLAGS) -c s21_to_lower.c -o s21_to_lower.o
	$(CC) $(CFLAGS) -c s21_insert.c -o s21_insert.o
	$(CC) $(CFLAGS) -c s21_trim.c -o s21_trim.o
	$(CC) $(CFLAGS) -c s21_memchr.c -o s21_memchr.o
	$(CC) $(CFLAGS) -c s21_memcmp.c -o s21_memcmp.o
	$(CC) $(CFLAGS) -c s21_memcpy.c -o s21_memcpy.o
	$(CC) $(CFLAGS) -c s21_memset.c -o s21_memset.o
	$(CC) $(CFLAGS) -c s21_strncat.c -o s21_strncat.o
	$(CC) $(CFLAGS) -c s21_strchr.c -o s21_strchr.o
	$(CC) $(CFLAGS) -c s21_strncmp.c -o s21_strncmp.o
	$(CC) $(CFLAGS) -c s21_strncpy.c -o s21_strncpy.o
	$(CC) $(CFLAGS) -c s21_strcspn.c -o s21_strcspn.o
	$(CC) $(CFLAGS) -c s21_strerror.c -o s21_strerror.o
	$(CC) $(CFLAGS) -c s21_strlen.c -o s21_strlen.o
	$(CC) $(CFLAGS) -c s21_strpbrk.c -o s21_strpbrk.o
	$(CC) $(CFLAGS) -c s21_strrchr.c -o s21_strrchr.o
	$(CC) $(CFLAGS) -c s21_strstr.c -o s21_strstr.o
	$(CC) $(CFLAGS) -c s21_strtok.c -o s21_strtok.o
	$(CC) $(CFLAGS) -c s21_support_functions.c -o s21_support_functions.o
	$(CC) $(CFLAGS) -c s21_float_or_double_to_str.c -o s21_float_or_double_to_str.o
	$(CC) $(CFLAGS) -c s21_int_to_str.c -o s21_int_to_str.o
	$(CC) $(CFLAGS) -c s21_strtoll.c -o s21_strtoll.o
	$(CC) $(CFLAGS) -c s21_str_to_double.c -o s21_str_to_double.o
	$(CC) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o
	$(CC) $(CFLAGS) -c s21_sscanf.c -o s21_sscanf.o
	ld -r s21_memchr.o s21_memcmp.o s21_memcpy.o s21_memset.o s21_strncat.o \
	    s21_strchr.o s21_strncmp.o s21_strncpy.o s21_strcspn.o s21_strerror.o \
		s21_strlen.o s21_strpbrk.o s21_strrchr.o s21_strstr.o s21_strtok.o \
		s21_support_functions.o s21_float_or_double_to_str.o s21_int_to_str.o s21_sprintf.o \
		s21_strtoll.o s21_str_to_double.o s21_sscanf.o \
		s21_to_upper.o s21_to_lower.o s21_trim.o s21_insert.o -o $(OBJ)


test: $(LIBRARY)
	$(CC) $(CFLAGS) -o test $(TESTS) $(LIBRARY) -lcheck -lm -lsubunit
	./test

gcov_report: clean
	mkdir -p gcov_report
	$(CC) $(CFLAGS) -c --coverage s21_to_lower.c -o s21_to_lower.o
	$(CC) $(CFLAGS) -c --coverage s21_to_upper.c -o s21_to_upper.o
	$(CC) $(CFLAGS) -c --coverage s21_trim.c -o s21_trim.o
	$(CC) $(CFLAGS) -c --coverage s21_insert.c -o s21_insert.o
	$(CC) $(CFLAGS) -c --coverage s21_memchr.c -o s21_memchr.o
	$(CC) $(CFLAGS) -c --coverage s21_memcmp.c -o s21_memcmp.o
	$(CC) $(CFLAGS) -c --coverage s21_memcpy.c -o s21_memcpy.o
	$(CC) $(CFLAGS) -c --coverage s21_memset.c -o s21_memset.o
	$(CC) $(CFLAGS) -c --coverage s21_strncat.c -o s21_strncat.o
	$(CC) $(CFLAGS) -c --coverage s21_strchr.c -o s21_strchr.o
	$(CC) $(CFLAGS) -c --coverage s21_strncmp.c -o s21_strncmp.o
	$(CC) $(CFLAGS) -c --coverage s21_strncpy.c -o s21_strncpy.o
	$(CC) $(CFLAGS) -c --coverage s21_strcspn.c -o s21_strcspn.o
	$(CC) $(CFLAGS) -c --coverage s21_strerror.c -o s21_strerror.o
	$(CC) $(CFLAGS) -c --coverage s21_strlen.c -o s21_strlen.o
	$(CC) $(CFLAGS) -c --coverage s21_strpbrk.c -o s21_strpbrk.o
	$(CC) $(CFLAGS) -c --coverage s21_strrchr.c -o s21_strrchr.o
	$(CC) $(CFLAGS) -c --coverage s21_strstr.c -o s21_strstr.o
	$(CC) $(CFLAGS) -c --coverage s21_strtok.c -o s21_strtok.o
	$(CC) $(CFLAGS) -c --coverage s21_support_functions.c -o s21_support_functions.o
	$(CC) $(CFLAGS) -c --coverage s21_float_or_double_to_str.c -o s21_float_or_double_to_str.o
	$(CC) $(CFLAGS) -c --coverage s21_int_to_str.c -o s21_int_to_str.o
	$(CC) $(CFLAGS) -c --coverage s21_sprintf.c -o s21_sprintf.o
	$(CC) $(CFLAGS) -c --coverage s21_strtoll.c -o s21_strtoll.o
	$(CC) $(CFLAGS) -c --coverage s21_str_to_double.c -o s21_str_to_double.o
	$(CC) $(CFLAGS) -c --coverage s21_sscanf.c -o s21_sscanf.o
	ld -r s21_memchr.o s21_memcmp.o s21_memcpy.o s21_memset.o s21_strncat.o \
	    s21_strchr.o s21_strncmp.o s21_strncpy.o s21_strcspn.o s21_strerror.o \
		s21_strlen.o s21_strpbrk.o s21_strrchr.o s21_strstr.o s21_strtok.o \
		s21_support_functions.o s21_float_or_double_to_str.o s21_int_to_str.o \
		s21_sprintf.o s21_strtoll.o s21_str_to_double.o s21_sscanf.o \
		s21_to_upper.o s21_to_lower.o s21_trim.o s21_insert.o -o $(OBJ)

	$(CC) $(CFLAGS) --coverage -o test ./tests/test_s21_string.c s21_string.o -lcheck -lm -lsubunit
	./test
	rm -f test-test_s21_string.g*
	gcovr --html --html-details -o gcov_report/index.html
clean:
	rm -f $(OBJ) $(LIBRARY) test *.gcda *.gcno *.o
	rm -rf ./gcov_report
