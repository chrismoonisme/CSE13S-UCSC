cc = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: sorting

sorting: quick.c stats.c shell.c heap.c set.c batcher.c sorting.c
	$(cc) -o sorting quick.c stats.c shell.c heap.c set.c batcher.c sorting.c

sorting.o: *.c
	$(cc) $(CFLAGS) -c *.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c

	


