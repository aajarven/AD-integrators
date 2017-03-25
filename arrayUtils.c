#include<stdlib.h>


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
