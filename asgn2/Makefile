
cc = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: mathlib-test

mathlib-test: viete.c madhava.c bbp.c euler.c newton.c e.c mathlib-test.c
	$(cc) -o mathlib-test viete.c madhava.c bbp.c euler.c newton.c e.c mathlib-test.c -lm

mathlib-test.o: *.c
	$(cc) $(CFLAGS) -c *.c

clean:
	rm -f mathlib-test *.o

format:
	clang-format -i -style=file *.c
