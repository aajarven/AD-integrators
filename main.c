#include <stdlib.h>
#include <stdio.h>
#include "arrayUtils.h"
#include "fileio.h"
#include "leapfrog.h"
#include "consts.h"


void main(){
    FILE *in;
    in = fopen("input/input_precise.dat", "r");

    double *positions = malloc(6*3*sizeof(double));
    double *velocities = malloc(6*3*sizeof(double));
    double *masses = malloc(6*sizeof(double));

    readInitialConditions(in, positions, velocities, masses);
    dArrMultiply(velocities, dayInYr, 6*3);
    dArrMultiply(masses, 1.0/kgInMsun, 6);

    FILE *out;
    out = fopen("output/test.dat", "w");
    dumpSim(out, positions, velocities, 6, 3);
}
