#!/bin/bash



#clean all prexisting executables and then compile monte_carlo only
make clean && make monte_carlo

#clean files
>/tmp/error.dat

>/tmp/error2.dat

>/tmp/error3.dat

>/tmp/error4.dat

>/tmp/inside.dat

>/tmp/outside.dat

>/tmp/random.dat

#GRAPHING THE ERROR
#run monte carlo with a given seed -> take the first two columns of the output which will be index and estimate of pi -> find error using estimate -> cut out header line -> data file
echo "$(./monte_carlo -n 65536 -r 100| awk '{print $1, '3.141592' - $2}' | tail -n 65535)" >> /tmp/error.dat;

echo "$(./monte_carlo -n 65536 -r 200| awk '{print $1, '3.141592' - $2}' | tail -n 65535)" >> /tmp/error2.dat;

echo "$(./monte_carlo -n 65536 -r 300| awk '{print $1, '3.141592' - $2}' | tail -n 65535)" >> /tmp/error3.dat;

echo "$(./monte_carlo -n 65536 -r 400| awk '{print $1, '3.141592' - $2}' | tail -n 65535)" >> /tmp/error4.dat;


#GRAPHING THE COORDINATES

echo "$(./monte_carlo -n 500 -r 567 | tail -n 499 | awk '{ if ($5 == "0") print $3, $4;}' )" >> /tmp/outside.dat;

echo "$(./monte_carlo -n 500 -r 567 | tail -n 499 | awk '{ if ($5 == "1") print $3, $4;}' )" >> /tmp/inside.dat;

#pi with regards to X

echo "$(./monte_carlo -n 100 -r 100| awk '{print $1, $2}' | tail -n 99)" >> /tmp/random.dat;


#graph
gnuplot <<END

set terminal pdf
set output "pivx.pdf"
set title "PI estimate over iterations"
plot "/tmp/random.dat" with lines title ""


set terminal pdf
set output "circle.pdf"
set title ""
set xtics 0.2
set ytics 0.2
plot [x=0:1] sqrt(1-x**2) lt rgb "black" title "", "/tmp/inside.dat" with dots lt rgb "blue" title "", "/tmp/outside.dat" with dots lt rgb "red" title ""


set terminal pdf
set output "error.pdf"
set title "Monte Carlo Error Estimation"
set ylabel "Error"
set logscale x 4
set ytics .5
set yrange [-1:1]
set zeroaxis
plot "/tmp/error.dat" with lines title "seed 1", "/tmp/error2.dat" with lines title "seed 2", "/tmp/error3.dat" with lines title "seed 3", "/tmp/error4.dat" with lines title "seed 4"



END

