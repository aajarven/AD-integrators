#include<math.h>
#include<stdlib.h>
#include"arrayUtils.h"

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
