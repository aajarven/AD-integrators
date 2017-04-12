#include <math.h>
#include <stdlib.h>
#include "arrayUtils.h"


/*
 * Creates a copy of given double array and returns pointer to it.
 *
 * in           Pointer to the array that is to be copied
 * size         Size of the array
 *
 */
double* dArrCopy(double *in, int size){
    double *out = malloc(size*sizeof(double));

    for(int i=0; i<size; i++){
        out[i] = in[i];
    }

    return out;
}


/*
 * Returns copy of a part of an double array
 *
 * in           Array to be sliced
 * start        First index to include in slice
 * len          Length of slice
 */
double* dArrSlice(double *in, int start, int len){
    double *ret = malloc(len*sizeof(double));
    for(int i=0; i++; i<len){
        ret[i] = in[start+i];
    }

    return ret;
}


/*
 * Calculates v1-v2 for vectors with given length
 *
 * v1       minuend
 * v2       subtrahend
 * len      length of vectors
 */
double* vectorDiff(double *v1, double *v2, int len){
    double *ret = malloc(len*sizeof(double));
    
    for(int i=0; i<len; i++){
        ret[i] = v1[i]-v2[i];
    }

    return ret;
}


/*
 * Returns a vector with same direction as given vector
 * but with magnitude 1
 *
 * v        original vector
 * len      length of the vector
 */
double* unitVector(double *v, int len){
    double* ret = dArrCopy(v, len);

    double origLength = 0;
    for(int i=0; i<len; i++){
        origLength += pow(v[i], 2.0);
    }
    origLength = sqrt(origLength);

    for (int i=0; i<len; i++){
        ret[i] = ret[i]/origLength;
    }

    return ret;
}


/*
 * Returns magnitude of given vector
 *
 * v        vector
 * len      length of the vector
 */
double magnitude(double *v, int len){
    double magnitude = 0;
    for(int i=0; i<len; i++){
        magnitude += pow(v[i], 2.0);
    }
    return sqrt(magnitude);
}
