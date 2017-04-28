#include <stdio.h>
#include <stdlib.h>
#include "arrayUtils.h"
#include "physUtils.h"
#include "fileio.h"

/*
 * Integrates n dimensional system with initial positions and velocites
 * of masses given using leapfrog integrator.
 *
 * masses:      Pointer to double array containing masses for the objects,
 *              masses given as mG (AU^3/yr^2)
 * positions:   Pointer to double array containing initial positions of
 *              particles. Each row contains 3 elements containing
 *              x, y and z components of a particle. Units in AU
 * velocities   Pointer to double array containing initial velocities of
 *              particles. Indexed similarly to positions, Units
 *              AU/yr.
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
    double *vel = dArrCopy(velocities, nBodies*dimensions);
    double *a = malloc(nBodies*dimensions*sizeof(double));
    double time = 0;
    int loopNum = 0;

    while (time < endtime){
        time += dt;
        loopNum++;

        calculateAccelerations(a, masses, pos, nBodies, dimensions);
        kick(vel, a, dt/2.0, nBodies, dimensions);
        
        drift(pos, vel, dt, nBodies, dimensions);
        
        calculateAccelerations(a, masses, pos, nBodies, dimensions);
        kick(vel, a, dt/2.0, nBodies, dimensions);

        if(loopNum%outFreq == 0){
            dumpSim(output, time, pos, vel, nBodies, dimensions);
        }
    }
    
    free(pos);
    free(vel);
    free(a);
}


/*
 * Integrates n dimensional system with initial positions and velocites
 * of masses given using fourth order Runge-Kutta integrator.
 *
 * masses:      Pointer to double array containing masses for the objects,
 *              masses given as mG (AU^3/yr^2)
 * positions:   Pointer to double array containing initial positions of
 *              particles. Each row contains 3 elements containing
 *              x, y and z components of a particle. Units in AU
 * velocities   Pointer to double array containing initial velocities of
 *              particles. Indexed similarly to positions, Units
 *              AU/yr.
 *  nBodies     Integer, number of particles in simulation
 *  dimensions  Integer, number of dimensions in simulation
 *  dt          Double, length of the time step in seconds
 *  endtime     Double, time at which the simulation terminates
 *  outFreq     Integer giving number of simulation steps between dumping
 *              otput to file.
 *  output      Pointer to file that is used to save outputs
 *
 */
void rk4(double *masses, double *positions, double *velocities,
        int nBodies, int dimensions, double dt, double endtime, int outFreq, FILE *output){
    
    double *pos = dArrCopy(positions, nBodies*dimensions);
    double *vel = dArrCopy(velocities, nBodies*dimensions);
   
    double *tmp; 
    double *tmp1;
    double *tmp2;
    double *tmpPos;
    double *a = malloc(nBodies*dimensions*sizeof(double));

    double time = 0;
    int loopNum = 0;

    while (time < endtime){
        time += dt;
        loopNum++;

        calculateAccelerations(a, masses, pos, nBodies, dimensions);
        double *k1a = dArrCopy(a, nBodies*dimensions);
        double *k1v = dArrCopy(vel nBodies*dimension);

        // k2a
        tmp = dArrCopy(k1a, nBodies*dimensions);
        tempPos = vectorSum(pos, dArrMultiply(tmp, 0.5*dt, nBodies*dimensions), nBodies*dimensions);
        double *k2a = malloc(nBodies*dimensions*sizeof(double));
        calculateAcceleration(k2a, masses, tempPos, nBodies, dimensions);
        free(tempPos);
        free(tmp);
        
        // k2v
        tmp = dArrCopy(k1v, nBodies*dimensions);
        double *k2v = vectorSum(vel, dArrMultiply(tmp, 0.5*dt, nBodies*dimensions), nBodies*dimensions);
        free(tmp);

        // k3a
        tmp = dArrCopy(k2a, nBodies*dimensions);
        tmpPos = vectorSum(pos, dArrMultiply(tmp, 0.5*dt, nBodies*dimensions), nBodies*dimensions);
        double *k3a = malloc(nBodies*dimensions*sizeof(double));
        calculateAcceleration(k3a, masses, tmpPos, nBodies, dimensions);
        free(tmp);
        free(tmpPos);

        // k3v
        tmp = dArrCopy(k2v, nBodies*dimensions);
        double *k2v = vectorSum(vel, dArrMultiply(tmp, 0.5*dt, nBodies*dimensions), nBodies*dimensions);
        free(tmp);

        // k4a
        tmp = dArrCopy(k3a, nBodies*dimensions);
        tmpPos = vectorSum(pos, dArrMultiply(tmp, k3a), nBodies*dimensions);
        double *k4a = malloc(nBodies*dimensions*sizeof(double));
        calculateAcceleration(k4a, masses, tmpPos, nBodies, dimensions);
        free(tmp);
        free(tmpPos);

        // k4v
        tmp = dArrCopy(k3v, nBodies*dimensions);
        double *k4v = vectorSum(vel, dArrMultiply(tmp, dt, nBodies*dimensions), nBodies*dimensions);
        free(tmp);

        // next velocity
        tmp1 = vectorSum(k1a, dArrMultiply(k2a, 2.0, nBodies*dimensions), nBodies*dimensions); 
        tmp2 = dArrCopy(tmp1, dArrMultiply(k3a, 2.0, nBodies*dimensions), nBodies*dimensions);
        free(tmp1);
        tmp1 = vectorSum(tmp2, k4a, nBodies*dimensions);
        dArrMultiply(tmp1, dt/6.0, nBodies*dimensions);
        free(tmp2);
        tmp2 = vectorSum(vel, tmp1, nBodies*dimensions);
        free(vel);
        vel = tmp2;
        free(tmp2);

        // nextxt acceleration
        tmp1 = vectorSum(k1v, dArrMultiply(k2v, 2.0, nBodies*dimensions), nBodies*dimensions); 
        tmp2 = dArrCopy(tmp1, dArrMultiply(k3v, 2.0, nBodies*dimensions), nBodies*dimensions);
        free(tmp1);
        tmp1 = vectorSum(tmp2, k4v, nBodies*dimensions);
        dArrMultiply(tmp1, dt/6.0, nBodies*dimensions);
        free(tmp2);
        tmp2 = vectorSum(pos, tmp1, nBodies*dimensions);
        free(pos);
        pos = tmp2;
        free(tmp2);

        if(loopNum%outFreq == 0){
            dumpSim(output, time, pos, vel, nBodies, dimensions);
        }
    }
    
    free(pos);
    free(vel);
    free(a);

}
