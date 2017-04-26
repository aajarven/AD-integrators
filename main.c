#include <stdlib.h>
#include <stdio.h>
#include "fileio.h"
#include "leapfrog.h"


void main(){
    FILE *in;
    in = fopen("input/input_precise.dat", "r");

    double *positions = malloc(6*3*sizeof(double));
    double *velocities = malloc(6*3*sizeof(double));
    double *masses = malloc(6*sizeof(double));

    readInitialConditions(in, positions, velocities, masses);
}
