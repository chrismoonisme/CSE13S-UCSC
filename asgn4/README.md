FILES

    universe.h: header file for universe.c

    universe.c: implementation of the Universe data type, which is essentially a matrix

    life.c: allows the user to run the Game of Life simulation

    Makefile: compiles all C files

    WRITEUP.pdf: analysis

    DESIGN.pdf: pseudocode 




UNIVERSE.C HOW TO RUN

    ./life_amd64 tsn:i:o:h

OPTIONS

    -t             Create your universe as a toroidal
    -s             Silent - do not use animate the evolution
    -n {number}    Number of generations [default: 100]
    -i {file}      Input file [default: stdin]
    -o {file}      Output file [default: stdout]

MAKEFILE HOW TO COMPILE

    make option

OPTIONS

    -all/life      Compiles all C files
    -clean         Removes all executables
    -format        Formats all C and header files
