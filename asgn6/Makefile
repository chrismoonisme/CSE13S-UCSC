SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: encode decode

encode: encode.c trie.c io.c word.c
	$(CC) -o encode encode.c trie.c io.c word.c

encode.o: *.c 
	$(CC) $(CFLAGS) -c *.c

decode: decode.c trie.c io.c word.c
	$(CC) -o decode decode.c trie.c io.c word.c

decode.o: *.c 
	$(CC) $(CFLAGS) -c *.c


clean: 
	rm -f encode .o
	rm -f decode .o

format: 
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h

