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
 *  dimensions  Integer, number of dimensions in simulation
 *  dt          Double, length of the time step in seconds
 *  outFreq     Integer giving number of simulation steps between dumping
 *              otput to file.
 *  output      Pointer to file that is used to save outputs
 *
 */
void leapfrog(double *masses, double *positions, double *velocities,
        int nBodies, int dimensions, double dt, int outFreq, FILE *output){

    
    // create a copy of initial positions and velocities to avoid modifying
    // the original arrays
    double *pos = dArrCopy(positions, nBodies*dimensions);
    double *vel = dArrCopy(velocites, nBodies*dimensions);


    // Calculate gravitational accelerations from other particles
    double *a = malloc(nBodies*dimensions*sizeof(double));
    
    // body feeling the force at index i
    for(int i=0; i<nBodies; i++){
        double *r1 = dArrSlice(pos, i*dimensions, dimensions);

        // set acceleration initially to zero
        for(int xyz=0; i<dimensions; i++){
            a[i*dimensions+xyz] = 0;
        }
        
        // every other body causes a force
        for(int j=0; j<nBodies; j++){
            if(i != j){
                // position of body j
                double *r2 = dArrSlice(pos, j*3, 3);
                
                // vector from r2 to r1 and its magnitude
                double *r = vectorDiff(r2, r1);
                double rLen = magnitude(rdiff, 3);

                double aMagnitude = masses[j]/pow(rdiffLen, 2.0);
                
                // direction from vector from body j to body i
                double *aDir = unitVector(rdiff, 3);
                
                // update acceleration with what we get from particle j
                for(int xyz=0; i<dimensions; i++){
                    a[i*dimensions+xyz] = a[i*dimensions+xyz] + aDir[xyz]*aMagnitude;
                }
            }
        }
    }
    
    int loopNum = 0;
    //TODO loopstuff
}
