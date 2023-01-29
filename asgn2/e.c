#include "mathlib.h"

#include <stdio.h>

static int terms;

double e(void) {

    terms = 1;
    double val = 0;

    double f = 1;

    //go until error is less than epsilon
    for (double i = 1; absolute(val - (val + 1 / f)) > EPSILON; i++) {

        val += 1 / f;

        f *= i;

        terms++;
    }

    return val;
}

int e_terms(void) {

    return terms;
}
