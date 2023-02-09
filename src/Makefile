CC = gcc
EFLAGS = -Wall -Wextra -Werror -std=c11 -g
CFLAGS = $(EFLAGS) -c
OFLAGS = $(EFLAGS) -o
S21_DECIMAL_C = functions/*.c
S21_DECIMAL_O = *.o

all: clean test

s21_decimal.a:
	$(CC) $(CFLAGS) $(S21_DECIMAL_C)
	ar r s21_decimal.a $(S21_DECIMAL_O)
	rm -rf *.o
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $(CFLAGS) main.c
	$(CC) $(OFLAGS) test main.o s21_decimal.a -lm
	rm -rf *.o *.a
	./test

check:
	cppcheck --enable=all --inconclusive --std=c11 --suppress=missingIncludeSystem ./
	clang-format -n *.c *.h

clean:
	rm -rf *.o *.a test tgtests *.gcda *.gcno *.gcov *.html *.css *.out

rebuild: clean all
