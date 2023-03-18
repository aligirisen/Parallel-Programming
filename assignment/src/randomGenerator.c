#include <stdio.h>
#include <hellomake.h>
#include <stdlib.h>

double randomGenerator(){
    double randomNum = ((double)rand()/(double)(RAND_MAX)) * 100.0 + 1.0;
    return randomNum;
}