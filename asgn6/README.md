FILES:

code.h: declaration of constants, used in word.c, trie.c, and io.c

decode.c: allows user to decode a file, compressed by encode.c

decode.h

encode.c: allows user to compress a file

encode.h

io.c: mathematics and function behind encode and decode

io.h

word.c: implementation of the word ADT

word.h

trie.c: implementation of the trie ADT

trie.h

endian.h: contains functions used by io.c

WRITEUP.pdf

DESIGN.pdf

RUNNING MAKEFILE

make all to compile all .c files

make clean to remove all executables

make format to format all .c and header files

RUNNING ENCODE:

./encode -options

OPTIONS:

-i file: file to compress

-o file: file to output to

-v: toggle statistics

-h: help message

RUNNING ENCODE:

./decode -options

OPTIONS:

-i file: file to decode

-o file: file to output to

-v: toggle statistics

-h: help message





