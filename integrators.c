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
            originToCOM(pos, masses, nBodies, dimensions);
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
void RK4(double *masses, double *positions, double *velocities,
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
        double *k1v = dArrCopy(vel, nBodies*dimensions);

        // k2a
        tmp = dArrCopy(k1a, nBodies*dimensions);
        dArrMultiply(tmp, 0.5*dt, nBodies*dimensions);
        tmpPos = vectorSum(pos, tmp, nBodies*dimensions);
        double *k2a = malloc(nBodies*dimensions*sizeof(double));
        calculateAccelerations(k2a, masses, tmpPos, nBodies, dimensions);
        free(tmpPos);
        free(tmp);
        
        // k2v
        tmp = dArrCopy(k1v, nBodies*dimensions);
        dArrMultiply(tmp, 0.5*dt, nBodies*dimensions);
        double *k2v = vectorSum(vel, tmp, nBodies*dimensions);
        free(tmp);

        // k3a
        tmp = dArrCopy(k2a, nBodies*dimensions);
        dArrMultiply(tmp, 0.5*dt, nBodies*dimensions);
        tmpPos = vectorSum(pos, tmp, nBodies*dimensions);
        double *k3a = malloc(nBodies*dimensions*sizeof(double));
        calculateAccelerations(k3a, masses, tmpPos, nBodies, dimensions);
        free(tmp);
        free(tmpPos);

        // k3v
        tmp = dArrCopy(k2v, nBodies*dimensions);
        dArrMultiply(tmp, 0.5*dt, nBodies*dimensions);
        double *k3v = vectorSum(vel, tmp, nBodies*dimensions);
        free(tmp);

        // k4a
        tmp = dArrCopy(k3a, nBodies*dimensions);
        dArrMultiply(tmp, dt, nBodies*dimensions);
        tmpPos = vectorSum(pos, tmp, nBodies*dimensions);
        double *k4a = malloc(nBodies*dimensions*sizeof(double));
        calculateAccelerations(k4a, masses, tmpPos, nBodies, dimensions);
        free(tmp);
        free(tmpPos);

        // k4v
        tmp = dArrCopy(k3v, nBodies*dimensions);
        dArrMultiply(tmp, dt, nBodies*dimensions);
        double *k4v = vectorSum(vel, tmp, nBodies*dimensions);
        free(tmp);

        // next velocity
        dArrMultiply(k2a, 2.0, nBodies*dimensions);
        dArrMultiply(k3a, 2.0, nBodies*dimensions);
        tmp1 = vectorSum(k1a, k2a, nBodies*dimensions); 
        tmp2 = vectorSum(tmp1, k3a, nBodies*dimensions);
        free(tmp1);
        tmp1 = vectorSum(tmp2, k4a, nBodies*dimensions);
        dArrMultiply(tmp1, dt/6.0, nBodies*dimensions);
        free(tmp2);
        tmp2 = vectorSum(vel, tmp1, nBodies*dimensions);
        free(tmp1);
        free(vel);
        vel = dArrCopy(tmp2, nBodies*dimensions);
        free(tmp2);

        // nextxt acceleration
        dArrMultiply(k2v, 2.0, nBodies*dimensions);
        dArrMultiply(k3v, 2.0, nBodies*dimensions);
        tmp1 = vectorSum(k1v, k2v, nBodies*dimensions); 
        tmp2 = vectorSum(tmp1, k3v, nBodies*dimensions);
        free(tmp1);
        tmp1 = vectorSum(tmp2, k4v, nBodies*dimensions);
        dArrMultiply(tmp1, dt/6.0, nBodies*dimensions);
        free(tmp2);
        tmp2 = vectorSum(pos, tmp1, nBodies*dimensions);
        free(tmp1);
        free(pos);
        pos = dArrCopy(tmp2, nBodies*dimensions);
        free(tmp2);

        if(loopNum%outFreq == 0){
            originToCOM(pos, masses, nBodies, dimensions);
            dumpSim(output, time, pos, vel, nBodies, dimensions);
        }
    }
    
    free(pos);
    free(vel);
    free(a);

}
