#include <stdio.h> 
#include <stdlib.h>
#include "mathlib.h"

static int iterations;

double sqrt_newton(double x){
	
	iterations = 0;

	double val = 1.0;
	
	for(double guess = 0.0; absolute(val - guess) >= EPSILON; val = (val +x/val) / 2.0){
	
		guess = val;
		iterations ++;
	}
	
	return val;

}

int sqrt_newton_iters(void){

	
	return iterations;

}
