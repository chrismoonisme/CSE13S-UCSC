#FILES

DESIGN.pdf

    -psuedocode and project description

WRITEUP.pdf

    -includes graphs of the Monte Carlo estimates and points, as well as description of said graphs and processes

monte_carlo.c

    -C implementation of the Monte Carlo method of approximating pi.  Takes command line inputs:

    run format: ./monte_carlo -x      
    
    where x is the option

    OPTIONS:

    -n points: specifies the number of points.  More points = more accurate estimations. 

    -r seed: specifies the seed for the random number generator

plot.sh

    -bash script that creates graphs of Monte Carlo estimates and points

    run format: ./plot.sh

Makefile

    -compiles monte_carlo.c

    run format: make option

    OPTIONS:

    all/monte_carlo: compiles monte_carlo

    clean: removes all executables 

    format: formats the C files
