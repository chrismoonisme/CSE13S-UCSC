#include "mathlib.h"

#include <stdio.h>

static int terms;

double pi_viete(void) {

    terms = 0;

    double root = 1;

    double prev = 0;

    double val = 1;

    for (double i = 0; absolute((sqrt_newton(2 + root) / 2) - (root / 2.0)) >= EPSILON; i++) {

        //r = sqrt(r)

        if (i == 0) {

            root = sqrt_newton(2);

        } else {

            root = sqrt_newton(2 + root);
        }

        val *= (root / 2.0);

        terms++;
    }

    //since the series returns 2/pi
    return 2 / val;
}

int pi_viete_factors(void) {

    return terms;
}
