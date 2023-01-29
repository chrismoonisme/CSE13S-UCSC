#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int eterms;

double pi_euler(void) {

    double val = 0;

    //absolute(val - (val + 1 / (i*i))) > EPSILON

    eterms = 0;

    for (double i = 1; absolute(1 / (i * i)) >= EPSILON; i++) {

        val += 1 / (i * i);
        eterms++;
    }

    return sqrt_newton(val * 6);
}

int pi_euler_terms(void) {

    return eterms;
}
