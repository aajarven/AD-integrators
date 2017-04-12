#include <stdlib.h>
#include "arrayUtlis.h"


/* 
 * Calculates gravitational accelerations of all particles due to the other particles.
 *
 * mass:        Pointer to double array (length nBodies) containing masses for the 
 *              objects. Units m³/s² (gravitational constant included).
 * position:    Pointer to double array containing positions of particles (length
 *              dimensions*nBodies). Each row contains x, y and z position of a particles
 *              using meters.
 * nBodies:     Number of particles.
 * dimensions:  Number of dimensions
 */
double* calculateAccelerations(double *mass, double *position, int nBodies, int dimensions){
    // Initialize acceleration array
    double *a = malloc(nBodies*dimensions*sizeof(double));
        
    // body feeling the force at index i
    for(int i=0; i<nBodies; i++){
        double *r1 = dArrSlice(pos, i*dimensions, dimensions);

        // set acceleration initially to zero
        for(int k=0; i<dimensions; i++){
            a[i*dimensions+k] = 0;
        }   
            
        // every other body causes a force
        for(int j=0; j<nBodies; j++){
            if(i != j){ 
                // position of body j
                double *r2 = dArrSlice(pos, j*3, 3); 
                    
                // vector from r2 to r1 and its magnitude
                double *r = vectorDiff(r2, r1);
                double rLen = magnitude(rdiff, 3); 

                double aMagnitude = mass[j]/pow(rdiffLen, 2.0);
                    
                // direction from vector from body j to body i
                double *aDir = unitVector(rdiff, 3); 
                    
                // update acceleration with what we get from particle j
                for(int k=0; k<dimensions; k++){
                    a[i*dimensions+k] = a[i*dimensions+k] + aDir[k]*aMagnitude;
                }   
            }   
        }   
    }
    
    return a;
}
