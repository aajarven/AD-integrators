#include"arrayUtils.h"

/*
 * Integrates 3D system with initial positions and velocites of masses
 * given using leapfrog integrator.
 *
 * masses:      Pointer to double array containing masses for the objects,
 *              masses given as mG (m^3/s^2)
 * positions:   Pointer to double array containing initial positions of
 *              particles. Each row contains 3 elements containing
 *              x, y and z components of a particle. Units in meters
 * velocities   Pointer to double array containing initial velocities of
 *              particles. Indexed similarly to positions, Units
 *              km/s.
 *  nBodies     Integer, number of particles in simulation
 *  dt          Double, length of the time step in seconds
 *  outFreq     Integer giving number of simulation steps between dumping
 *              otput to file.
 *  output      Pointer to file that is used to save outputs
 *
 */
void leapfrog(double *masses, double *positions, double *velocities,
        int nBodies, double dt, int outFreq, FILE *output){

    
    // create a copy of initial positions and velocities to avoid modifying
    // the original arrays
    double *pos = dArrCopy(positions, nBodies*3);
    double *vel = dArrCopy(velocites, nBodies*3);

    // Calculate forces affecting particles
    double *F = malloc(nBodies*3*sizeof(double));
    //TODO actually calculate
    
    
    int loopNum = 0;
    //TODO loopstuff
}
