#include <stdio.h>
#include <stdlib.h>

/*
 * Writes state of the simulation to given file in form
 * index of object; positions;  velocity;
 * 
 * Different dimensions are separated with comma.
 *
 * fp:          Pointer to output file
 * pos:         Double array containing positions to be written
 * vel:         Double array containing velocities to be written
 * nBodies:     Number of bodies in simulation
 * dimensions:  Number of dimensions
 *
 */
void dumpSim(FILE *fp, double *pos, double *vel, int nBodies, int dimensions){
    for(int i=0; i<nBodies; i++){
        // index of body
        fprintf(fp, "%i;\t", i);
           
        // position
        for(int j=0; j<dimensions; j++){
            fprintf(fp, "%10.e", pos[i*dimensions+j]);
            if (j<dimensions-1){
                fprintf(fp, ",\t");
            } else {
                fprintf(fp, ";\t");
            }
        }
        
        // velocity
        for(int j=0; j<dimensions; j++){
            fprintf(fp, "%10.e", vel[i*dimensions+j]);
            if (j<dimensions-1){
                fprintf(fp, ",\t");
            } else {
                fprintf(fp, ";\n");
            }
        }
    }
}


/*
 * Reads initial conditions from file, each row containing data for one body,
 * first three rows representing position, next three velocities and last one mass,
 * and writes them into the given arrays. Numbers in scientific notation separated
 * by space.
 *
 * Empty lines and lines starting with # are ignored.
 *
 * fp:          File pointer to input file
 * pos:         Double array that is big enough for the data (3*nBodies), will
 *              contain the positions of bodies
 * vel:         Double array that is big enough for the data (3*nBodies), will
 *              contain the velocities of bodies
 * mass:        Double array that is big enough for the data (nBodies), will
 *              contain the masses of bodies
 *
 */
void readInitialConditions(FILE *fp, double *pos, double *vel, double *mass){
    size_t maxLinelength = 256;
    char *lineBuffer = malloc(maxLinelength*sizeof(char));
    int index = 0;

    while (getline(&lineBuffer, &maxLinelength, fp) != -1){
        // skip empty lines and lines starting with #
        if (strlen(lineBuffer) > 1 && lineBuffer[0] != '#'){
            sscanf(*lineBuffer, "%e %e %e %e %e %e %e", pos[i], pos[i+1], pos[i+2],
                    vel[i], vel[i+1], vel[i+2], mass[i]);
            i++;
        }
    }
}
