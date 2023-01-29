//include standard libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

//include mathlib file
#include "mathlib.h"

//command line options
#define OPTIONS "saebmrvnh"

//toggles (default false); 

//stats
int s = 0;
//e
int etoggle = 0;
//n
int ntoggle = 0;
//euler
int rtoggle = 0;
//bbp
int btoggle = 0;
//madhava
int mtoggle = 0;
//viete
int vtoggle = 0;


// SQRT VAL
double num;

//main
int main(int argc, char **argv){

	int opt = 0;
	
	while((opt = getopt(argc, argv, OPTIONS)) != -1){
	
		switch (opt){
		
		//help message
		case 'h': {
		
			printf("SYNOPSIS\n");
			printf("   A test harness for the small numerical library.\n\n");
			printf("USAGE\n");
			printf("   ./mathlib-test-amd64 [-aebmrvnsh]\n\n");
			printf("OPTIONS\n");
			printf("  -a   Runs all tests.\n  -e   Runs e test.\n  -b   Runs BBP pi test.\n  -m   Runs Madhava pi test.\n  -r   Runs Euler pi test.\n  -v   Runs Viete pi test.\n  -n   Runs Newton square root tests.\n  -s   Print verbose statistics.\n  -h   Display program synopsis and usage.\n");
			
			return 1;

		}
		//toggle stats
		case 's': {
			//printf("yina beeboo\n");
			s = 1;
			break;
		}
		//run all
		case 'a': {
		
			etoggle = 1;
			ntoggle = 1;
			rtoggle = 1;
			btoggle = 1;
			mtoggle = 1;
			vtoggle = 1;
			break;
		}
		
		case 'e': {
			
			//toggle e
			etoggle = 1;
			
			break;
		}
		
		case 'b': {
		
			//toggle b
			btoggle = 1;
			break;
		}
		
		case 'm': {
		
			// toggle m
			mtoggle = 1;
			break;
		}
		
		case 'r': {
		
			rtoggle = 1;
			break;
		}
		
		case 'v': {
		
			vtoggle = 1;
			break;
		}
		
		case 'n': {
		
			
			ntoggle = 1;
			break;
		}
		
		
		}
	}
	//if e is toggled
	if(etoggle == 1){
		//printf("running e option:\n");
			
		printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(M_E-e()));
		//if stats are toggles print terms
		if(s == 1){
			
			printf("e() terms = %d\n", e_terms());
			
		}
	}
	
	//euler run
	if(rtoggle == 1){
		//printf("running euler estimation:\n");
			
		printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(M_PI-pi_euler()));
		//if stats are toggles print terms
		if(s == 1){
			
			printf("pi_euler() terms = %d\n", pi_euler_terms());
			
		}
	}
	//bbp run
	if(btoggle == 1){
		//printf("running bbp estimation:\n");
			
		printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, absolute(M_PI-pi_bbp()));
		//if stats are toggles print terms
		if(s == 1){
			
			printf("pi_bbp() terms = %d\n", pi_bbp_terms());
			
		}
	}
	
	//madhava run
	if(mtoggle == 1){
		
		printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, absolute(M_PI-pi_madhava()));
		//if stats are toggles print terms
		if(s == 1){
			
			printf("pi_madhava() terms = %d\n", pi_madhava_terms());
			
		}
	}
	
	//viete run
	if(vtoggle == 1){
		
		printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, absolute(M_PI-pi_viete()));
		//if stats are toggles print terms
		if(s == 1){
			
			printf("pi_viete() terms = %d\n", pi_viete_factors());
			
		}
	}
	//if n is toggled
	if(ntoggle == 1){
			
		//sqrt
		for(double x = 0; x <10; x+= 0.1){
		
			printf("sqrt_newton(%lf) = %16.15lf, sqrt = %16.15lf, diff = %16.15lf\n", x, sqrt_newton(x), sqrt(x), absolute(sqrt(x)-sqrt_newton(x)));
			
			//if stats are toggled	
			if(s == 1){
			
				printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
			
			}
		
		}
		
		//if stats are toggled	
		if(s == 1){
			
			printf("iterations to find the sqrt: %d\n", sqrt_newton_iters());
			
		}

	}
	
	//end
	return 0;
}
