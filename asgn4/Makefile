cc = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic


all: life

life: universe.c life.c
	$(cc) -o life universe.c life.c -lncurses

life.o: *.c
	$(cc) $(CFLAGS) -c *.c
clean:
	rm -f life *.o

format:
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h



