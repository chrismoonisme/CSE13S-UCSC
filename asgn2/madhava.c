#include "mathlib.h"

#include <stdio.h>

static int terms;

double pi_madhava(void) {

    terms = 0;

    double val = 0;

    double power = 1;

    for (double i = 0; absolute(power / ((2 * i) + 1)) > EPSILON; i++) {

        //zero case
        if (i == 0) {

            power = 1;

        } else {

            //(16 ^ -i) =  ((1/ 16) ^  i )
            power *= (1 / (3.0 * -1.0));
        }

        val += power / ((2 * i) + 1);
        terms++;
    }

    return val * sqrt_newton(12);
}

int pi_madhava_terms(void) {

    return terms;
}
