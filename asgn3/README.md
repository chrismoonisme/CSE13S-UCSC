#FILES:
batcher.c:
-contains implementation of Batcher's merge sort method, which sorts an array from least to greatest, tracking moves and compares. 

quick.c:
-contains implementation of the quicksort method, which sorts an array from least to greatest, tracking moves and compares. 

heap.c:
-contains implementation of the heapsort method, which sorts an array from least to greatest, tracking moves and compares. 

shell.c:
-contains implementation of the shellsort method, which sorts an array from least to greatest, tracking moves and compares. 

set.c
-contains implementations of the set data structure, used in sorting.c

stats.c:
-contains implementations of the stats struct, allowing tracking of moves and compares

sorting.c:
-allows the user to run the above sorting functions, and returns statistics on said functions.  Statistics include moves and compares for each function.

gaps.h:
-contains the gap array used in shell.c

HOW TO RUN (assumes already compiled):

    ./sorting -option


-OPTIONS:

    -H              Display program help and usage.

    -a              Enable all sorts.

    -b              Enable Batcher Sort.

    -h              Enable Heap Sort.

    -q              Enable Quick Sort.

    -s              Enable Shell Sort.

    -n length       Specify number of array elements (default: 100).

    -p elements     Specify number of elements to print (default: 100).

    -r seed         Specify random seed (default: 13371453).


Makefile:
-compiles all c files

HOW TO RUN:

    make option


-OPTIONS

all: compiles all c files
clean: removes all executables
format: formats all .c files
