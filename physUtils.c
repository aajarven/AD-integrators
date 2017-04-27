#include <stdlib.h>
#include <math.h>
#include "arrayUtils.h"


/* 
 * Calculates gravitational accelerations of all particles due to the other particles.
 *
 * a:           Pointer to double array that will contain accelerations after
 *              this function is run
 * mass:        Pointer to double array (length nBodies) containing masses for the 
 *              objects. Units m³/s² (gravitational constant included).
 * position:    Pointer to double array containing positions of particles (length
 *              dimensions*nBodies). Each row contains x, y and z position of a particles
 *              using meters.
 * nBodies:     Number of particles.
 * dimensions:  Number of dimensions
 */
void calculateAccelerations(double *a, double *mass, double *position, int nBodies, int dimensions){
        
    // body feeling the force at index i
    for(int i=0; i<nBodies; i++){
        double *r1 = dArrSlice(position, i*dimensions, dimensions);

        // set acceleration initially to zero
        for(int k=0; k<dimensions; k++){
            a[i*dimensions+k] = 0;
        }   
            
        // every other body causes a force
        for(int j=0; j<nBodies; j++){
            if(i != j){ 
                // position of body j
                double *r2 = dArrSlice(position, j*dimensions, dimensions);

                // vector from r2 to r1 and its magnitude
                double *r = vectorDiff(r2, r1, dimensions);
                double rLen = magnitude(r, dimensions); 

                double aMagnitude = mass[j]/pow(rLen, 2.0);
                    
                // direction from vector from body j to body i
                double *aDir = unitVector(r, dimensions); 
                    
                // update acceleration with what we get from particle j
                for(int k=0; k<dimensions; k++){
                    a[i*dimensions+k] = a[i*dimensions+k] + aDir[k]*aMagnitude;
                }
                free(r2);
                free(r);
                free(aDir);
            } 
        }
       free(r1);
    }
    
    return a;
}

/*
 * Updates all velocities
 *
 * vel:     Pointer to double array containing velocities to be updated
 * a:       Pointer to double array containing accelerations
 * dt:      Double, length of the time step
 * N:       Integer, length of the arrays
 */
void kick(double *vel, double *a, double dt, int N, int dimensions){
    for(int i=0; i<N*dimensions; i++){
        vel[i] = vel[i] + a[i]*dt;
    }
}


/*
 * Updates all positions 
 *
 * pos:     Pointer to double array containing positions to be updated
 * vel:     Pointer to double array containing velocities
 * dt:      Double, length of the time step
 * N:       Integer, length of the arrays
 */
void drift(double *pos, double *vel, double dt, int N, int dimensions){
    for(int i=0; i<N*dimensions; i++){
        pos[i] = pos[i] + vel[i]*dt;
    }
}
