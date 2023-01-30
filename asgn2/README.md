#FILES: 

e.c:

-contains functions to estimate the value of e using a series, to a certain accuracy, and return the the number of terms the series takes to reach said accuracy

bbp.c:

-contains functions to estimate the value of PI using the BBP series, to a certain accuracy, and return the the number of terms the series takes to reach said accuracy

euler.c:

-contains functions to estimate the value of PI using Euler's method, to a certain accuracy, and return the the number of iterations the method takes to reach said accuracy

madhava.c:

-contains functions to estimate the value of PI using the Madhava series, to a certain accuracy, and return the the number of terms the series takes to reach said accuracy

viete.c

-contains functions to estimate the value of PI using the Viete series, to a certain accuracy, and return the the number of terms the series takes to reach said accuracy

newton.c:

-contains functions to estimate the square root of a value, to a certain accuracy. 

mathlib-test.c:

-allows the user to run the above estimation functions, and returns statistics on said function.  Statistics include value comparisons to math.h's M_PI constant, M_E constant, and sqrt() function.

    HOW TO RUN (assumes already compiled):

        ./mathlib-test -option

-OPTIONS: 

    -h: prints a help message, explaining how to use the program, and terminates the program. 
    -a: runs all estimation functions
    -s: toggles display of terms (default, NO TERMS)
    -e: runs the e estimation function in e.c, comparing the value of e to M_E
    -n: runs the sqrt estimation function in newton.c, using values from 0-10, inclusive.  Compares the estimated values to sqrt()
    -m: runs the PI estimation function in madhava.c, comparing the value to M_PI
    -r: runs the PI estimation function in euler.c, comparing the value to M_PI
    -b: runs the PI estimation function in bbp.c, comparing the value to M_PI
    -v: runs the PI estimation function in viete.c, comparing the value to M_PI

Makefile:

-compiles all c files

    HOW TO RUN:

        make option

-OPTIONS

    all: compiles all c files
    clean: removes all executables
    format: formats all .c files


