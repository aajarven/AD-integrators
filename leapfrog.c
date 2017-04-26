#include <stdlib.h>
#include "arrayUtils.h"
#include "physUtils.h"
#include "fileio.h"

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
 *  endtime     Double, time at which the simulation terminates
 *  outFreq     Integer giving number of simulation steps between dumping
 *              otput to file.
 *  output      Pointer to file that is used to save outputs
 *
 */
void leapfrog(double *masses, double *positions, double *velocities,
        int nBodies, int dimensions, double dt, double endtime, int outFreq, FILE *output){


    // create a copy of initial positions and velocities to avoid modifying
    // the original arrays
    double *pos = dArrCopy(positions, nBodies*dimensions);
    double *vel = dArrCopy(velocites, nBodies*dimensions);
    double *a;
    double time = 0;
    int loopNum = 0;

    while (time < endtime){
        time += dt;
        loopNum++;

        a = calculateAccelerations(masses, pos, nBodies, dimensions);
        kick(vel, a, dt/2.0, nBodies, dimensions);
        
        drift(pos, vel, dt, nBodies, dimensions);
        
        a = calculateAccelerations(masses, pos, nBodies, dimensions);
        kick(vel, a, dt/2.0, nBodies, dimensions);

        if(loopNum%outFreq = 0){
            dumpSim(output, pos, vel, nBodies, dimensions);
        }
    }
}
