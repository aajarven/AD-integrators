#include <stdlib.h>
#include <stdio.h>
#include "arrayUtils.h"
#include "fileio.h"
#include "leapfrog.h"
#include "consts.h"


int main(int argc, char *argv[]){

    if (argc<9){
        printf("\nYou must give path to initial conditions, number of bodies in simulation, number of dimensions, length of time step (in years), length of simulation (yr), number of integration time steps between consecutive outputs to file and path to the output destination file and simulation type ('l' for leapfrog or 'r' for RK4). For example\n\tinput/input_precise.dat 6 3 0.01 250 10 output/out.dat l\nfor leapfrog simulation with 6 bodies in 3D space using timestep of 0.01 yr, running 250 years and outputting every 0.1 years, where input is read from file input/input_precise.dat and output is written to output/out.dat.\n\nNB! Erroneous arguments or nonexistent input file may cause an unhandled crash.\n\n");
        exit(-1);
    }

    FILE *in;
    in = fopen(argv[1], "r");

    int nBodies, dimensions, outFreq;
    double step, endTime;
    sscanf(argv[2], "%d", &nBodies);
    sscanf(argv[3], "%d", &dimensions);
    sscanf(argv[4], "%lf", &step);
    sscanf(argv[5], "%lf", &endTime);
    sscanf(argv[6], "%d", &outFreq);

    double *positions = malloc(nBodies*dimensions*sizeof(double));
    double *velocities = malloc(nBodies*dimensions*sizeof(double));
    double *masses = malloc(nBodies*sizeof(double));

    readInitialConditions(in, positions, velocities, masses);
    dArrMultiply(velocities, dayInYr, nBodies*dimensions);
    dArrMultiply(masses, 1.0/kgInMSun, nBodies);
    dArrMultiply(masses, 4*pi*pi, nBodies);

    FILE *out;
    out = fopen(argv[7], "w");
    leapfrog(masses, positions, velocities, nBodies, dimensions, step, endTime, outFreq, out);

    free(positions);
    free(velocities);
    free(masses);
}
