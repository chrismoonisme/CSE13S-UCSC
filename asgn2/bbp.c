#include <stdio.h> 
#include "mathlib.h"

static int terms;


double pi_bbp(void){

	double val = 0;
	
	double power = 1;
	
	terms = 0;

	for(double i = 0; absolute((power * ((i*(120*i + 151) + 47) / (i*(i*(i*(512*i + 1024) + 712) + 194)+15)))) > EPSILON; i++){	
		
		
		//zero case
		if(i == 0){
		
			power = 1;
		} else {
		
			//(16 ^ -i) =  ((1/ 16) ^  i )
			power *= (1 / 16.0);
		
		}
			

		val += (power * ((i*(120*i + 151) + 47) / (i*(i*(i*(512*i + 1024) + 712) + 194)+15)));
		terms++; 
		
		
	}
	
	
	return val;

}

int pi_bbp_terms(void){

	return terms;

}



